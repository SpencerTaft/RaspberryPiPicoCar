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
        void LRMotorRuntime(unsigned int timeMS);
        //This function takes the the ramp output + motor state and converts it to a position to set the motor to in degrees
        void SetMotorPosition (int percent);


    private:
        MotorState currentState;
        int currentPercent;
        MotorState previousState;
        
        const unsigned int maxTurnAngle = 10; //specific to model car and physical wheel well, in degrees
        const unsigned int turnRate = 1000; //how fast the wheels ramp from straight to turned, in ms

};