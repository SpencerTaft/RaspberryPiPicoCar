
#pragma once

class RLight : public Light
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        RLight();
        //Destructor declaration
        ~RLight();

        /* ***********************
         * Public Member Functions
         * **********************/

        bool setFlasher();

        void setState(eLightState newState);

};