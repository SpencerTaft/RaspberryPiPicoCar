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
        case eLSOff:
            SetRamp(0,0); //disables the ramp in TimeAlgo
            SetGPIOPinVoltage(0); //turn off voltage
            break;

        case eLSOn:
            SetRamp(0,0); //disables the ramp in TimeAlgo
            SetGPIOPinVoltage(100); //turn on voltage
            break;

        case eLSFlasher:
            SetRamp(0,100); //todo need duration
            SetGPIOPinVoltage(0); //turn off voltage
            break;

        case eLSIndicator:
            SetRamp(0,100); //todo need duration
            SetGPIOPinVoltage(0); //turn off voltage
            break;

        case eLSConfig:
            SetRamp(0,100); //todo need duration
            SetGPIOPinVoltage(0); //turn off voltage
            break;

        case eLSError:
        default:
            SetRamp(0,100); //todo need duration
            SetGPIOPinVoltage(0); //turn off voltage
            break;
    }
}