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
    return true; //todo implement, or might already come for free
}

//Receive control data from web controller
void wifiSingleton::receiveData(WifiUserCommands *userCommands)
{
    //todo use wifi to receive data
    userCommands->lightStates[0] = Light::eLSConfig; //front left headlight
    userCommands->lightStates[1] = Light::eLSOn; //front right headlight
    userCommands->lightStates[2] = Light::eLSOn; //front left indicator
    userCommands->lightStates[3] = Light::eLSOn; //front right indicator
    userCommands->lightStates[4] = Light::eLSOn; //rear left light
    userCommands->lightStates[5] = Light::eLSOn; //rear right light
    userCommands->lrMotorState = LRMotor::driveLeft;
    userCommands->forwardButton = true;
    userCommands->reverseButton = false;
}
