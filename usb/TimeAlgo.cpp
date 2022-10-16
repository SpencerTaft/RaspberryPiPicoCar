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
    //todo Constructor definition
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
    blink = false;

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
        printf("rollover\n");
    }
    else
    {
        timeElapsed = timestamp - startTS;  
    }

    //First multiply numerator by 100% to prevent truncation in integer division
//    timePercent = (duration - timeElapsed)*100;
    timePercent = timeElapsed*100;
    timePercent /= duration;

    //Convert percent of duration complete to percent complete along startPercent->endPercent span
    if (revRamp)
    {
        currentPercent = startPercent + ((endPercent - startPercent) * timePercent)/100;
    }
    else
    {
        currentPercent = endPercent - ((endPercent - startPercent) * timePercent)/100;
    }

    printf("/////////////////////////////////////\n");
    printf("startTime: %d, timeStamp: %d, elapsed %d timepercent %d currentpercent %d\n", startTS, timestamp, timeElapsed, timePercent, currentPercent);
    

    if (blink)
    {
        //Reverses the ramp direction, used to create sawtooth for flashing lights
        if (((endPercent == currentPercent) && (!revRamp))
                || ((startPercent == currentPercent) && revRamp))
        {
            printf("REVERSE\n");
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
