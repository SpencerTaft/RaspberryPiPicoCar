#include "TimeAlgo.hpp"
#include "pico/stdlib.h"
#include <algorithm>
#include <climits>

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

TimeAlgo::TimeAlgo()
{
    //todo Constructor definition
}

TimeAlgo::~TimeAlgo()
{
    //todo Destructor definition
}

/* ***********************
 * Public Member Functions
 * **********************/

void TimeAlgo::SetRamp(int newStartPercent, int newEndPercent, unsigned int newDuration)
{
    startPercent = newStartPercent;
    currentPercent = startPercent;
    endPercent = newEndPercent;
    duration = newDuration;

    startTS = time_us_32();
}

int TimeAlgo::UpdateRamp(unsigned int timestamp)
{
    unsigned int timeElapsed;
    int timePercent;

    if (timestamp < startTS)
    {
        //time rolled over, elapsed is startTS to rollover plus the current timestamp
        timeElapsed = timestamp + (UINT_MAX - startTS);
    }
    else
    {
        timeElapsed = timestamp - startTS;
        
    }

    //First multiply numerator by 100% to prevent truncation in integer division
    timePercent = (duration - timeElapsed)*100;
    timePercent /= duration;

    //Convert percent of duration complete to output voltage percent
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//NEXT TIME: start here
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //Reverses the ramp direction, used to create sawtooth for flashing lights
    if (endPercent == currentPercent)
    {
        revRamp = ~revRamp;
    }

    return currentPercent;
}

bool TimeAlgo::IsRampEnabled()
{
    return (startPercent != endPercent);
}
