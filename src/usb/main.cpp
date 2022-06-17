/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <array>
#include "pico/stdlib.h"
#include "wifiSingleton.hpp"
#include "Light.hpp"

void LightStorageInit(std::array<Light, 6> &lightStorage);



void LightStorageInit(std::array<Light, 6> &lightStorage)
{
    //Assign GPIO pins
    lightStorage[0].AssignGPIOPin(0); //front left headlight
    lightStorage[1].AssignGPIOPin(0); //front right headlight
    lightStorage[2].AssignGPIOPin(0); //front left indicator
    lightStorage[3].AssignGPIOPin(0); //front right indicator
    lightStorage[4].AssignGPIOPin(0); //rear left light
    lightStorage[5].AssignGPIOPin(0); //rear right light

    //Set all voltages to zero initially
    for (auto& record : lightStorage)
    {
        record.SetGPIOPinVoltage(0);
    }
}

int main() {
    stdio_init_all();


    //Allocate and initialize light storage
    std::array<Light, 6> lightStorage;
    LightStorageInit(lightStorage);

    //Get a reference to the wifiSingleton
    wifiSingleton& wifiInst = wifiSingleton::getInstance();

    //Loop until successful wifi connection is made
    do{
        sleep_ms(1000);
    }while ( !wifiInst.connect() );


    //Main control loop
    //time_us_32(); //returns u32 in ms






    return 0;
}
