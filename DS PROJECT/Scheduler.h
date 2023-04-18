#pragma once
#include<iostream>
#include"Data Structures/Linked_List.h"
#include"Data Structures/QUEUE.h"
#include"Process/Process.h"
#include"RR_processor.h"
#include"FCFS_processor.h"
#include"Processors/Processor.h"
#include "SJF.h"
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;
class Scheduler
{
private:
	struct SIGKILL
	{
		int SKPID;
		int  ST;
	};
	Queue<Processor*> Processors_List;
	Queue<Process*> New_Process_List;
	Queue<Process*> BLK_Process_List;
	Queue<Process*> TRM_Process_List;
	Queue< SIGKILL> Signal_Kill_List;
	Queue<string> Pairs_of_io;
	Queue<int>List;
	int t_Step;
	
public:

	Scheduler();
	int noOf_Signal_Kill=0;
	int noOf_FCFS, noOF_SJF, noOF_RR;
	int AT, PID, CT, N;
	int NumofProcess;
	int Timeslice;
	int RTF, MaxW, STL, ForkPROB;
	int SPID, T;
	void LoadData(string filename);
	void Dispaly_New_Process_List();
	void Display_input_file_Data();
	void Add_to_BLK(Process* p);
	void Add_to_TRM(Process* p);
	Queue<Processor*> GetProcessorList() const;
	Queue<Process*> GetBLKList()const;
	Queue<Process*> GetTRMList() const;
	int GettimeStep();

};

