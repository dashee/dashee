#include "threads.h"


// Device locks
dashee::Threads::LockReadWrite lockConfig = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockServer = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockHardwareServoController 
    = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockVehicle = dashee::Threads::LockReadWrite();

// Unique to this file locks
dashee::Threads::LockMutex lockBuffer = dashee::Threads::LockMutex();

// System Locks
dashee::Threads::LockReadWrite lockEXIT = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockRELOAD = dashee::Threads::LockReadWrite();

// Sensor Locks
dashee::Threads::LockReadWrite lockHardwareAccelerometer
    = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockSensor = dashee::Threads::LockReadWrite();

// Define our thread shared globals
dashee::Buffer<unsigned char> buffer = dashee::Buffer<unsigned char>();
std::chrono::milliseconds lastRead = static_cast<std::chrono::milliseconds>(0);

/**
 * This is a simple thread that is run to initialize the controller
 *
 * @param container The controller to set the locks to
 */
void threadInitilizeContainer(Container * container)
{
    if (container == NULL)
        throw dashee::Exception("container passed as NULL");

    container->setLockConfig(
            static_cast<dashee::Threads::Lock *>(&lockConfig)
        );
    container->setLockServer(
            static_cast<dashee::Threads::Lock *>(&lockServer)
        );
    container->setLockHardwareServoController(
            static_cast<dashee::Threads::Lock *>(&lockHardwareServoController)
        );
    container->setLockHardwareAccelerometer(
            static_cast<dashee::Threads::Lock *>(&lockHardwareAccelerometer)
        );
    container->setLockVehicle(
            static_cast<dashee::Threads::Lock *>(&lockVehicle)
        );
}

/**
 * Check the value of EXIT and returns true or false telling the thread
 * of its status to keep going or not
 *
 * @retval true Keep Going
 * @retval false Stop
 */
bool threadKeepGoing()
{
    dashee::Threads::Scope scope(
            &lockEXIT, 
            dashee::Threads::Lock::LOCKTYPE_READ
        );
    if (EXIT) return false;

    return true;
}

/**
 * Loop through calling read and reading from the server.
 *
 * The read should handle SIGTERM so no timeout should be required.
 *
 * @param s The pointer to the Server object
 *
 * @returns Nothing
 */
void * threadReadFromServer(void * s)
{
    // Cast our pointer
    dashee::Server * server = static_cast<dashee::Server *>(s);

    try
    {
        while(threadKeepGoing())
        {
            if (server->read())
            {
                lastRead = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                );
                dashee::Threads::Scope scope(&lockBuffer);

                if(server->getBufferByte(0) == '\1'){
                    server->write("pong");
                }
                else {
                    server->appendBufferTo(&buffer);

                    // Remove any excess values, good to clean up in case this
                    // just keeps growing till the cows come home
                    while (buffer.size() > DASHEE_SERVOD_THREADS_BUFFERSIZE)
                        buffer.pop();
                }
            }
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromServer failed as Exception thrown: %s", 
                ex.what()
            );

        dashee::Threads::Scope scope(&lockEXIT);
        EXIT = 1;
    }

    dashee::Threads::Thread::exit();
    return NULL;
}

/**
 * Update our sensors every tick.
 *
 * @param c The pointer to the container which holds points to the sensors
 *
 * @returns Nothing
 */
void * threadUpdateSensors(void * c)
{
    Container * container = static_cast<Container *>(c);

    try
    {
        while(threadKeepGoing())
        {
	    {
		dashee::Threads::Scope scopeSensor(&lockSensor);
		dashee::Threads::Scope scopeHardwareAccelerometer(
			&lockHardwareAccelerometer
		    );

		container->getHardwareAccelerometer()->update();
		//container->getHardwareGyro()->update();
		//container->getHardwareMagnometer()->update();
	    }

            dashee::sleep(DASHEE_SERVOD_THREADS_TICK_SENSOR);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromSensor failed as Exception thrown: %s", 
                ex.what()
            );
        
        dashee::Threads::Scope scope(&lockEXIT);
        EXIT = 1;
    }

    dashee::Threads::Thread::exit();
    return NULL;
}

/**
 * This is our main loop which reads from servers, and sensors 
 * and updates the vehicle model. The controller itself holds all
 * the known pointer to different aspect of the systems and should
 * internally worry about locking different objects.
 *
 * @param c The pointer to the Controller
 *
 * @returns Nothing
 */
void * threadStepController(void * c)
{
    Container * container = static_cast<Container *>(c);
    dashee::Vehicle * vehicle = container->getVehicle();

    try
    {
        while(threadKeepGoing())
        {
            {
                dashee::Threads::Scope scope(
                        &lockRELOAD
                    );

                // Reload from configuration and reset the value of our vehicle,
                // because the pointer vehicle will no longer exist after the 
                // reload
                if (RELOAD)
                {
                    container->reloadConfiguration();
                    vehicle = container->getVehicle();
                    RELOAD = 0;
                }
            }

            // Do to main things
            {
                dashee::Threads::Scope scope(&lockBuffer);
                dashee::Threads::Scope scopeVehicle(&lockVehicle);

                std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                );

                std::chrono::milliseconds timeout = static_cast<std::chrono::milliseconds>(
                        DASHEE_SERVOD_FALLBACK_TIMEOUT
                );

                if((currentTime - lastRead) > timeout){
                    vehicle->fallback();
                }
                else {
                    vehicle->revert();
                    vehicle->read(&buffer);
                    //vehicle->read(&sensor);
                }

                vehicle->update();
            }

            dashee::sleep(DASHEE_SERVOD_THREADS_TICK_CONTROLLER);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadStepController failed as Exception thrown: %s", 
                ex.what()
            );

        dashee::Threads::Scope scope(&lockEXIT);
        EXIT = 1;
    }

    dashee::Threads::Thread::exit();
    return NULL;
}
