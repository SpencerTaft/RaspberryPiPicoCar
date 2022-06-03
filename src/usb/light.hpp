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

        //turn on the GPIO pin
        virtual void setState(eLightState newState);
};