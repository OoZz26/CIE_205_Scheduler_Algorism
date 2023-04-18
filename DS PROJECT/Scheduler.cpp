#include "Scheduler.h"
Scheduler::Scheduler()
{
	
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
								Pairs_of_io.EnQueue(x);
								cout << x << endl;
							}
						}
						
						
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
void Scheduler::Dispaly_New_Process_List()
{
	for (int i = 0; i < NumofProcess; i++)
	{

		Process* P = New_Process_List.FRONT();
		New_Process_List.DeQueue();
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
	BLK_Process_List.EnQueue(p);
}
void Scheduler::Add_to_TRM(Process* p)
{
	TRM_Process_List.EnQueue(p);

}



