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
        virtual void setState(eLightState newState);
        //overriden by child classes to update timeAlgo
        virtual void lightRuntime();

        //Called from any child class to set gpioPin
        void assignGPIOPin();

        //Called from any child class to set the assigned gpioPin to a percent of 
        void setGPIOPinVoltage(int percent);
        
    private:
        int gpioPin;
        int maxVoltage;
};