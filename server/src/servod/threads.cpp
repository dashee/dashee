#include "threads.h"

/**
 * Lock our sensor when reading.
 */
dashee::Threads::LockReadWrite lockReadSensor 
    = dashee::Threads::LockReadWrite();

/**
 * Lock our sensor when writing.
 */
dashee::Threads::LockReadWrite lockWriteSensor 
    = dashee::Threads::LockReadWrite(
            dashee::Threads::LockReadWrite::LOCKTYPE_WRITE
        );

/**
 * Lock our vehicle for updating
 */
dashee::Threads::LockReadWrite lockWriteVehicle 
    = dashee::Threads::LockReadWrite(
            dashee::Threads::LockReadWrite::LOCKTYPE_WRITE
        );

/**
 * Loop through calling read and reading from the server.
 *
 * The read should handle SIGTERM so no timeout should be required.
 *
 * @param server The pointer to the Server object
 *
 * @returns Nothing
 */
void * threadReadFromServer(void * server)
{
    try
    {
        while(!dashee::EXIT)
        {
            dashee::Log::info(3, "Server Step");
            dashee::sleep(100000);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromServer failed as Exception thrown: %s", 
                ex.what()
            );

        // send a signal to the current process. Stopping every thing
        kill(0, SIGTERM);
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
            dashee::Log::info(3, "Sensor Step");
            dashee::sleep(100000);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromServer failed as Exception thrown: %s", 
                ex.what()
            );

        // send a signal to the current process. Stopping every thing
        kill(0, SIGTERM);
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
 * @param sensor The pointer to the SensorIMU
 *
 * @returns Nothing
 */
void * threadStepController(void *)
{
    try
    {
        while(!dashee::EXIT)
        {
            dashee::Log::info(3, "Controller Step");
            dashee::sleep(100000);
        }
    }
    catch (dashee::Exception ex)
    {
        dashee::Log::error(
                "threadReadFromServer failed as Exception thrown: %s", 
                ex.what()
            );

        // send a signal to the current process. Stopping every thing
        kill(0, SIGTERM);
    }

    dashee::Threads::Thread::exit();
    return NULL;
}
