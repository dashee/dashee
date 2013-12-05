#include "threads.h"

// Define our locks
dashee::Threads::LockReadWrite lockConfig = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockServer = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockServoController 
    = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockSensor = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockVehicle = dashee::Threads::LockReadWrite();
dashee::Threads::LockMutex lockBuffer = dashee::Threads::LockMutex();

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
        while(!dashee::EXIT)
        {
            if (server->read())
            {
                dashee::Threads::Scope scope(&lockBuffer);
 
                // Take the buffer   
                server->appendBufferTo(&buffer);

                // Remove any excess values, good to clean up incase this 
                // just keeps growing till the cows come home
                while (buffer.size() > 30) buffer.pop();
            }

            //dashee::Log::info(3, "Server Step");
            //dashee::sleep(100000);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromServer failed as Exception thrown: %s", 
                ex.what()
            );

        dashee::EXIT = 1;
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
        while(!dashee::EXIT)
        {
            //dashee::Log::info(3, "Sensor Step");
            dashee::sleep(100000);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromSensor failed as Exception thrown: %s", 
                ex.what()
            );
        
        dashee::EXIT = 1;
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
 * @param v The pointer to the SensorIMU
 *
 * @returns Nothing
 */
void * threadStepController(void * v)
{
    dashee::Vehicle * vehicle = static_cast<dashee::Vehicle *>(v);

    try
    {
        while(!dashee::EXIT)
        {
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

            dashee::sleep(20000);
        }
    }
    catch (dashee::Exception ex)
    {

        dashee::Log::error(
                "threadStepController failed as Exception thrown: %s", 
                ex.what()
            );

        dashee::EXIT = 1;
    }

    dashee::Threads::Thread::exit();
    return NULL;
}
