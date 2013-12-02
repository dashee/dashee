#include "threads.h"

// Define our locks
dashee::Threads::LockReadWrite lockSensor = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite lockVehicle = dashee::Threads::LockReadWrite();
dashee::Threads::LockMutex lockBuffer = dashee::Threads::LockMutex();

// Define our thread shared globals
std::queue<unsigned char> buffer = std::queue<unsigned char>();

/**
 * Loop through calling read and reading from the server.
 *
 * The read should handle SIGTERM so no timeout should be required.
 *
 * @param server The pointer to the Server object
 *
 * @returns Nothing
 */
void * threadReadFromServer(void * s)
{
    // Cast our pointer
    dashee::Server * server = reinterpret_cast<dashee::Server *>(s);

    try
    {
        while(!dashee::EXIT)
        {
            if (server->read())
            {
                lockBuffer.lock();

                // Only add to our buffer, if we have less than 100
                // commands to deal with, 
                if (buffer.size() < 100)
                {
                    for (size_t x = 0; x < server->size(); x++)
                    {
                        buffer.push(server->getBufferByte(x));
                    }
                }
                
                lockBuffer.unlock();
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

        // Just incase! an exception is thrown
        lockBuffer.unlock();
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
    dashee::Vehicle * vehicle = reinterpret_cast<dashee::Vehicle *>(v);

    try
    {
        while(!dashee::EXIT)
        {
            lockBuffer.lock();

            vehicle->transform(&buffer);

            dashee::Log::info(
                4, 
                "P:%3d R:%3d Y:%3d T:%3d", 
                vehicle->getPitch(), 
                vehicle->getRoll(), 
                vehicle->getYaw(), 
                vehicle->getThrottle()
            );

            lockBuffer.unlock();

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
        
        // Just incase the value is not good
        lockBuffer.unlock();
    }

    dashee::Threads::Thread::exit();
    return NULL;
}
