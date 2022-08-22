
#pragma once

#include "Light.hpp"
#include "LRMotor.hpp"

class wifiSingleton
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        wifiSingleton();
        //Destructor declaration
        ~wifiSingleton();

        //Remove these operations to prevent multiple copies
        wifiSingleton(wifiSingleton const&) = delete;
        void operator=(wifiSingleton const&) = delete;

        /* ***********************
         * Types
         * **********************/

        typedef struct {
            Light::eLightState lightStates[6];
            LRMotor::MotorState lrMotorState;
            bool forwardButton;
            bool reverseButton;
        } WifiUserCommands;

        /* ***********************
         * Public Static Functions
         * **********************/

        static wifiSingleton& getInstance();

        /* ***********************
         * Public Member Functions
         * **********************/

        bool connect();

        void receiveData(WifiUserCommands *userCommands);

};