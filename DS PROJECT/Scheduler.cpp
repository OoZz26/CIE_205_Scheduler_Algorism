#pragma once
#include "Scheduler.h"
#include"Processors/Processor.h"

#include <iostream>
using namespace std;
Scheduler::Scheduler()
{
	t_Step = 1;

}
void Scheduler::LoadData(string filename)
{

	int counter_noOf_FCFS = 1;
	int counter_noOf_SJF = 1;
	int counter_noOf_RR = 1;
	int currenLine = 1;
	fstream Myfile;
	Myfile.open(filename, ios::in);
	if (Myfile.is_open())
	{

		while (!Myfile.eof())
		{
			if (currenLine == 1)
			{
				Myfile >> noOf_FCFS >> noOF_SJF >> noOF_RR;
				currenLine += 1;
				const int size = noOf_FCFS + noOF_SJF + noOF_RR;
				Processors_List = new Processor * [size];
				int index = 0;

				for (int i = 0; i < noOf_FCFS; i++)
				{
					FCFS_processor* P = new FCFS_processor(counter_noOf_FCFS, this);
					Processors_List[index] = P;
					index++;
					counter_noOf_FCFS += 1;

				}
				for (int i = 0; i < noOF_SJF; i++)
				{
					SJF_processor* P = new SJF_processor(counter_noOf_SJF, this);
					counter_noOf_SJF += 1;
					Processors_List[index] = P;
					index++;
				}
				for (int i = 0; i < noOF_RR; i++)
				{
					RR_processor* R = new RR_processor(counter_noOf_RR, this, Timeslice);
					counter_noOf_RR += 1;
					Processors_List[index] = R;
					index++;
				}

			}
			if (currenLine == 2)
			{
				Myfile >> Timeslice;
				currenLine += 1;
			}
			if (currenLine == 3)
			{
				Myfile >> RTF >> MaxW >> STL >> ForkPROB;
				currenLine += 1;
			}
			if (currenLine == 4)
			{
				Myfile >> NumofProcess;
				currenLine += 1;


			}
			if (currenLine > 4 && currenLine <= NumofProcess + 4)
			{


				for (int i = 0; i < NumofProcess; i++)
				{
					
					if (Myfile.eof())
					{
						break;
					}
					else
					{
						Queue<string> Pairs_of_io;
						string x;
						Myfile >> AT >> PID >> CT >> N;
						if (N > 0)
						{
							for (int i = 0; i < N; i++)
							{
								Myfile >> x;
								Pairs_of_io.Enqueue(x);

							}
						}


						Process* Processes = new Process(AT, PID, CT, N);
						New_Process_List.Enqueue(Processes);
						currenLine += 1;

					}

				}
			}


			if (currenLine > 4 + NumofProcess)
			{

				while (!Myfile.eof())
				{
					Myfile >> SPID >> T;
					SIGKILL S;
					S.SKPID = SPID;
					S.ST = T;
					Signal_Kill_List.Enqueue(S);
					noOf_Signal_Kill += 1;

				}

			}
		}

		Myfile.close();

	}
	else
	{
		cout << "file faild to open";
	}



}
void Scheduler::Dispaly_New_Process_List()
{
	for (int i = 0; i < NumofProcess; i++)
	{

		Process* P;
		New_Process_List.Dequeue(P);
		cout << "arrival time is" << " " << P->get_arrival_time() << endl;
		cout << "PID is" << " " << P->get_pid() << endl;
		cout << "CPU Time is" << " " << P->get_cpu_time() << endl;
		cout << "no of io req is" << " " << P->get_io_request_number() << endl;
		cout << "------------------------------------------------------" << endl;
	}


}

void Scheduler::Add_to_BLK(Process* p)
{
	BLK_Process_List.Enqueue(p);
}
void Scheduler::Add_to_TRM(Process* p)
{
	TRM_Process_List.Enqueue(p);

}

Processor** Scheduler::GetProcessorList() const
{
	return Processors_List;
}

Queue<Process*> Scheduler::GetBLKList() const
{
	return BLK_Process_List;
}



Queue<Process*> Scheduler::GetTRMList() const
{
	return TRM_Process_List;
}

int Scheduler::GettimeStep()
{
	return t_Step;
}

Processor* Scheduler::get_shortest_processor() {
	const int p_count = sizeof(Processors_List);

	int* array_CTs = new int[p_count];
	int i = 0;


	for (int i = 0; i < p_count; i++)
	{

		array_CTs[i] = Processors_List[i]->RDY_Duration();

	}

	int min = array_CTs[0];
	for (int i = 0; i < p_count; i++) {
		if (array_CTs[i] < min) {
			min = array_CTs[i];
		}
	}
	for (int i = 0; i < p_count; i++) {
		if (Processors_List[i]->RDY_Duration() == min) {
			return Processors_List[i];
		}
	}
	return Processors_List[0];
}


Processor* Scheduler::get_longest_processor() {
	const int p_count = sizeof(Processors_List);

	int* array_CTs = new int[p_count];
	int i = 0;


	for (int i = 0; i < p_count; i++)
	{

		array_CTs[i] = Processors_List[i]->RDY_Duration();

	}

	int max = array_CTs[0];
	for (int i = 0; i < p_count; i++) {
		if (array_CTs[i] > max) {
			max = array_CTs[i];
		}
	}
	for (int i = 0; i < p_count; i++) {
		if (Processors_List[i]->RDY_Duration() == max) {
			return Processors_List[i];
		}
	}
	return Processors_List[0];
}





void Scheduler::Simulate()
{
	UI* pUI = new UI();

	int counter_for_processors = 0;
	pUI->print_message("Please choose the mode you want\n 1- for Interactive Mode \n 2- for Step by Step Mode \n 3- for Silent Mode");
	int mode;
	cin >> mode;


	pUI->print_message("---------------------------------------------------------------------------------------------");
	while (TRM_Process_List.Count() < NumofProcess)
	{
		if (New_Process_List.Count() != 0) {
			// to move from new to rdy lists
			Process* p;
			New_Process_List.Peek(p);

			if (p->get_arrival_time() <= t_Step) {
				New_Process_List.Dequeue(p);

				get_shortest_processor()->add_process(p); // adding the procecess to the least time processor

			}
		}

		work_Steal(t_Step); // work stealing function




		
		


	}


}

	

void Scheduler::work_Steal(int step)
{

	// work stealing starts here 
	if (t_Step % STL == 0) { // every stl 
		Processor* short_processor = get_shortest_processor();
		Processor* long_processor = get_longest_processor();
		// here the LQF must be for the most processor only not genaral same as sqf 
		while (LQF(long_processor) != 0 && (((LQF(long_processor) - SQF(short_processor)) / LQF(long_processor)) * 100) > 40) // work stealing // what if infinite loop ?? 
		{
			Process* firstprocess = long_processor->get_fIrst_proces(); // here the get first function is with removal of the first element
			short_processor->add_process(firstprocess); // adding to the ready of the shortest queueu
			// removing the first element from run if it was
			if (long_processor->get_run() == firstprocess) {
				long_processor->set_run(nullptr);
			}


		}
	}
	//end of work stealing 

}

int Scheduler::LQF(Processor* p)
{
	return p->RDY_Duration();
}

int Scheduler::SQF(Processor* p)
{
	return p->RDY_Duration();
}

Scheduler::~Scheduler()
{
	for (int i = 0; i < sizeof(Processors_List); ++i) {
		delete Processors_List[i];  // Delete each dynamically allocated Processor object
	}
	delete[] Processors_List;  // Delete the array itself

}




