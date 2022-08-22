#include "wifiSingleton.hpp"
//#include <stdio.h>
//#include "pico/stdlib.h"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

wifiSingleton::wifiSingleton()
{
}

wifiSingleton::~wifiSingleton()
{
}

/* ***********************
 * Public Static Functions
 * **********************/

wifiSingleton& wifiSingleton::getInstance()
{
    static wifiSingleton instance;
    return instance;
}

/* ***********************
 * Public Member Functions
 * **********************/

//Attempt connection to web controller over wifi, and return true if connection is successfull
bool wifiSingleton::connect()
{
    return true; //todo implement
}

//Receive control data from web controller
void wifiSingleton::receiveData(WifiUserCommands *userCommands)
{
    //todo use wifi to receive data
    userCommands->lightStates[0] = Light::eLSOn;
    userCommands->lightStates[1] = Light::eLSOn;
    userCommands->lightStates[2] = Light::eLSOn;
    userCommands->lightStates[3] = Light::eLSOn;
    userCommands->lightStates[4] = Light::eLSOn;
    userCommands->lightStates[5] = Light::eLSOn;
    userCommands->lrMotorState = LRMotor::driveLeft;
    userCommands->forwardButton = true;
    userCommands->reverseButton = false;
}