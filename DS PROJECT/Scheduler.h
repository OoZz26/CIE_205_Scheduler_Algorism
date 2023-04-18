#pragma once
#include<iostream>
#include"Data Structures/Linked_List.h"
#include"Data Structures/QUEUE.h"
#include"Process/Process.h"
#include"RR_processor.h"
#include"FCFS_processor.h"
#include"Processors/Processor.h"
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;
class Scheduler
{
private:
	Queue<Processor*> Processors_List;
	Queue<Process*> New_Process_List;
	Queue<Process*> BLK_Process_List;
	Queue<Process*> TRM_Process_List;
	Queue<int>Signal_Kill_List;
public:
	int noOf_FCFS, noOF_SJF, noOF_RR;
	int AT, PID, CT, N;
	int NumofProcess;
	int Timeslice;
	int RTF, MaxW, STL, ForkPROB;
	int SPID, T;
	void LoadData(string filename);
};

