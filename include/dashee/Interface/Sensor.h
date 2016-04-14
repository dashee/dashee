/**
 * @file include/dashee/Hardware/Sensor.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_INTERFACE_SENSOR_H_
#define DASHEE_INTERFACE_SENSOR_H_

namespace dashee
{
    namespace Interface
    {
	class Sensor;
    }
}

/**
 * Class that holds the interface for our Accelerometer
 */
class dashee::Interface::Sensor
{
public:

    // Update the value of this class from the sensor
    virtual void update() = 0;
};

#endif
