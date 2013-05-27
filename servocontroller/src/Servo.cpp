#include "Servo.h"

/** 
 * Initiate the Servo's defaults, fallback and current
 * structs to be set to 0, and also set the channel
 *
 * @param (const unsigned short int)channel - The channel that this servo belongs to
 */
Servo::Servo(const unsigned short int channel)
{
    this->channel = channel;
    
    // Reset all values to 0;   
    memset(&defaults, 0, sizeof(defaults));
    memset(&fallbacks, 0, sizeof(fallbacks));
    memset(&current, 0, sizeof(current));
    memset(&fallbackEnabled, 0, sizeof(fallbackEnabled));
}

/**
 * This function takes the number 0-100, and converts it into servo
 * frequency value, represented from 3968-8000, It does a check weather or not
 * the value falls between the range of 0-100, if not it throws an exception
 *
 * @param (short int &)target - The target represented in 0-100
 *
 * @throw Exception_Servo - If the target is out of range
 */
void Servo::PercentageToTarget(unsigned short int & target)
{
    const int zero = 3968;
    const int hundred = 8000;
    const int difference = 4032; //zero-hundred

    if (target >= 0 && target <= 100)
    {
        // If it is 0, set to 0% value
        if (target == 0) 
            target = zero;

        // Other wise set to 100% value
        else if (target == 100)
            target = hundred;

        // Other wise get a percentage number between the range
        // 3968-8000, Note that for calculations sake we calculate from 0-4032
        // then add 3968, to get the correct value
        else
            target = ((difference/100) * target) + zero;
    }
    else
        throw Exception_Servo("Invalid Target!\n");
}

/** 
 * This function takes a value between 3968-8000 and converts it into
 * percentage such as 0-100. It is the oposite of the function above
 *
 * @param (short int &)target - The target represented in 0-100
 *
 * @throw Exception_Servo - If the target is out of range
 */
void Servo::TargetToPercentage(unsigned short int & target)
{
    const int zero = 3968;
    const int difference = 4032;
        
    // If the target is lower than the zero value
    // Quite Probebly an invalid channel
    if (target < zero) 
        throw Exception_Servo("Channel returned low voltage, meaning it is invalid!");
        
    // Zero the target
    target = target - zero;
    
    target = (target / difference) * 100;
}

/** 
 * This function will set the Target, Speed and Acceleration
 * to fallback mode, only if fallbackEnabled allows it.
 */
void Servo::fallback()
{
    current.target = getTarget();
    //current.speed = getSpeed();
    //current.acceleration = getAcceleration();

    if (fallbackEnabled.target) 
        setTarget(fallbacks.target);
    //if (fallbackEnabled.speed) 
        //setSpeed(fallbacks.speed);
    //if (fallbackEnabled.acceleration) 
        //setAcelleration(fallbacks.acceleration);
}

/** 
 * This function will set the Target, Speed and Acceleration
 * back to its last known current position, The reversion is only
 * run if the fallbackEnabled.target value is enabled. If it was disabled
 * then we didnt fallback, hense we dont need to revert
 */
void Servo::revert()
{
    // Convert the Target value to percentage
    unsigned short int percentage_target = current.target;
    TargetToPercentage(percentage_target);
    
    if (fallbackEnabled.target)
        setTarget(percentage_target);
    //if (fallbackEnabled.speed) 
        //setSpeed(current.speed);
    //if (fallbackEnabled.acceleration) 
        //setAcelleration(current.acceleration);
}
