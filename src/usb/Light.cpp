#include "Light.hpp"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

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

    if (percent == 100)
    {
        gpio_put(gpioPin, true);
    }
    else if (percent == 0)
    {
        gpio_put(gpioPin, false);
    }
    else
    {
        newVoltage = maxVoltage * (percent/100);

        //TODO PWM
        //gpioPin must be a pin that has PWM
        gpio_set_function(gpioPin, GPIO_FUNC_PWM);
        // Find out which PWM slice is connected to GPIO pin
        uint slice_num = pwm_gpio_to_slice_num(0);

        // Set period of 4 cycles (0 to 3 inclusive)
        pwm_set_wrap(slice_num, 99);
        // Set channel A output high for one cycle before dropping
        pwm_set_chan_level(slice_num, PWM_CHAN_A, (percent - 1));
        // Set initial B output high for three cycles before dropping
        pwm_set_chan_level(slice_num, PWM_CHAN_B, (percent - 1));
        // Set the PWM running
        pwm_set_enabled(slice_num, true);
    }
}














































