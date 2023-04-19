#pragma once
#include<string>
#include "stdafx.h"
#include <time.h> // required for time
#include <cstdlib> //required for srand and rand


// Parent Processor class
class Processor {
protected:
    int ProcessorID;
    string type;


public:
    Processor(int n) {
        ProcessorID = n;
    }

    virtual void ScheduleAlgo() = 0; // pure virtual function

    virtual void add_process(Process* p) = 0;

    virtual bool IS_IDLE() = 0;

    virtual string Processor_Type() = 0;

    virtual Process* get_run() = 0;
    virtual void PrintReady() = 0;


    virtual void remove_process(Process* p) = 0;


};
