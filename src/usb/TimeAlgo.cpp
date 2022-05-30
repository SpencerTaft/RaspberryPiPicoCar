#include "TimeAlgo.hpp"

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

void TimeAlgo::SetRamp(int startPercent, int endPercent)
{

}

int TimeAlgo::UpdateRamp()
{
    return TimeAlgo::currentPercent;
}

bool TimeAlgo::IsEvent()
{
    bool isEvent = false;

    isEvent = ((endPercent == currentPercent) && (startPercent != endPercent));

    return isEvent;
}
