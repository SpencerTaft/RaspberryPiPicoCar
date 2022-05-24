/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

#include "include/wifiSingleton.hpp"

int main() {
    stdio_init_all();

    printf("Hello, world!\n");
    
    //Get a reference to the wifiSingleton
    //wifiSingleton& wifiInst = wifiSingleton::getInstance();
    wifiSingleton::getInstance();

    //Loop until successful wifi connection is made
//    do{
//        sleep_ms(1000);
//    }while ( !wifiInst.connect() );


    //Main control loop


    return 0;
}
