/** 
 * This class, holds a vector of our servo's. 
 * It allows you to interface with individual servo's, and this 
 * class holds the filedescriptor to the device of servo's
 *
 * ServoController cannot be initiated and must be derived, It is upto 
 * the derived class to populate the @servos variable. Cleanup of servos should be
 * left to this class. Doing it in the base class, will work effiecently as 
 * this class will have no pointers to delete.
 *
 * This class's main job is to open the handel to our device, and send the readwrite
 * commands to our Servo class, which is stored in our servos
 *
 * @author Shahmir Javaid
 */

#ifndef SERVOCONTROLLER_H_
#define SERVOCONTROLLER_H_

#include <vector>
#include <dashee/Log.h>

#include "Exception/ServoController.h"
#include "Exception/ServoController/OutOfBound.h"
#include "Servo.h"

class ServoController
{   
private:

protected:

    /** 
     * List of Uninitialized servos, as a vector. This vector is initialized
     * in the derived classes,
     */
    std::vector<Servo *> servos;
    
    /** 
     * This determines whather the controller is in fallback mode
     */
    int fallbackmode;
        
    /**
     * This variable is set during the construct
     * It represents the textual format of the file currently open
     * Great for debugging purposes. And as this class is called once
     * this should only be set once, so it wont add a performance hit on runtime
     * unless the object is being created every time
     */
    const char * dev;
    
    // Set the @dev
    explicit ServoController(const char *);

public:
    
    // Get the target of the given channel
    virtual unsigned short int getTarget(const unsigned short int channel);
    
    // Given a channel number, set its given target
    virtual void setTarget(const unsigned short int, unsigned short int);
    
    // Set the struct defaults.target and call setTarget
    virtual void setTargetDefault(const unsigned short int, unsigned short int);
    
    // Set the struct fallbacks.target
    virtual void setTargetFallback(const unsigned short int, unsigned short int);
    
    // Set the struct fallbacks.target
    virtual void setTargetFallbackEnabled(const unsigned short int, bool);
    
    // Call fallback on all servos
    virtual void fallback();
    
    // Revert all servo's back to original
    virtual void revert();
    
    // Get the error
    virtual short int getError() = 0;
    
    // Get the channel size
    virtual unsigned int size();
    
    // Delete and empty our @servo's array
    virtual ~ServoController();
};

#endif
