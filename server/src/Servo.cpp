#include "Servo.h"

/** 
 * Initiate the Servo's defaults, fallback and current
 * structs to be set to 0, and also set the channel
 *
 * @param channel - The channel that this servo belongs to
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
 * This function will set the defaults struct target value
 * and call setTarget() to actually move the servo
 *
 * @param target - The value of the target
 *
 * @throws Exception_Servo - If the value is greated than 100
 */
void Servo::setTargetDefault(unsigned short int target)
{
    if (target > 100)
        throw Exception_Servo("setTargetDefault: Invalid defaults.target, must be 0-100!\n");

    this->defaults.target = target;
    this->setTarget(target);
}

/**
 * Set the fallbacks.target struct value, and enables
 * the fallbackEnabled flag as an implicit rule
 *
 * @param target - The target to set to
 *
 * @throws Exception_Servo - If the value is greated than 100
 */
void Servo::setTargetFallback(unsigned short int target)
{
    if (target > 100)
        throw Exception_Servo("setTargetFallback: Invalid fallback.target, must be 0-100!\n");

    this->fallbacks.target = target;

    this->setTargetFallbackEnabled(true);
}

/**
 * Set our fallbackEnabled.target value
 *
 * @param enabled - The value
 */
void Servo::setTargetFallbackEnabled(bool enabled)
{
    this->fallbackEnabled.target = enabled;
}

/**
 * This function takes the number 0-100, and converts it into servo
 * frequency value, represented from 3968-8000, It does a check weather or not
 * the value falls between the range of 0-100, if not it throws an exception
 *
 * @param target - The target represented in 0-100
 *
 * @throw Exception_Servo - If the target is out of range
 */
void Servo::PercentageToTarget(unsigned short int * target)
{
    const unsigned short int zero = 3968;
    const unsigned short int hundred = 8000;
    const unsigned short int difference = 4032; //zero-hundred

    if (*target >= 0 && *target <= 100)
    {
        // If it is 0, set to 0% value
        if (*target == 0) 
            *target = zero;

        // Other wise set to 100% value
        else if (*target == 100)
            *target = hundred;

        // Other wise get a percentage number between the range
        // 3968-8000, Note that for calculations sake we calculate from 0-4032
        // then add 3968, to get the correct value
        //
        // The rounding and float conversions is important to ensure that
        // the converted values match up when setting to and from a percentage
        else
            *target = (unsigned short int)roundf( (((float)difference/100.0f) * (*target)) + zero );
    }
    else
        throw Exception_Servo("Invalid Target!\n");
}

/**
 * This is a wrapper around the pointer function to make
 * life easier
 *
 * @param target - The target represented in 0-100
 *
 * @returns unsigned short int - The target value in percentage
 */
unsigned short int Servo::PercentageToTarget(unsigned short int target)
{
    PercentageToTarget(&target);
    return target;
}

/** 
 * This function takes a value between 3968-8000 and converts it into
 * percentage such as 0-100. It is the oposite of the function above
 *
 * @param target - The target represented in 0-100
 *
 * @throw Exception_Servo - If the target is out of range
 */
void Servo::TargetToPercentage(unsigned short int * target)
{
    if (*target == 0)
        return;

    const unsigned short int zero = 3968;
    const unsigned short int difference = 4032;

    // If the target is lower than the zero value
    // Quite Probebly an invalid channel
    if (*target < zero) 
    {
        dashee::Log::warning(4, "target:%d, channel:%d, zero:%d", *target, this->channel, zero);
        throw Exception_Servo("Channel returned low voltage, meaning it is invalid!");
    }
    
    // Zero the target
    //
    // Float conversions and rounding ordering is important
    // to ensure that Precentage to/from is accurate
    *target = *target - zero;
    *target = (unsigned short int)roundf(((float)*target / difference) * 100.0f);
}

/** 
 * Wrapper around TargetToPercentage that returns the new value
 * rather than changing it.
 *
 * @param target - The target represented in 0-100
 *
 * @returns unsigned short int - The target value in percentage
 */
unsigned short int Servo::TargetToPercentage(unsigned short int target)
{
    TargetToPercentage(&target);
    return target;
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
    if (fallbackEnabled.target)
        setTarget(current.target);
    //if (fallbackEnabled.speed) 
        //setSpeed(current.speed);
    //if (fallbackEnabled.acceleration) 
        //setAcelleration(current.acceleration);
}
