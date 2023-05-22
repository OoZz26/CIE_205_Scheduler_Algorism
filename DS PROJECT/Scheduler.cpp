#pragma once
#include "Scheduler.h"
#include"Processors/Processor.h"
#include"Struct.h"
#include <iostream>
using namespace std;
Scheduler::Scheduler()
{
	t_Step = 1;

}

void Scheduler::Create_Processors(int noOf_FCFS, int noOF_SJF, int noOF_RR, int Timeslice)
{
	int counter_noOf_FCFS = 0;
	int counter_noOf_SJF = 0;
	int counter_noOf_RR = 0;
	size = noOf_FCFS + noOF_SJF + noOF_RR;
	Processors_List = new Processor * [size];
	int index = 0;
	

	for (int i = 0; i < noOf_FCFS; i++)
	{
		FCFS_processor* P = new FCFS_processor(counter_noOf_FCFS, this);
		Processors_List[index] = P;
		index++;
		counter_noOf_FCFS ++;

	}
	for (int i = 0; i < noOF_SJF; i++)
	{
		SJF_processor* P = new SJF_processor(counter_noOf_SJF, this);
		counter_noOf_SJF ++;
		Processors_List[index] = P;
		index++;
	}
	for (int i = 0; i < noOF_RR; i++)
	{
		RR_processor* R = new RR_processor(counter_noOf_RR, this, Timeslice);
		counter_noOf_RR ++;
		Processors_List[index] = R;
		index++;
	}
}


void Scheduler::LoadData(string filename) {
    ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        exit(1);
    }
	else {
		// Read Processors, General Info  --> The first three lines 
		int num_FCFS, num_SJF, num_RR, timeSlice_RR, rtf, Maxw, stl, Forkprobability;
		infile >> num_FCFS >> num_SJF >> num_RR >> timeSlice_RR >> rtf >> Maxw >> stl >> Forkprobability;
		RTF = rtf; MaxW = Maxw; STL = stl;  ForkPROB = Forkprobability;
		noOf_FCFS = num_FCFS; noOF_SJF = num_SJF; noOF_RR = num_RR;
		Create_Processors(num_FCFS, num_SJF, num_RR, timeSlice_RR);

		// Read Processes Info -->
		int numProcesses;
		infile >> numProcesses;


		NumofProcess = numProcesses;
		/*UniqueChildID = numOFProcesses + 1;*/
		char l;  // to end the line and go to the next one
		infile.get(l);

		string line;

		int IO_R, IO_D;
		char comma, space;

		for (int i = 0; i < numProcesses; i++) {


			getline(infile, line);

			int val1, val2, val3, val4;
			// extract the first four values
			istringstream ss_first_four(line);
			if (ss_first_four.fail()) {
				continue;
			}
			else {
				ss_first_four >> val1 >> val2 >> val3 >> val4;
			}

			Queue<io_request> io_requests;

			int totalIOD_File = 0;
			for (int g = 0; g < val4; g++) {

				// find the start and end positions of the round brackets
				size_t start_pos = line.find("(");
				size_t end_pos = line.find(")");

				// create a string stream and extract the values
				std::istringstream ss(line.substr(start_pos + 1, end_pos - start_pos - 1));

				ss >> IO_R >> comma >> IO_D >> space;

				io_request req = { IO_R, IO_D };
				io_requests.Enqueue(req);
				totalIOD_File += IO_D;
			}




			Process* P = new Process(val1, val2, val3, val4, io_requests);
			New_Process_List.Enqueue(P);
			
		}
		
		int KillTime, ProcessID;

		while (!infile.eof()) {
			infile >> KillTime >> ProcessID;
			SIGKILL k = { KillTime, ProcessID };
			Signal_Kill_List.Enqueue(k);
			noOf_Signal_Kill++;
		}
		if (infile.is_open()) {
			infile.close();
		}
		
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
		New_Process_List.Enqueue(P);
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

void Scheduler::KILLSIG()
{
	Node1<SIGKILL>* Sig = Signal_Kill_List.GetFront();
	if (Signal_Kill_List.IsEmpty()) {
		return;
	}
	else {
		if (Sig->GetItem().ST == t_Step){
			for (int i = 0;i < sizeof(Processors_List); i++) {
				if (Processors_List[i]->Processor_Type() == "FCFS_processor") {
					Processors_List[i]->remove_process(Sig->GetItem().SKPID);
					
				}
				
				
			}
			return;
		}

		else {
			return;
		}
	}
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
	 int p_count = size;

	int* array_CTs = new int[p_count];
	

	for (int i = 0; i < p_count; i++)
	{

		array_CTs[i] = Processors_List[i]->RDY_Duration();

	}

	int min = array_CTs[0];
	int index = 0;
	for (int i = 0; i < p_count; i++) {
		if (array_CTs[i] < min) {

			min = array_CTs[i];
			index = i;
		}
	}
	return Processors_List[index];

}

Processor* Scheduler::get_shortest_FCFS()
{
	const int p_count = sizeof(Processors_List);

	int* array_CTs = new int[noOf_FCFS];
	for (int j = 0; j < p_count; j++)
	{

		if (Processors_List[j]->Processor_Type() == "FCFS_processor") {
			for (int i = 0; i < noOf_FCFS; i++)
			{

				array_CTs[i] = Processors_List[i]->RDY_Duration();

			}
			 
			int min = array_CTs[0];
			for (int i = 0; i < noOf_FCFS; i++) {
				if (array_CTs[i] < min) {
					min = array_CTs[i];
				}
			}
			for (int i = 0; i < noOf_FCFS; i++) {
				if (Processors_List[i]->RDY_Duration() == min) {
					return Processors_List[i];
				}
			}
		}
	}
	
	return nullptr;
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


void Scheduler::RUN_TO_BLK()
{
	for (int i = 0; i < size; i++)
	{
		Process* R = Processors_List[i]->get_run();
		if (R != nullptr) {
			if (R->get_N_ofIoR() > 0) {
				
					int executedtime = R->get_cpu_time() - R->get_remainnig_time();
					
					io_request req;
					Queue<io_request> Q = R->get_iorequest();
					Q.Peek(req);
					if (req.io_request_time <= executedtime) {
						
						R->decrement_N_ofIoR(); // so that the next time the number of io requests is less than before 
						R->reset_BLK_counter();// resenting BLK counter because it has enered new IO request
						BLK_Process_List.Enqueue(R);
						Processors_List[i]->set_run(nullptr);
						R->set_state(3);
					
					}
				
			}
		}

	}


	
}

void Scheduler::BLK_TO_RDY()
{
	Queue<Process*>* TMP = new Queue<Process*>;
	Process* empty;
	
	while (BLK_Process_List.Dequeue(empty)) {
		io_request req;
		Queue<io_request> Q = empty->get_iorequest();
		Q.Peek(req);
		if (empty->get_BLK_counter() == req.io_duration) {
			get_shortest_processor()->add_process(empty);
			Q.Dequeue(req);

		}
		else {
			TMP->Enqueue(empty);
		}

	}
	while (TMP->Dequeue(empty)) {
		BLK_Process_List.Enqueue(empty);
	}
	delete TMP;
}

void Scheduler::incrementBLKcounters()
{
	Queue<Process*>* TMP = new Queue<Process*>;
	Process* empty;
	while (BLK_Process_List.Dequeue(empty)) {
		empty->increament_BLK_counter();
		empty->incrementIO_D();
		TMP->Enqueue(empty);
	}

	while (TMP->Dequeue(empty)) {
		BLK_Process_List.Enqueue(empty);
	}
	delete TMP;

}




void Scheduler::Run_to_TRM(int step)
{
	for (int  i = 0; i < size; i++)
	{
		Process* R = Processors_List[i]->get_run();
		if (R != nullptr) {
			if (R->get_remainnig_time() == 0) {

				/*remove_from_RDY(Run);*/
				TRM_Process_List.Enqueue(R);
				if (R->get_child_pointer() != nullptr) {
					TRM_Process_List.Enqueue(R->get_child_pointer());
					R->set_state(4);
					R->set_child_pointer(nullptr);
					R->set_TT(step);
				}
				
				Processors_List[i]->set_run(nullptr);

			}
		}

	}
	

}




	




void Scheduler::Simulate()
{
	UI* pUI = new UI();
	pUI->print_message("Enter the name of the file you would to load from: ");
	string fileName;
	cin >> fileName;
	LoadData(fileName + ".txt");
	Dispaly_New_Process_List();

	int counter_for_processors = 0;
	/*pUI->print_message("Please choose the mode you want\n 1- for Interactive Mode \n 2- for Step by Step Mode \n 3- for Silent Mode");
	int mode;
	cin >> mode;*/


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
				for (int i = 0; i < size; i++) {
					Processors_List[i]->ScheduleAlgo();
				}


			}
		}

		//work_Steal(t_Step); // work stealing function





		
		pUI->output(this); 
		t_Step++;


	}
	

}

void Scheduler::Fork(int step, int forkprob , Processor* processor)
{
	srand(time(nullptr));
	if (processor->Processor_Type() == "FCFS_processor" && processor->get_run() != NULL && processor->get_run()->get_has_forked() != true) { // to make sure that the processor is FCFS and has a run currently and its run hadn't forked before 
		int random_number = rand() % 100;
		if (random_number <= forkprob) {
			// making a new process and add it to the shortestFCFS RDY list
			int random_Forked_pid = 900 + (std::rand() % 1000); // new pid (should be random ) for forked 
			Process* p = new Process(step, random_Forked_pid, processor->get_run()->get_remainnig_time(), 0); // setting new processs arguments 
			processor->get_run()->set_child_pointer(p); // setting the child pointer of the parent process to the new forked process
			processor->get_run()->set_has_forked(true); // setting the has forked to true
			Processor* x = get_shortest_FCFS();
			x->add_process(p);
			forking_counter++;

		}
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
		worksteal_counter++;

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

void Scheduler::print()
{
	ofstream outfile;
	outfile.open("output.txt");

	// Write first line
	outfile << "TT" << " " << "pid" << " " << "AT" << " " << "CT" << " " << "iod" << " " << "WT" << " " << "RT" << " " << "TRT\n";
	int s = TRM_Process_List.Count();
	// calculating averges 
	double sum_WT = 0;
	double sum_RT = 0;
	double sum_TRT = 0;
	for (int i = 0; i < s; i++) {
		Process* Process_to_be_written;
		TRM_Process_List.Dequeue(Process_to_be_written);
		sum_RT = sum_RT + Process_to_be_written->get_response_time();
		sum_WT = sum_WT + Process_to_be_written->get_Waiting_t();
		sum_TRT = sum_TRT + Process_to_be_written->get_turnaround_duration();
		outfile << Process_to_be_written->get_termination_time() << " " << Process_to_be_written->get_pid() << " " << Process_to_be_written->get_cpu_time() << " " << Process_to_be_written->get_totalIOD() << " " << Process_to_be_written->get_Waiting_t() << " " << Process_to_be_written->get_response_time()<< " " << Process_to_be_written->get_turnaround_duration() << " \n";
	}
	outfile << "---------------------------------------------------------------------\n";
	outfile << "Number of processes:  " << TRM_Process_List.Count() << "\n";
	outfile << "---------------------------------------------------------------------\n";
	outfile << "AVG WT = " << sum_WT / s << "  " << "AVG RT = " << sum_RT / s << "  " << "AVG TRT = " << sum_TRT / s << "  \n";
	double RTF_ratio = ((RTF) / s) * 100;
	double maxw_ratio = ((MaxW) / s) * 100;
	outfile << "Migration % :" << "  " << "RTF : " << abs(RTF_ratio) << "%   MaxW: " << abs(maxw_ratio) << "% \n";
	outfile << "Work steal %:  " << 100 * abs((worksteal_counter) / s) << "\n";
	outfile << "Forking %:  " << 100 * abs((forking_counter) / s) << "\n";
	outfile << "Killing %:  " << 100 * abs((Signal_Kill_List.Count()) / s) << "\n";
	outfile << "processors: " <<sizeof(Processors_List) << "\n";
	outfile << "Processors load" << "\n";
	int no_of_processors = sizeof(Processors_List);
	for (int i = 0; i < no_of_processors; i++) {
		Processor* p = Processors_List[i];
		outfile << "P" << p->get_number() << " : " << 100 * (p->get_busy_T() / sum_TRT) << "   ";
	}
	outfile << "\n";
	outfile << "Processors Utiliz" << "\n";
	int sum_Utiliz = 0;
	for (int i = 0; i < no_of_processors; i++) {
		Processor* p = Processors_List[i];
		outfile << "P" << p->get_number() << " : " << 100 * (p->get_busy_T() / (p->get_busy_T() + p->get_Idle_T())) << "   ";
		sum_Utiliz = sum_Utiliz + 100 * (p->get_busy_T() / (p->get_busy_T() + p->get_Idle_T()));
	}
	outfile << "average UTILIZ = " << (sum_Utiliz / s) * 100 << "\n";
	outfile.close();


}

