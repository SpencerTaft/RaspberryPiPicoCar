#include "TimeAlgo.hpp"

#pragma once

class Light : public TimeAlgo
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        Light();
        //Destructor declaration
        ~Light();

        /* ***********************
         * Types and Enums
         * **********************/

        typedef enum eLightState
        {
            eLSOff = 0,
            eLSOn,
            eLSFlasher,
            eLSIndicator,
            eLSConfig,
            eLSError
        };

        /* ***********************
         * Public Member Functions
         * **********************/

        //Overriden by child classes to allow different states
        virtual void SetState(eLightState newState);
        //overriden by child classes to update timeAlgo
        virtual void LightRuntime();

        //Called from any child class to set gpioPin
        void AssignGPIOPin();

        //Called from any child class to set the assigned gpioPin to a percent of 
        void SetGPIOPinVoltage(int percent);

    private:
        int gpioPin;
        int maxVoltage;
};