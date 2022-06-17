#pragma once

class TimeAlgo
{
    public:
        /* ***********************
         * Constructors, Destructors, Operators
         * **********************/

        //Constructor declaration
        TimeAlgo();
        //Destructor declaration
        ~TimeAlgo();

        /* ***********************
         * Public Member Functions
         * **********************/

        //SetRamp starts a ramp algorithm with a start percent and end percent
        void SetRamp(int newStartPercent, int newEndPercent, unsigned int newDuration);
        //UpdateRamp is called every scan and returns the current percent completion
        int UpdateRamp(unsigned int timestamp);
        bool IsRampEnabled();

    private:
        int currentPercent;
        int startPercent;
        int endPercent;
        unsigned int duration;
        unsigned int startTS;
        bool revRamp;
};