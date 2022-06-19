#pragma once

#include "TimeAlgo.hpp"

class LRMotor : public TimeAlgo
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        LRMotor();
        //Destructor declaration
        ~LRMotor();

        /* ***********************
         * Types
         * **********************/

        typedef enum MotorState
        {
            hold = 0, //no change to position, set motor to 0V
            driveLeft, //increase motor position: left
            driveRight, //increase motor position: right
            retZero //return motor position to zero, stay in this state until zero is achieved or driveLeft/driveRight
        };

        /* ***********************
         * Public Member Functions
         * **********************/
        
        void UpdateState(MotorState newState);
        void SetTurnRate(unsigned int newTurnRate);
        void LRMotorRuntime(void);


    private:
        MotorState currentState;

};