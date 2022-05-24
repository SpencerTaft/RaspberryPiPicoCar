#include "wifiSingleton.hpp"
//#include <stdio.h>
//#include "pico/stdlib.h"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

wifiSingleton::wifiSingleton()
{
    //todo Constructor definition
}

wifiSingleton::~wifiSingleton()
{
    //todo Destructor definition
}

/* ***********************
 * Public Static Functions
 * **********************/

static wifiSingleton& getInstance()
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
void wifiSingleton::receiveData()
{

}