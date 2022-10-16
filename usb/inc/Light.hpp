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
        virtual void LightRuntime(unsigned int timeMS);
        //Called from any child class to set gpioPin
        void AssignGPIOPin(int pinNum);
        //Called to set max voltage for pin, in volts
        void setMaxVoltage(float newVal);
        //Called from any child class to set the assigned gpioPin
        void SetGPIOPinVoltage(int percent);

    private:
        int gpioPin;
        float maxVoltage;
        eLightState currentState;
};