#include "FrLight.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

FrLight::FrLight()
{

}

FrLight::~FrLight()
{
    
}

/* ***********************
 * Public Member Functions
 * **********************/

void FrLight::SetState(eLightState newState)
{
    switch(newState)
    {
        case eLSFlasher:
            SetRamp(0,100, 200); //200 = 0.2 seconds
            SetGPIOPinVoltage(0); //turn off voltage
            break;

        case eLSOff:
        case eLSOn:
        case eLSIndicator:
        case eLSConfig:
        case eLSError:
        default:
            //Use SetState() from parent class
            Light::SetState(newState);
            break;
    }
}