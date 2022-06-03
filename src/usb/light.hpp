
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

        enum eLightState
        {
            eLSOff = 0,
            eLSOn,
            eLSFlasher,
            eLSIndicator,
            eLSConfig,
            eLSError
        }

        /* ***********************
         * Public Member Functions
         * **********************/

        bool setIOPin();

        //turn on the GPIO pin
        virtual bool setState(eLightState newState);
        //turn on light at indicator interval
        void indicate();

};