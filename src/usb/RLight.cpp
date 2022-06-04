#include "RLight.hpp"

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

RLight::RLight()
{

}

RLight::~RLight()
{
    
}

/* ***********************
 * Public Member Functions
 * **********************/

void RLight::SetState(eLightState newState)
{
    //No special cases in terms of state, so pass to parent function
    Light::SetState(newState);
}