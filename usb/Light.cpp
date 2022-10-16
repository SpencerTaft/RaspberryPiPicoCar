#include "Light.hpp"
#include <stdio.h>
#include "pico/stdlib.h"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

Light::Light()
{
    currentState = eLSOff;
    TimeAlgo::SetBlink(true); //all lights use blink ramps(sawtooth waves), while motors don't
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
                SetRamp(0,50,1000000); //1000000 = 1 second
                SetGPIOPinVoltage(0); //turn off voltage
                break;

            case eLSError:
            default:
                SetRamp(0,100,500000); //500000 = 0.5seconds
                SetGPIOPinVoltage(0); //turn off voltage
                break;
        }

        currentState = newState;
    }
}

void Light::LightRuntime(unsigned int timeMS)
{
    int voltagePercent;

    if (TimeAlgo::IsRampEnabled())
    {
        //Ramp related code, only run if in appropriate light state
        voltagePercent = UpdateRamp(timeMS);
        printf("Current percent: %d", voltagePercent);
        SetGPIOPinVoltage(voltagePercent);
    }

}

void Light::AssignGPIOPin(int pinNum)
{
    gpioPin = pinNum;

    //Init for GPIO pin
    gpio_init(pinNum);
    gpio_set_dir(pinNum, GPIO_OUT);
}

void Light::setMaxVoltage(float newVal)
{
    maxVoltage = newVal;
}

void Light::SetGPIOPinVoltage(int percent)
{
    float newVoltage;
    
    newVoltage = maxVoltage * (percent/100);

    //todo set pin voltage, not just a binary value, using ADC
    if(percent > 0)
    {
        gpio_put(gpioPin, true);
    }
    else
    {
        gpio_put(gpioPin, false);
    }

}














































