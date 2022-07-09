#include "Light.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

Light::Light()
{
    currentState = eLSOff;
}

Light::~Light()
{
    
}

/* ***********************
 * Public Member Functions
 * **********************/

void Light::SetState(eLightState newState)
{
    if (newState != currentState)
    {
        switch(newState)
        {
            case eLSOff:
                SetRamp(0,0,0); //disables the ramp in TimeAlgo
                SetGPIOPinVoltage(0); //turn off voltage
                break;

            case eLSOn:
                SetRamp(0,0,0); //disables the ramp in TimeAlgo
                SetGPIOPinVoltage(100); //turn on voltage
                break;

            case eLSIndicator:
                SetRamp(0,0,0); //disables the ramp in TimeAlgo
                SetGPIOPinVoltage(0); //turn off voltage
                break;

            case eLSConfig:
                SetRamp(0,50,1000); //1000 = 1 second
                SetGPIOPinVoltage(0); //turn off voltage
                break;

            case eLSError:
            default:
                SetRamp(0,100,500); //500 = 0.5seconds
                SetGPIOPinVoltage(0); //turn off voltage
                break;
        }
    }
}

void Light::LightRuntime(unsigned int timeMS)
{
    int voltagePercent;

    if (TimeAlgo::IsRampEnabled())
    {
        //Ramp related code, only run if in appropriate light state
        voltagePercent = UpdateRamp(timeMS);
        SetGPIOPinVoltage(voltagePercent);
    }

}

void Light::AssignGPIOPin(int pinNum)
{
    gpioPin = pinNum;
}

void Light::SetGPIOPinVoltage(int percent)
{

}