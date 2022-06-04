#include "Light.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

Light::Light()
{

}

Light::~Light()
{
    
}

/* ***********************
 * Public Member Functions
 * **********************/

void Light::setState(eLightState newState)
{
    switch(newState)
    {
        case eLSOff:
            //SetRamp(0,0); //disables the 
            break;

        case eLSOn:
            break;
        case eLSFlasher:
            break;
        case eLSIndicator:
            break;
        case eLSConfig:
            break;
        case eLSError:
        default:
            break;
    }
}