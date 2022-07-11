#pragma once

#include "TimeAlgo.hpp"

class DriveMotor : public TimeAlgo
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        DriveMotor();
        //Destructor declaration
        ~DriveMotor();

        /* ***********************
         * Types
         * **********************/

        typedef enum MotorState
        {
            stop = 0, //motor is at 0V
            accel, //increase motor speed
            coast //maintain motor speed
        };

        typedef enum MotorDir
        {
            forward = 0, //car is going forward
            reverse //car is going backwards
        };

        /* ***********************
         * Public Member Functions
         * **********************/
        
        void UserInput(bool forwardButton, bool revButton);
        void DriveMotorRuntime(unsigned int timeMS);
        void SetMotorSpeed();

    private:
        MotorState currentState;
        int currentPercent;
        MotorDir direction;

        const int accelRate = 3000;
        const int maxVoltage = 5;
};