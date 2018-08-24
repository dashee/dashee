#include <dashee/Vehicle.h>

using namespace dashee;

/**
 * Construct the Vehicle with params.
 *
 * Set servoController and server variables
 *
 * @param servoController The pointer to the controller
 * @param config The pointer to the configuration file
 */
Vehicle::Vehicle(
	dashee::Hardware::ServoController * servoController, 
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

    this->setPitch(128);
    this->setRoll(128);
    this->setYaw(128);
    this->setThrottle(0);

    this->setPitchChannel(1);
    this->setRollChannel(2);
    this->setYawChannel(3);
    this->setThrottleChannel(4);

    if (config != NULL)
        this->loadFromConfig(config);
}

/**
 * Set a control value.
 *
 * Helpful to move the set function in one so set setYaw/setRoll/setPitch 
 * and setThrottle can be tied into one function.
 *
 * Note if the fallbackMode is enabled then we don't change the model
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
    if (target > 255)
        throw ExceptionVehicle(
                "Control value cannot be out the range of 0-255"
            );

    control = target;
}

/**
 * Set the control trim value.
 *
 * This is a helpful function which allows to change the trim value
 * of major control surfaces, as their validation logic is the same, we same
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

    if (config->isKeySet("pitch-channel"))
        this->setPitchChannel(config->getUInt("pitch-channel"));
    if (config->isKeySet("roll-channel"))
        this->setRollChannel(config->getUInt("roll-channel"));
    if (config->isKeySet("yaw-channel"))
        this->setYawChannel(config->getUInt("yaw-channel"));
    if (config->isKeySet("throttle-channel"))
        this->setThrottleChannel(config->getUInt("throttle-channel"));
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
unsigned short int Vehicle::getPitch(bool notrim) const
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
unsigned short int Vehicle::getRoll(bool notrim) const
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
unsigned short int Vehicle::getYaw(bool notrim) const
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
unsigned short int Vehicle::getThrottle(bool notrim) const
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
 * Set the pitch Servo channel.
 *
 * @param channel The value of the channel to set
 *
 * @throws ExceptionVehicle if channel is outside the constraints of the servoc
 *  controller
 */
void Vehicle::setPitchChannel(const unsigned short int channel)
{
    if (channel > this->servoController->size())
        throw ExceptionVehicle("The pitch channel is invalid");

    this->pitchChannel = channel;
}

/**
 * Get the yaw channel.
 *
 * @returns yaw channel.
 */
unsigned short int Vehicle::getPitchChannel() const
{
    return this->pitchChannel;
}

/**
 * Set the roll Servo channel.
 *
 * @param channel The value of the channel to set
 *
 * @throws ExceptionVehicle if channel is outside the constraints of the servoc
 *  controller
 */
void Vehicle::setRollChannel(const unsigned short int channel)
{
    if (channel > this->servoController->size())
        throw ExceptionVehicle("The roll channel is invalid");

    this->rollChannel = channel;
}

/**
 * Get the roll channel.
 *
 * @returns roll channel.
 */
unsigned short int Vehicle::getRollChannel() const
{
    return this->rollChannel;
}

/**
 * Set the yaw Servo channel.
 *
 * @param channel The value of the channel to set
 *
 * @throws ExceptionVehicle if channel is outside the constraints of the servoc
 *  controller
 */
void Vehicle::setYawChannel(const unsigned short int channel)
{
    if (channel > this->servoController->size())
        throw ExceptionVehicle("The yaw channel is invalid");

    this->yawChannel = channel;
}

/**
 * Get the yaw channel.
 *
 * @returns yaw channel.
 */
unsigned short int Vehicle::getYawChannel() const
{
    return this->yawChannel;
}

/**
 * Set the throttle Servo channel.
 *
 * @param channel The value of the channel to set
 *
 * @throws ExceptionVehicle if channel is outside the constraints of the servoc
 *  controller
 */
void Vehicle::setThrottleChannel(const unsigned short int channel)
{
    if (channel > this->servoController->size())
        throw ExceptionVehicle("The throttle channel is invalid");

    this->throttleChannel = channel;
}

/**
 * Get the throttle channel.
 *
 * @returns throttle channel.
 */
unsigned short int Vehicle::getThrottleChannel() const
{
    return this->throttleChannel;
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
signed short int Vehicle::getPitchTrim() const
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
signed short int Vehicle::getRollTrim() const
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
signed short int Vehicle::getYawTrim() const
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
signed short int Vehicle::getThrottleTrim() const
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
unsigned short int Vehicle::getPitchFallback() const
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
unsigned short int Vehicle::getRollFallback() const
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
unsigned short int Vehicle::getYawFallback() const
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
unsigned short int Vehicle::getThrottleFallback() const
{
    return this->throttleFallback;
}   

/** 
 * Set the servoController
 *
 * @param servoController The pointer to the servoController
 */
void Vehicle::setServoController(
	dashee::Hardware::ServoController * servoController
    )
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
dashee::Hardware::ServoController * Vehicle::getServoController() const
{
    return this->servoController;
}

/**
 * Simple function to return the current fallbackMode.
 *
 * @retval TRUE the server is in fallback mode
 * @retval FALSE the server is not in fallback mode
 */ 
bool Vehicle::isFallback() const
{
    return this->fallbackMode;
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
 * Read from the queue and update our model
 *
 * @param buffer The std::queue holding our values.
 */
void Vehicle::read(Buffer<unsigned char> * buffer)
{
    while (!buffer->empty())
    {
        auto mode = static_cast<unsigned short int>(buffer->next());
        switch (mode) {
            case VEHICLE_MODE_CONTROL:
                // Set the yaw and throttle from the buffer
                this->setPitch(static_cast<unsigned short int>(buffer->next()));
                this->setRoll(static_cast<unsigned short int>(buffer->next()));
                this->setYaw(static_cast<unsigned short int>(buffer->next()));
                this->setThrottle(static_cast<unsigned short int>(buffer->next()));
                break;
            case VEHICLE_MODE_PARTYMODE:
                this->setYaw(0);
                break;
            default:
                dashee::Log::warning(4, "Invalid Ccommand %d", mode);
        }
    }
}

/**
 * This function sends its current state to the physical model
 */
void Vehicle::update()
{
    this->servoController->setTarget(
            this->getPitchChannel(),
            this->getPitch()
    );

    this->servoController->setTarget(
            this->getRollChannel(),
            this->getRoll()
    );

    this->servoController->setTarget(
            this->getYawChannel(),
            this->getYaw()
    );

    this->servoController->setTarget(
            this->getThrottleChannel(),
            this->getThrottle()
    );

    dashee::Log::info(
            4,
            "Updated vehicle to %3up %3ur %3uy %3ut",
            this->getPitch(),
            this->getRoll(),
            this->getYaw(),
            this->getThrottle()
    );
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
