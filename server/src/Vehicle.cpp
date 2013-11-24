#include <dashee/Vehicle.h>

using namespace dashee;

/**
 * Construct the Vehicle with params.
 *
 * Set servoController and server variables
 *
 * @param servoController The pointer to the controller
 * @param server The pointer to the server
 * @param config The pointer to the configuration file
 */
Vehicle::Vehicle(
	ServoController * servoController, 
	Config * config
    )
{
    this->fallbackMode = false;

    this->setServoController(servoController);

    this->pitchTrim = 0;
    this->rollTrim = 0;
    this->yawTrim = 0;
    this->throttleTrim = 0;
    
    this->pitchFallback = 128;
    this->rollFallback = 128;
    this->yawFallback = 128;
    this->throttleFallback = 0;
    
    this->pitchFallbackEnabled = true;
    this->rollFallbackEnabled = true;
    this->yawFallbackEnabled = true;
    this->throttleFallbackEnabled = true;

    this->setPitch(0);
    this->setRoll(128);
    this->setYaw(128);
    this->setThrottle(0);

    if (config != NULL)
        this->loadFromConfig(config);
}

/**
 * Set a control value.
 *
 * Helpfull to move the set function in one so set setYaw/setRoll/setPitch 
 * and setThrottle can be tied into one function.
 *
 * Note if the fallbackMode is enabled then we dont change the model
 * values. Its a clever way of keeping the original values of the model
 * before fallback was enabled
 *
 * @param control The control surface to set
 * @param target The target value of the control to set
 * 
 * @throws ExceptionVehicle if trim is less than 0 and greater than 255 as these
 *                        are invalid values
 */ 
void Vehicle::setControl(
	unsigned short int & control, 
	unsigned short int target
    )
{
    if (target < 0 || target > 255)
        throw ExceptionVehicle("Control value cannot be out the range of 0-255");

    control = target;
}

/**
 * Set the control trim value.
 *
 * This is a helpfull function which allows to chanage the trim value
 * of major control surfaces, as thier validation logic is the same, we same
 * some space by combining it into one function
 * 
 * @param controlTrim The control surface who's trim to set
 * @param trim The trim value of the control to set
 *
 * @throws ExceptionVehicle if trim is less than -128 and greater than 128 as 
 *                        these are invalid values
 */
void Vehicle::setControlTrim(
        signed short int & controlTrim, 
        signed short int trim
    )
{
    if (trim < -128 || trim > 128)
        throw ExceptionVehicle(
                "Control trim value cannot be out the range of -128-128"
            );

    controlTrim = trim;
}

/**
 * Load from a config class.
 *
 * @param config Pointer to the configuration
 *
 * @throws ExceptionVehicle When config is invalid
 */
void Vehicle::loadFromConfig(Config * config)
{
    if (config == NULL)
        throw new ExceptionVehicle("Cannot load from model as config is null");

    // Set the defaults
    if  (config->isKeySet("pitch"))
        this->setPitch(config->getUInt("pitch"));
    if  (config->isKeySet("roll"))
        this->setRoll(config->getUInt("roll"));
    if  (config->isKeySet("yaw"))
        this->setYaw(config->getUInt("yaw"));
    if  (config->isKeySet("throttle"))
        this->setThrottle(config->getUInt("throttle"));

    // Set the fallbacks
    if  (config->isKeySet("pitch-fallback"))
        this->setPitchFallback(config->getUInt("pitch-fallback"));
    if  (config->isKeySet("roll-fallback"))
        this->setRollFallback(config->getUInt("roll-fallback"));
    if  (config->isKeySet("yaw-fallback"))
        this->setYawFallback(config->getUInt("yaw-fallback"));
    if  (config->isKeySet("throttle-fallback"))
        this->setThrottleFallback(config->getUInt("throttle-fallback"));
}

/**
 * Set the pitch.
 *
 * @param value The value of 0 to 255
 */
void Vehicle::setPitch(unsigned short int value)
{
    this->setControl(this->pitch, value);
}

/**
 * Get the pitch.
 *
 * @param notrim If set to true, the raw value is returned
 *
 * @returns the pitch value
 */ 
unsigned short int Vehicle::getPitch(bool notrim)
{
    if (notrim)
        return this->pitch;

    return dashee::constrain(
            this->pitch - this->pitchTrim, 
            0, 
            255
        );
}

/**
 * Set the roll.
 *
 * @param value The value of 0 to 255
 */
void Vehicle::setRoll(unsigned short int value)
{
    this->setControl(this->roll, value);
}

/**
 * Get the roll.
 *
 * @param notrim If set to true, the raw value is returned
 *
 * @returns the roll value
 */ 
unsigned short int Vehicle::getRoll(bool notrim)
{
    if (notrim)
        return this->roll;
    
    return dashee::constrain(
            this->roll - this->rollTrim, 
            0, 
            255
        );
}

/**
 * Set the yaw.
 *
 * @param value The value of 0 to 255
 */
void Vehicle::setYaw(unsigned short int value)
{
    this->setControl(this->yaw, value);
}

/**
 * Get the yaw.
 *
 * @param notrim If set to true, the raw value is returned
 *
 * @returns the yaw value
 */ 
unsigned short int Vehicle::getYaw(bool notrim)
{
    if (notrim)
        return this->yaw;

    return dashee::constrain(
            this->yaw - this->yawTrim, 
            0, 
            255
        );
}

/**
 * Set the throttle.
 *
 * @param value The value of 0 to 255
 */
void Vehicle::setThrottle(unsigned short int value)
{
    this->setControl(this->throttle, value);
}

/**
 * Get the throttle.
 *
 * @param notrim If set to true, the raw value is returned
 *
 * @returns the throttle value
 */ 
unsigned short int Vehicle::getThrottle(bool notrim)
{
    if (notrim)
        return this->throttle;

    return dashee::constrain(
            this->throttle - this->throttleTrim, 
            0, 
            255
        );
}

/**
 * Set the pitch Trim
 * 
 * @param pitchTrim The trim value to set
 */
void Vehicle::setPitchTrim(signed short int pitchTrim)
{
    this->setControlTrim(this->pitchTrim, pitchTrim);
}

/**
 * Get the pitch trim value
 *
 * @returns the pitch trim
 */
signed short int Vehicle::getPitchTrim()
{
    return this->pitchTrim;
}   

/**
 * Set the Roll Trim
 * 
 * @param rollTrim The trim value to set
 */
void Vehicle::setRollTrim(signed short int rollTrim)
{
    this->setControlTrim(this->rollTrim, rollTrim);
}   

/**
 * Get the roll trim value
 *
 * @returns the roll trim
 */
signed short int Vehicle::getRollTrim()
{
    return this->rollTrim;
}   

/**
 * Set the Yaw Trim
 * 
 * @param yawTrim The trim value to set
 */
void Vehicle::setYawTrim(signed short int yawTrim)
{
    this->setControlTrim(this->yawTrim, yawTrim);
}   

/**
 * Get the yaw trim value
 *
 * @returns the yaw trim
 */
signed short int Vehicle::getYawTrim()
{
    return this->yawTrim;
}   

/**
 * Set the Throttle Trim
 * 
 * @param throttleTrim The trim value to set
 */
void Vehicle::setThrottleTrim(signed short int throttleTrim)
{
    this->setControlTrim(this->throttleTrim, throttleTrim);
}   

/**
 * Get the throttle trim value
 *
 * @returns the throttle trim
 */
signed short int Vehicle::getThrottleTrim()
{
    return this->throttleTrim;
}   

/**
 * Set the Pitch Fallback.
 *
 * @param value The value of the fallback 0-255
 */
void Vehicle::setPitchFallback(unsigned short int value)
{
    this->setControl(this->pitchFallback, value);
}

/**
 * Get the Pitch fallback value
 *
 * @returns the pitch fallback
 */
unsigned short int Vehicle::getPitchFallback()
{
    return this->pitchFallback;
}   

/**
 * Set the Roll Fallback.
 *
 * @param value The value of the fallback 0-255
 */
void Vehicle::setRollFallback(unsigned short int value)
{
    this->setControl(this->rollFallback, value);
}

/**
 * Get the Roll fallback value
 *
 * @returns the roll fallback
 */
unsigned short int Vehicle::getRollFallback()
{
    return this->rollFallback;
}   

/**
 * Set the Yaw Fallback.
 *
 * @param value The value of the fallback 0-255
 */
void Vehicle::setYawFallback(unsigned short int value)
{
    this->setControl(this->yawFallback, value);
}

/**
 * Get the Yaw fallback value
 *
 * @returns the Yaw fallback
 */
unsigned short int Vehicle::getYawFallback()
{
    return this->yawFallback;
}   

/**
 * Set the throttle Fallback.
 *
 * @param value The value of the fallback 0-255
 */
void Vehicle::setThrottleFallback(unsigned short int value)
{
    this->setControl(this->throttleFallback, value);
}

/**
 * Get the Throttle fallback value
 *
 * @returns the Throttle fallback
 */
unsigned short int Vehicle::getThrottleFallback()
{
    return this->throttleFallback;
}   

/** 
 * Set the servoController
 *
 * @param servoController The pointer to the servoController
 */
void Vehicle::setServoController(ServoController * servoController)
{
    if (servoController == NULL)
        throw ExceptionVehicle("ServoController cannot be null");
    this->servoController = servoController;
}

/**
 * Return the pointer to the servoController.
 *
 * @returns Pointer to the servoController object
 */
ServoController * Vehicle::getServoController()
{
    return this->servoController;
}

/**
 * Simple function to return the current fallbackMode.
 *
 * @retval TRUE the server is in fallback mode
 * @retval FALSE the server is not in fallback mode
 */ 
bool Vehicle::isFallback()
{
    return this->fallbackMode;
}

/**
 * Transform the physical model.
 *
 * Before transforming check the value of our 
 * pointers server and servoController, if all is good
 * revert() before continuing
 *
 * @param server The server to transform from
 */
void Vehicle::transform(Server * server)
{
    if (server == NULL)
        throw ExceptionVehicle(
                "Cannot transform model as Server is not set"
            );
    if (this->servoController == NULL)
        throw ExceptionVehicle(
                "Cannot transform model as ServoController is not set"
            );

    this->revert();
}

/**
 * Initiate fallback.
 *
 * If we are already in fallback mode return out
 * otherwise set the fallback.
 */
void Vehicle::fallback()
{
    if (this->fallbackMode)
        return;

    // This is important, when this is set to 
    // true the actual value of pitch/roll/yaw and throttle
    // will not change in this model
    //
    // @see this->setControl(...);
    this->fallbackMode = true;

    if (this->pitchFallbackEnabled)
        this->setPitch(this->pitchFallback);

    if (this->rollFallbackEnabled)
        this->setRoll(this->rollFallback);

    if (this->yawFallbackEnabled)
        this->setYaw(this->yawFallback);

    if (this->throttleFallbackEnabled)
        this->setThrottle(this->throttleFallback);
}

/**
 * Initiate revert from fallback.
 *
 * Note without fallback initiated this will
 * do nothing.
 */
void Vehicle::revert()
{
    this->fallbackMode = false;
}

/**
 * Destruct
 */
Vehicle::~Vehicle()
{

}
