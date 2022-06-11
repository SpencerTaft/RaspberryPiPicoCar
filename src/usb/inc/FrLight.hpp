#include "Light.hpp"
#pragma once

class FrLight : public Light
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        FrLight();
        //Destructor declaration
        ~FrLight();

        /* ***********************
         * Public Member Functions
         * **********************/

        void SetState(eLightState newState);

        void LightRuntime();

};