#include <dashee/Servo.h>

using namespace dashee;

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
    memset(&this->defaults, 0, sizeof(this->defaults));
    memset(&this->fallbacks, 0, sizeof(this->fallbacks));
    memcpy(&this->lastknown, &this->defaults, sizeof(this->defaults));
    memset(&this->fallbackEnabled, 1, sizeof(this->fallbackEnabled));

    this->fallbackmode = false;
}

/**
 * Set the default value of the servo.
 *
 * This function will set the defaults struct target value
 * and call setTarget() to actually move the servo
 *
 * @param target - The value of the target
 *
 * @throws ExceptionServo - If the value is greated than 100
 */
void Servo::setTargetDefault(unsigned short int target)
{
    if (target > 100)
        throw ExceptionServo("setTargetDefault: Invalid defaults.target, must be 0-100!\n");

    this->defaults.target = target;
    this->setTarget(target);
}

/**
 * Get the Default target.
 *
 * @returns The default target value
 */
unsigned short int Servo::getTargetDefault()
{
    return this->defaults.target;
}

/**
 * Set the target fallback.
 *
 * Set the fallbacks.target struct value, and enables
 * the fallbackEnabled flag as an implicit rule
 *
 * @param target The target to set to
 *
 * @throws ExceptionServo If the value is greated than 100
 */
void Servo::setTargetFallback(unsigned short int target)
{
    if (target > 100)
        throw ExceptionServo("setTargetFallback: Invalid fallback.target, must be 0-100!\n");

    this->fallbacks.target = target;
    this->setTargetFallbackEnabled(true);
}

/**
 * Get the Target Fallback value.
 *
 * @returns The default target value
 */
unsigned short int Servo::getTargetFallback()
{
    return this->fallbacks.target;
}

/**
 * Set our fallbackEnabled.target value
 *
 * This should bomb out if the fallback mode is enabled, changing fallback
 * mode enabled to disable or vv while in fallback mode is a can of worms that
 * is worthless trying to patch, its better and more uniform to tell the user that
 * changing the fallbackEnabled value while in fallback is not good so revert before
 * changing the enabled value
 *
 * @param enabled The value to set
 *
 * @throws ExceptionServo If trying to change the value while fallback is enabled
 */
void Servo::setTargetFallbackEnabled(bool enabled)
{
    if (this->fallbackmode)
        throw ExceptionServo("Trying to change the value of FallbackEnabled when the servo is in fallback mode is not allowed, please call revert() before continuing");

    this->fallbackEnabled.target = enabled;
}

/**
 * Get the Target Fallback Enabled value.
 *
 * @returns The default fallback enabled value.
 * @retval TRUE If enabled
 * @retval FALSE if disabled
 */
bool Servo::getTargetFallbackEnabled()
{
    return this->fallbackEnabled.target;
}

/**
 * This function takes the number 0-100, and converts it into servo
 * frequency value, represented from 3968-8000, It does a check weather or not
 * the value falls between the range of 0-100, if not it throws an exception
 *
 * @param target The target represented in 0-100
 *
 * @throw ExceptionServo If the target is out of range
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
        throw ExceptionServo("Invalid Target!\n");
}


/**
 * This is a wrapper around the pointer function to make
 * life easier
 *
 * @param target The target represented in 0-100
 *
 * @returns The target value in percentage
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
 * @param target The target represented in 0-100
 *
 * @throw ExceptionServo If the target is out of range
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
        throw ExceptionServo("Channel returned low voltage, meaning it is invalid!");
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
 * @param target The target represented in 0-100
 *
 * @returns The target value in percentage
 */
unsigned short int Servo::TargetToPercentage(unsigned short int target)
{
    TargetToPercentage(&target);
    return target;
}

/**
 * Is the servo in fallbackmode
 *
 * @returns weather or not the servo is in fallback mode
 * @retval TRUE is in fallbackmode
 * @retval FASE is not in fallbackmode
 */
bool Servo::isFallback()
{
    return this->fallbackmode;
}

/** 
 * Send servo's to fallback mode.
 *
 * This function will set the Target, Speed and Acceleration
 * to fallback mode, only if fallbackEnabled allows it.
 */
void Servo::fallback()
{
    // already in fallback mode, so no point doing
    // it again
    if (this->fallbackmode) return;

    this->lastknown.target = this->getTarget();
    //current.speed = getSpeed();
    //current.acceleration = getAcceleration();

    if (this->fallbackEnabled.target) 
        this->setTarget(this->fallbacks.target);
    //if (fallbackEnabled.speed) 
        //setSpeed(fallbacks.speed);
    //if (fallbackEnabled.acceleration) 
        //setAcelleration(fallbacks.acceleration);
    
    this->fallbackmode = true;
}

/** 
 * Revert the Servo.
 *
 * This function will fallback target, speed and acceleration
 * only if their fallbackEnabled counterpart is set to true
 *
 * And there is no point running this function if we are not in 
 * fallback mode
 */
void Servo::revert()
{
    // Note in fallback mode so no point reverting
    if (!this->fallbackmode) return;

    if (this->fallbackEnabled.target)
        this->setTarget(this->lastknown.target);
    //if (fallbackEnabled.speed) 
        //setSpeed(current.speed);
    //if (fallbackEnabled.acceleration) 
        //setAcelleration(current.acceleration);
    
    this->fallbackmode = false;
}
