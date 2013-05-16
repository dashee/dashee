#include "Servo.h"

Servo::Servo(const unsigned short int channel)
{
    this->channel = channel;

    defaults.target = 0;
    defaults.speed = 0;
    defaults.acceleration = 0;
    
    fallbacks.target = 0;
    fallbacks.speed = 0;
    fallbacks.acceleration = 0;
}

/**
 * This function takes the number 0-100, and converts it into servo
 * frequency value, represented from 3968-8000, It does a check weather or not
 * the value falls between the range of 0-100, if not it throws an exception
 *
 * @param (short int &)target - The target represented in 0-100
 *
 * TODO: Create its own exception 
 * @throw Exception_Servo - If the target is out of range
 */
void Servo::calculateTarget(unsigned short int & target)
{
    int zero = 3968;
    int hundred = 8000;
    int difference = 4032; //zero-hundred

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

void Servo::fallback()
{
    setTarget(fallbacks.target);
    //setSpeed(fallbacks.speed);
    //setAcelleration(fallbacks.acceleration);
}

void Servo::revert()
{
    setTarget(current.target);
    //setSpeed(current.speed);
    //setAcelleration(current.acceleration);
}
