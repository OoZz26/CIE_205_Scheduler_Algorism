#pragma once
#include<iostream>
#include"Data Structures/Linked_List.h"
#include"Data Structures/QUEUE.h"
#include"Process/Process.h"
#include"RR_processor.h"
#include"FCFS_processor.h"
#include "SJF.h"
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
#include "UI.h"


class Processor;
using namespace std;
class Scheduler
{
private:
	struct SIGKILL
	{
		int SKPID;
		int  ST;
	};
	Processor** Processors_List;
	Queue<Process*> New_Process_List;
	Queue<Process*> BLK_Process_List;
	Queue<Process*> TRM_Process_List;
	Queue< SIGKILL> Signal_Kill_List;
	
	Queue<int>List;
	int t_Step;
	

public:

	Scheduler();
	int noOf_Signal_Kill = 0;
	int noOf_FCFS, noOF_SJF, noOF_RR;
	int AT, PID, CT, N;
	int NumofProcess;
	int Timeslice;
	int RTF, MaxW, STL, ForkPROB;
	int SPID, T;

	void LoadData(string filename);
	void Dispaly_New_Process_List();
	
	void Add_to_BLK(Process* p);
	void Add_to_TRM(Process* p);
	void KILLSIG();
	Processor** GetProcessorList() const;
	Queue<Process*> GetBLKList()const;
	Queue<Process*> GetTRMList() const;
	int GettimeStep();
	Processor* get_shortest_processor();
	Processor* get_shortest_FCFS();
	Processor* get_longest_processor();
	void Simulate();
	void Fork(int step, int forkprob, Processor* processor);
	void work_Steal(int step);
	int LQF(Processor* p);
	int SQF(Processor* p);
	~Scheduler();

};

