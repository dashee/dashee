/**
 * @file include/dashee/Hardware/ServoController.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_SERVOCONTROLLER_H_
#define DASHEE_HARDWARE_SERVOCONTROLLER_H_

#include <vector>

#include <dashee/Log.h>
#include <dashee/Exception/OutOfBounds.h>
#include <dashee/Hardware/Exception/ServoController.h>
#include <dashee/Hardware/Servo.h>

namespace dashee
{
    namespace Hardware
    {
        class ServoController;
    }
}

/** 
 * ServoController abstraction.
 *
 * This class, holds a vector of our servo's. 
 * It allows you to interface with individual servo's, and this 
 * class holds the file descriptor to the device of servo's
 *
 * ServoController cannot be initiated and must be derived, It is up to 
 * the derived class to populate the @p servos variable. Cleanup of servos 
 * should be left to this class. Doing it in the base class, will work 
 * efficiently as this class will have no pointers to delete.
 *
 * This class's main job is to open the handle to our device, and send the 
 * read-write commands to our Servo class, which is stored in our servos
 */
class dashee::Hardware::ServoController
{   
private:

protected:
        
    /**
     * The device filename.
     *
     * This variable is set during the construct
     * It represents the textual format of the file currently open
     * Great for debugging purposes. And as this class is called once
     * this should only be set once, so it wont add a performance hit on runtime
     * unless the object is being created every time
     */
    const char * dev;

    /** 
     * List of Servo's.
     *
     * List of Uninitialized servos, as a vector. This vector is initialized
     * in the derived classes,
     */
    std::vector<Servo *> servos;
    
    // Set the @dev
    explicit ServoController(const char *);

public:
    
    // Given a channel number, set its given target
    virtual void setTarget(
            const unsigned short int channel, 
            unsigned short int target
        );
    virtual unsigned short int getTarget(
            const unsigned short int channel
        ) const;

    // Check weather or not the value is inverted
    bool isInverted(const unsigned short int channel) const;

    // Set the invert value
    void invert(const unsigned short int channel, const bool value);
    
    // Return the servo represented by the channel
    Servo & getServo(
            const unsigned short int channel
        );
    Servo & operator[](const size_t channel);
    
    // Get the error
    virtual short int getError() const = 0;
    
    // Get the channel size
    size_t size() const;
    
    // Delete and empty our @servo's array
    virtual ~ServoController();
};

#endif
