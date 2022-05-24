
#pragma once

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
         * Public Static Functions
         * **********************/

        static wifiSingleton& getInstance();

        /* ***********************
         * Public Member Functions
         * **********************/

        bool connect();

        void receiveData();

};