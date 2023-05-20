#pragma once
#include "Scheduler.h"
#include"Processors/Processor.h"
Scheduler::Scheduler()
{
	t_Step = 0;
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
								Myfile >> x ;
								Pairs_of_io.Enqueue(x);
								
							}
						}
						
						
						Process* Processes = new Process(AT, PID, CT,N);
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
	for (int i = 0; i < noOf_FCFS; i++)
	{
		FCFS_processor* P = new FCFS_processor(counter_noOf_FCFS,this);
		counter_noOf_FCFS += 1;
		Processors_List.Enqueue(P);
	}
	for (int i = 0; i < noOF_SJF; i++)
	{
		SJF_processor* P = new SJF_processor(counter_noOf_SJF, this);
		counter_noOf_SJF += 1;
		Processors_List.Enqueue(P);
	}
	for (int i = 0; i < noOF_RR; i++)
	{
		RR_processor* R = new RR_processor(counter_noOf_RR,this ,Timeslice);
		counter_noOf_RR += 1;
		Processors_List.Enqueue(R);
	}
	
	
}
void Scheduler::Dispaly_New_Process_List()
{
	for (int i = 0; i < NumofProcess; i++)
	{

		Process* P;
		New_Process_List.Dequeue(P);
		cout<< "arrival time is" << " " << P->get_arrival_time() << endl;
		cout <<"PID is" << " " << P->get_pid() << endl;
		cout << "CPU Time is" << " " << P->get_cpu_time() << endl;
		cout <<"no of io req is" << " " << P->get_io_request_number() << endl;
		cout << "------------------------------------------------------"<<endl;
	}
	
	
}

void Scheduler::Display_input_file_Data()
{
	cout << "noOf_FCFS is" << " " << noOf_FCFS<< endl;
	cout << "------------------------------------------------------" << endl;
	cout << "noOF_SJF is" << " " << noOF_SJF  << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "noOF_RR is" << " " << noOF_RR  << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Timeslice is" << " " << Timeslice << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "RTF is" << " " << RTF  << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "MaxW is" << " " << MaxW  << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "STL is" << " " << STL << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "ForkPROB is" << " " << ForkPROB << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "NumofProcess is" << " " << NumofProcess  << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "noOf_Signal_Kill is" << " " << noOf_Signal_Kill  << endl;
}

void Scheduler:: Add_to_BLK(Process* p)
{
	BLK_Process_List.Enqueue(p);
}
void Scheduler::Add_to_TRM(Process* p)
{
	TRM_Process_List.Enqueue(p);

}

Queue<Processor*> Scheduler::GetProcessorList() const
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

void Scheduler::Increase_timeStep()
{
	t_Step = t_Step + 1;
}

void Scheduler::simulatioon()
{
	while (TRM_Process_List.Count() != NumofProcess) {

	}
}

