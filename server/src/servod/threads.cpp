#include "threads.h"

// Define our locks
dashee::Threads::LockReadWrite lockConfig = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockServer = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockServoController 
    = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockSensor = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockVehicle = dashee::Threads::LockReadWrite();
dashee::Threads::LockMutex lockBuffer = dashee::Threads::LockMutex();
dashee::Threads::LockReadWrite lockEXIT = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockRELOAD = dashee::Threads::LockReadWrite();

// Define our thread shared globals
std::queue<unsigned char> buffer = std::queue<unsigned char>();

/**
 * This is a simple thread that is run to initilize the controller
 *
 * @param controller The controller to set the locks to
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
    container->setLockServoController(
            static_cast<dashee::Threads::Lock *>(&lockServoController)
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
                dashee::Threads::Scope scope(&lockBuffer);
 
                // Take the buffer   
                server->appendBufferTo(&buffer);

                // Remove any excess values, good to clean up incase this 
                // just keeps growing till the cows come home
                while (buffer.size() > DASHEE_SERVOD_THREADS_BUFFERSIZE) 
                    buffer.pop();
            }

            //dashee::Log::info(3, "Server Step");
            //dashee::sleep(DASHEE_SERVOD_THREADS_TICK_SERVER);
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
 * Read from sensor and update the sensor model, passed by the pointer
 *
 * @param sensor The pointer to the SensorIMU
 *
 * @returns Nothing
 */
void * threadUpdateSensors(void * sensor)
{
    try
    {
        while(threadKeepGoing())
        {
            //dashee::Log::info(3, "Sensor Step");
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
 * the known pointer to different aspec of the systems and should
 * internally worry about locking different objects.
 *
 * @param c The pointer to the Controller
 *
 * @returns Nothing
 */
void * threadStepController(void * c)
{
    Controller * controller = static_cast<Controller *>(c);
    Container * container = controller->getContainer();
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
                    controller->getContainer()->reloadConfiguration();
                    vehicle = container->getVehicle();
                    RELOAD = 0;
                }
            }

            {
                dashee::Threads::Scope scope(&lockBuffer);

                vehicle->transform(&buffer);

                dashee::Log::info(
                    4, 
                    "P:%3d R:%3d Y:%3d T:%3d", 
                    vehicle->getPitch(), 
                    vehicle->getRoll(), 
                    vehicle->getYaw(), 
                    vehicle->getThrottle()
                );
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
