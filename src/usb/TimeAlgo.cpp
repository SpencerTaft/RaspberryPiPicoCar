#include "TimeAlgo.hpp"
#include "pico/stdlib.h"
#include <algorithm>
#include <stdio.h>
#include <climits>

/* ***********************
 * Constructors, Destructors, Operators
 * **********************/

TimeAlgo::TimeAlgo()
{
    currentPercent = 0;
    startPercent = 0;
    endPercent = 0;
    duration = 0;
    startTS = 0;
    revRamp = false;
    blink = false;
}

TimeAlgo::~TimeAlgo()
{
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
    revRamp = (startPercent > endPercent);

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
    timePercent = timeElapsed*100;
    timePercent /= duration;

    //Convert percent of duration complete to percent complete along startPercent->endPercent span
    if (revRamp)
    {
        currentPercent = endPercent - ((endPercent - startPercent) * timePercent)/100;
    }
    else
    {
        currentPercent = startPercent + ((endPercent - startPercent) * timePercent)/100;
    }

    if (blink)
    {
        //Reverses the ramp direction, used to create sawtooth for flashing lights
        //Use time percent which goes from 0 to 100%, rather than currentPercent which goes from newStartPercent to newEndPercent
        
        if ((currentPercent <= startPercent) || (currentPercent >= endPercent))
        {
            revRamp = !revRamp;
            startTS = timestamp;
        }
    }

    return currentPercent;
}

bool TimeAlgo::IsRampEnabled()
{
    return (startPercent != endPercent);
}

void TimeAlgo::SetBlink(bool newVal)
{
    blink = newVal;
}
