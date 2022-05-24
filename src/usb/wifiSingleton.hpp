//#include <stdio.h>
//#include "pico/stdlib.h"


class wifiSingleton
{
    public:
        wifiSingleton()
        {
            //Constructor
        }

        ~wifiSingleton()
        {
            //Destructor
        }

        //Remove these operations to prevent multiple copies
        wifiSingleton(wifiSingleton const&) = delete;
        void operator=(wifiSingleton const&) = delete;
};