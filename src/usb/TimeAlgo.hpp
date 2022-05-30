
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
        void SetRamp(int, int);
        //UpdateRamp is called every scan and returns the current percent completion
        int UpdateRamp();
        //IsEvent is called to check if a ramp or timer is complete
        bool IsEvent();
        
    private:
        bool eventFlag; //todo remove?
        int currentPercent;
        int startPercent;
        int endPercent;

};