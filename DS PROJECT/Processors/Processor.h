#pragma once
#include<string>
#include "stdafx.h"
#include <time.h> // required for time
#include <cstdlib> //required for srand and rand
class Scheduler;
 

// Parent Processor class
class Processor {
protected:
    int ProcessorID;
    string type;
    Scheduler* ss= nullptr;
    Queue<Process*> TRM_Process_List;
    Queue<Process*> readyQueue;

public:
    Processor(int n, Scheduler* s) {
        ProcessorID = n;
        ss = s;

    }

    virtual void ScheduleAlgo() = 0; // pure virtual function


    virtual void add_process(Process* p) = 0;

    virtual bool IS_IDLE() = 0;

    virtual string Processor_Type() = 0;

    virtual Process* get_run() = 0;
    virtual void set_run(Process* p) = 0;
    virtual void PrintReady() = 0;


    virtual void remove_process(int  id) = 0;
    virtual int RDY_Duration() = 0;
    virtual Process* get_fIrst_proces() = 0;
    void addToTerminatedList(Process* p);



};
