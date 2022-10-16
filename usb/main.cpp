/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <array>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "wifiSingleton.hpp"
#include "Light.hpp"
#include "LRMotor.hpp"
#include "DriveMotor.hpp"

/****Definitions****/

/*Pinout definitions*/
const int FLheadlightPin = 16;
const int FRheadlightPin = 15;
const int FLindicatorPin = 17;
const int FRindicatorPin = 14;
const int RLlightPin = 29;
const int RRlightPin = 9;


/****Function Declarations****/

void LightStorageInit(std::array<Light, 6> &lightStorage);

/****Function Definitions****/

void LightStorageInit(std::array<Light, 6> &lightStorage)
{
    //Assign GPIO pins
    lightStorage[0].AssignGPIOPin(FLheadlightPin); //front left headlight
    lightStorage[1].AssignGPIOPin(FRheadlightPin); //front right headlight
    lightStorage[2].AssignGPIOPin(FLindicatorPin); //front left indicator
    lightStorage[3].AssignGPIOPin(FRindicatorPin); //front right indicator
    lightStorage[4].AssignGPIOPin(RLlightPin); //rear left light
    lightStorage[5].AssignGPIOPin(RRlightPin); //rear right light

    //Set all voltages to zero initially
    for (auto& record : lightStorage)
    {
        record.SetGPIOPinVoltage(0);
    }
}

int main() {    
    //Init for chosen serial port
    stdio_init_all();

    //Init for Wifi chip onboard.  This includes the LED but not GPIO
    if (cyw43_arch_init()) {
        printf("WiFi init failed");
        return -1;
    }

/*    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(700);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(700);
    }*/

    printf("start of program");

    //Allocate and initialize light storage
    std::array<Light, 6> lightStorage;
    LightStorageInit(lightStorage);

    //Create motor objects
    LRMotor lrMotor;
    DriveMotor driveMotor;

    //Get a reference to the wifiSingleton
    wifiSingleton& wifiInst = wifiSingleton::getInstance();

    //instantiate a struct to hold user commands
    wifiSingleton::WifiUserCommands userCommands;

    //create boolean for onboard LED state, for troubleshooting
    bool LEDstate = false;

    //Loop until successful wifi connection is made
    do{
        LEDstate = !LEDstate;
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, LEDstate);
        sleep_ms(100);
        unsigned int timeMS = time_us_32();

        //run the light runtimes anyways so that lights are showing config mode
        for (auto& record : lightStorage)
        {
            record.LightRuntime(timeMS);
        }
    }while ( !wifiInst.connect() );

    //Update light states to off
    for (auto& record : lightStorage)
    {
        record.SetState(Light::eLSOff);
    }

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    //Successfully connected.  Run through main control loop
    while(true) //todo leave control loop upon wifi command or a manual switchoff
    {
        //Receive commands from wifi
        wifiInst.receiveData(&userCommands);

        //Set light states according to commands
        lightStorage[0].SetState(userCommands.lightStates[0]);
        lightStorage[1].SetState(userCommands.lightStates[1]);
        lightStorage[2].SetState(userCommands.lightStates[2]);
        lightStorage[3].SetState(userCommands.lightStates[3]);
        lightStorage[4].SetState(userCommands.lightStates[4]);
        lightStorage[5].SetState(userCommands.lightStates[5]);
        lrMotor.UpdateState(userCommands.lrMotorState);
        driveMotor.UserInput(userCommands.forwardButton, userCommands.reverseButton);


        //update light runtimes
        unsigned int timeMS = time_us_32();

        for (auto& record : lightStorage)
        {
            record.LightRuntime(timeMS);
        }
        sleep_ms(200);
    }

    printf("end of program");

    return 0;
}
