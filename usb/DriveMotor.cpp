#include "DriveMotor.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

DriveMotor::DriveMotor()
{
    currentState = stop;
    currentPercent = 0;
    direction = forward;
}

DriveMotor::~DriveMotor()
{
    
}

/* ***********************
 * Public Member Functions
 * **********************/

void DriveMotor::UserInput(bool forwardButton, bool revButton)
{
    //Accept new state input
    switch (currentState)
    {
        case stop:
            if (forwardButton)
            {
                //go into accel state, which will update the motor next scan
                //if direction was set to reverse, update direction to forward
                currentState = accel;
                direction = forward;
            }
            else if (revButton)
            {
                //go into accel state, which will update the motor next scan
                //switch direction
                currentState = accel;
                direction = reverse;
            }
            break;

        case accel:
            //external controller has a forward button and reverse/slowdown button
            if (forwardButton)
            {
                if (direction == forward)
                {
                    //speed up
                    TimeAlgo::SetRamp(currentPercent, 100, accelRate);
                }
                else
                {
                    //slow down
                    TimeAlgo::SetRamp(currentPercent, 0, accelRate);
                }
            }
            else if (revButton)
            {
                if (direction == forward)
                {
                    //slow down
                    TimeAlgo::SetRamp(currentPercent, 0, accelRate);
                }
                else
                {
                    //speed up
                    TimeAlgo::SetRamp(currentPercent, 100, accelRate);
                }
            }
            else
            {
                //no acceleration, go into coast state
                currentState = coast;
            }
            
            break;

        case coast:
        default:
            //Disable ramp
            TimeAlgo::SetRamp(0, 0, 0);
            break;
    }
}

void DriveMotor::DriveMotorRuntime(unsigned int timeMS)
{
    if (TimeAlgo::IsRampEnabled())
    {
        //Get current percent of the ramp completion.  Keep as class var, in case we change state
        currentPercent = UpdateRamp(timeMS);
        SetMotorSpeed();

        if (currentPercent == 0)
        {
            currentState = stop;
        }
    }
}

void DriveMotor::SetMotorSpeed()
{
    //input: currentPercent, maxVoltage
    float setVoltage;

    //Apply currentPercent to voltage output
    setVoltage = (float)maxVoltage * (float)currentPercent / 100.0f;
    
    //Adjust for direction
    if (direction == reverse)
    {
        setVoltage *= -1.0f;
    }

    //TODO set output voltage
}

