
#pragma once

class Light
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        wifiSingleton();
        //Destructor declaration
        ~wifiSingleton();

        /* ***********************
         * Public Member Functions
         * **********************/

        bool connect();

        void receiveData();

};