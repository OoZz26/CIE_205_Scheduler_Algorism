#include "Scheduler.h"
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
			if (currenLine = 1)
			{
				Myfile >> noOf_FCFS >> noOF_SJF >> noOF_RR;
				currenLine += 1;
				
			}
			if (currenLine = 2)
			{
				Myfile >> Timeslice;
				currenLine += 1;
			}
			if (currenLine = 3)
			{
				Myfile >> RTF >> Timeslice >> STL >> ForkPROB;
				currenLine += 1;
			}
			if (currenLine = 4)
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
						Myfile >> AT >> PID >> CT >> N;
						Process* Processes = new Process(AT, PID, CT,N);
						New_Process_List.EnQueue(Processes);
						
						currenLine += 1;
						
					}

				}
			}

			if (currenLine > 4 + NumofProcess)
			{

				while (!Myfile.eof())
				{
					Myfile >> SPID >> T;
					Signal_Kill_List.EnQueue(SPID);
					Signal_Kill_List.EnQueue(T);
					
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
		FCFS_processor* P = new FCFS_processor(counter_noOf_FCFS);
		counter_noOf_FCFS += 1;
		Processors_List.EnQueue(P);
	}
	for (int i = 0; i < noOF_SJF; i++)
	{

	}
	for (int i = 0; i < noOF_RR; i++)
	{
		RR_processor* R = new RR_processor(counter_noOf_RR, Timeslice);
		counter_noOf_RR += 1;
		Processors_List.EnQueue(R);
	}
	
}





