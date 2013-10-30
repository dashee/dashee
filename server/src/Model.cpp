#include <dashee/Model.h>

using namespace dashee;

/**
 * Construct the Model with params.
 *
 * Set servoController and server variables
 *
 * @param servoController The pointer to the controller
 * @param server The pointer to the server
 */
Model::Model(
	ServoController * servoController, 
	Server * server, 
	Config * config
    )
{
    this->fallbackMode = false;

    this->setServoController(servoController);
    this->setServer(server);

    this->pitchTrim = 0;
    this->rollTrim = 0;
    this->yawTrim = 0;
    this->throttleTrim = 0;
    
    this->pitchFallback = 0;
    this->rollFallback = 0;
    this->yawFallback = 0;
    this->throttleFallback = 0;
    
    this->pitchFallbackEnabled = false;
    this->rollFallbackEnabled = false;
    this->yawFallbackEnabled = false;
    this->throttleFallbackEnabled = false;

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
 * @throws ExceptionModel if trim is less than 0 and greater than 255 as these
 *                        are invalid values
 */ 
void Model::setControl(unsigned short int & control, unsigned short int target)
{
    // Fallback is enabled so dont bother changing the model
    // control surface value
    if (this->fallbackMode)
        return;

    if (target < 0 || target > 255)
        throw ExceptionModel("Control value cannot be out the range of 0-255");

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
 * @param value The trim value of the control to set
 *
 * @throws ExceptionModel if trim is less than -128 and greater than 128 as these
 *                        are invalid values
 */
void Model::setControlTrim(signed short int & controlTrim, signed short int trim)
{
    // SAFTEY
    // For saftey we dont want to change the trim when in fallback mode
    // as in harsh cases, a user may accidently move the throttle to 50% while
    // in fallback mode, and revert will cause the control surface at 50%
    if (this->fallbackMode)
        return;

    if (trim < -128 || trim > 128)
        throw ExceptionModel("Control trim value cannot be out the range of -128-128");

    controlTrim = trim;
}

/**
 * Load from a config class.
 *
 * @param config Pointer to the configuration
 *
 * @throws ExceptionModel When config is invalid
 */
void Model::loadFromConfig(Config * config)
{
    if (config == NULL)
        throw new ExceptionModel("Cannot load from model as config is null");
}

/**
 * Set the pitch.
 *
 * @param value The value of 0 to 255
 */
void Model::setPitch(unsigned short int value)
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
unsigned short int Model::getPitch(bool notrim)
{
    if (notrim)
        return this->pitch;

    short int trimmedPitch = this->pitch - this->pitchTrim;
    if (trimmedPitch < 0)
       return 0u;
    else if (trimmedPitch > 255) 
        return 255u;
    return trimmedPitch;
}

/**
 * Set the roll.
 *
 * @param value The value of 0 to 255
 */
void Model::setRoll(unsigned short int value)
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
unsigned short int Model::getRoll(bool notrim)
{
    if (notrim)
        return this->roll;

    short int trimmedRoll = this->roll - this->rollTrim;
    if (trimmedRoll < 0)
       return 0u;
    else if (trimmedRoll > 255) 
        return 255u;
    return trimmedRoll;
}

/**
 * Set the yaw.
 *
 * @param value The value of 0 to 255
 */
void Model::setYaw(unsigned short int value)
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
unsigned short int Model::getYaw(bool notrim)
{
    if (notrim)
        return this->yaw;

    short int trimmedYaw = this->yaw - this->yawTrim;
    if (trimmedYaw < 0)
       return 0u;
    else if (trimmedYaw > 255) 
        return 255u;
    return trimmedYaw;
}

/**
 * Set the throttle.
 *
 * @param value The value of 0 to 255
 */
void Model::setThrottle(unsigned short int value)
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
unsigned short int Model::getThrottle(bool notrim)
{
    if (notrim)
        return this->throttle;

    short int trimmedThrottle = this->throttle - this->throttleTrim;
    if (trimmedThrottle < 0)
       return 0u;
    else if (trimmedThrottle > 255) 
        return 255u;
    return trimmedThrottle;
}

/**
 * Set the pitch Trim
 * 
 * @param pitchTrim The trim value to set
 */
void Model::setPitchTrim(signed short int pitchTrim)
{
    this->setControlTrim(this->pitchTrim, pitchTrim);
}   

/**
 * Set the Roll Trim
 * 
 * @param rollTrim The trim value to set
 */
void Model::setRollTrim(signed short int rollTrim)
{
    this->setControlTrim(this->rollTrim, rollTrim);
}   

/**
 * Set the Yaw Trim
 * 
 * @param yawTrim The trim value to set
 */
void Model::setYawTrim(signed short int yawTrim)
{
    this->setControlTrim(this->yawTrim, yawTrim);
}   

/**
 * Set the Throttle Trima
 * 
 * @param thottleTrim The trim value to set
 */
void Model::setThrottleTrim(signed short int throttleTrim)
{
    this->setControlTrim(this->throttleTrim, throttleTrim);
}   

/** 
 * Set the servoController
 *
 * @param servoController The pointer to the servoController
 */
void Model::setServoController(ServoController * servoController)
{
    if (servoController == NULL)
        throw ExceptionModel("ServoController cannot be null");
    this->servoController = servoController;
}

/**
 * Return the pointer to the servoController.
 *
 * @returns Pointer to the servoController object
 */
ServoController * Model::getServoController()
{
    return this->servoController;
}

/**
 * Set the server.
 *
 * @param server pointer to the server
 */
void Model::setServer(Server * server)
{
    if (server == NULL)
        throw ExceptionModel("Server cannot be null");
    this->server = server;
}

/**
 * Return the pointer to the server.
 *
 * @returns Pointer to the server object
 */
Server * Model::getServer()
{
    return this->server;
}

/**
 * Transform the physical model.
 *
 * Before transforming check the value of our 
 * pointers server and servoController, if all is good
 * revert() before continuing
 */
void Model::transform()
{
    if (server == NULL)
        throw ExceptionModel("Cannot transform model as Server is not set");
    if (servoController == NULL)
        throw ExceptionModel("Cannot transform model as ServoController is not set");

    this->revert();
}

/**
 * Initiate fallback.
 *
 * If we are already in fallback mode return out
 * otherwise set the fallback.
 */
void Model::fallback()
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
        this->setRoll(this->pitchFallback);

    if (this->yawFallbackEnabled)
        this->setYaw(this->yawFallback);

    if (this->throttleFallbackEnabled)
        this->setThrottle(this->throttle);
}

/**
 * Initiate revert from fallback.
 *
 * Note without fallback initiated this will
 * do nothing.
 */
void Model::revert()
{
    // Not point reverting as we were not
    // in fallback mode
    if (!this->fallbackMode)
        return;

    // If this is not disabled before reverting controll
    // surfaces then nothing will be set, set pitch/roll/yaw
    // and throttle will not do anything
    //
    // @see this->setControl(...);
    this->fallbackMode = false;

    this->setPitch(this->pitch);
    this->setRoll(this->roll);
    this->setYaw(this->yaw);
    this->setThrottle(this->throttle);
}

/**
 * Destruct
 */
Model::~Model()
{

}
