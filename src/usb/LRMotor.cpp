#include "LRMotor.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

LRMotor::LRMotor()
{
    currentState = hold;
}

LRMotor::~LRMotor()
{
    
}

/* ***********************
 * Public Member Functions
 * **********************/

void LRMotor::UpdateState(MotorState newState)
{
    if (newState != currentState)
    {
        if ((currentState == driveLeft) || (currentState == driveRight))
        {
            //a new state is attempting to be written while turning.  
            //First return to zero, then accept the input on a future cycle
            previousState = currentState;
            currentState = retZero;
            TimeAlgo::SetRamp(currentPercent, 0, turnRate);
        }
        else if (currentState == retZero)
        {
            //Stay in this state until the car is pointing straight before receiving input
            if (currentPercent == 0)
            {
                currentState = hold;
                SetRamp(0,0,0); //disables the ramp in TimeAlgo
            }
        }
        else
        {
            //Accept new state input
            switch (newState)
            {
                case hold:
                    SetRamp(0,0,0); //disables the ramp in TimeAlgo
                    break;
                
                case driveLeft:
                    TimeAlgo::SetRamp(0, 100, turnRate);
                    break;

                case driveRight:
                    TimeAlgo::SetRamp(0, 100, turnRate);
                    break;

                case retZero:
                default:
                    //retZero is a hidden state, do nothing
                    break;
            }
        }
    }
}

void LRMotor::LRMotorRuntime(unsigned int timeMS)
{
    if (TimeAlgo::IsRampEnabled())
    {
        //Get current percent of the ramp completion.  Keep as class var, in case we change state
        currentPercent = UpdateRamp(timeMS);
        SetMotorPosition(currentPercent);
    }
}

void LRMotor::SetMotorPosition(int percent)
{
    //inputs: percent (of ramp), motor state (left/right/retZero), maxTurnAngle
    //output is in degrees

    float turnDegrees;
    float outputDegrees;
    bool turnLeft = false; //if false, turn right
    MotorState state;

    //First figure out if we are turning left or right
    if (currentState == retZero)
    {
        state = previousState;
    }
    else
    {
        state = currentState;
    }

    //Turn percentage to degrees.  100% = maxTurnAngle degrees output
    //HW sets steering to be straight at 90 degrees. Left is 0, right is 180
    turnDegrees = (float)maxTurnAngle * percent / 100.0f;

    if (state == driveLeft)
    {
        //turn left, so subtract from 90 degrees rather than add to it
        turnDegrees *= -1.0f;
    }

    outputDegrees = 90 + turnDegrees;

    //todo set motor position to outputDegrees using API
}
