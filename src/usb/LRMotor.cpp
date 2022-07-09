#include "LRMotor.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

LRMotor::LRMotor()
{
    currentState = hold;
    turnRate = 1;
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
                        break;
                }
            }
        }

        void LRMotor::SetTurnRate(unsigned int newTurnRate)
        {
            turnRate = newTurnRate;
        }

        void LRMotor::LRMotorRuntime(unsigned int timeMS)
        {
            if (TimeAlgo::IsRampEnabled())
            {
                voltagePercent = UpdateRamp(timeMS);
            }
    
        }
