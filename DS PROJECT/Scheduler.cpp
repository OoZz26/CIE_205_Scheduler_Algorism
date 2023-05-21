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

void Scheduler::Display_input_file_Data()
{
	cout << "noOf_FCFS is" << " " << noOf_FCFS << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "noOF_SJF is" << " " << noOF_SJF << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "noOF_RR is" << " " << noOF_RR << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Timeslice is" << " " << Timeslice << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "RTF is" << " " << RTF << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "MaxW is" << " " << MaxW << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "STL is" << " " << STL << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "ForkPROB is" << " " << ForkPROB << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "NumofProcess is" << " " << NumofProcess << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "noOf_Signal_Kill is" << " " << noOf_Signal_Kill << endl;
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

		for (int i = 0; i < sizeof(Processors_List); i++)
		{
			Process* p = Processors_List[i]->get_run();
			if (p)
			{

			}

		}


	}


}

Scheduler::~Scheduler()
{
	for (int i = 0; i < sizeof(Processors_List); ++i) {
		delete Processors_List[i];  // Delete each dynamically allocated Processor object
	}
	delete[] Processors_List;  // Delete the array itself

}




