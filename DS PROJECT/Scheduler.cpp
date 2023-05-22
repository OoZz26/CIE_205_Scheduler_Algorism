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
		
		/*int KillTime, ProcessID;

		while (!infile.eof()) {
			infile >> KillTime >> ProcessID;
			SIGKILL k = { KillTime, ProcessID };
			Signal_Kill_List.Enqueue(k);
			noOf_Signal_Kill++;
		}*/
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

void Scheduler::Check_KILLSIG()
{
	Process* p = nullptr;
	Processor* p1 = nullptr;
	SIGKILL s;
	Signal_Kill_List.Peek(s);
	int ptime = s.ST;
	int pid = s.SKPID;
	while (Signal_Kill_List.Count() != 0)
	{
		if (ptime == t_Step && p1->get_run()->get_pid() == pid)
		{
			if (p1->Processor_Type() == "FCFS_processor")
			{
				FCFS_processor* pro = nullptr;
				Signal_Kill_List.Dequeue(s);

				
				int p = s.SKPID;
				int t = s.ST;
				pro->KillProcess(p, t);
			}
		}
		else {
			return;
		}
	}



	/*Node1<SIGKILL>* Sig = Signal_Kill_List.GetFront();
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
	}*/
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
		TMP->Enqueue(empty);
	}

	while (TMP->Dequeue(empty)) {
		BLK_Process_List.Enqueue(empty);
	}
	delete TMP;

}




void Scheduler::Run_to_TRM()
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



void Scheduler::Migrate_RR_to_SJF(Process* p) {
	int size = Processors_List.Count();
	for (int i = 0; i < size; i++) {
		Processor* proc = Processors_List.GetFront();
		Processors_List.Dequeue();

		//checks whether the current processor is SJF and whether it is currently idle
		if (proc->Processor_Type() == "SJF_processor" && proc->IS_IDLE()) {
			//checks whether the remaining execution time of process is <= to the RTF threshold
			if (p->get_cpu_time() - p->get_remaining_time() <= RTF) {
				// If so, migrate the process into the queue_processes of the SJF 
				proc->add_process(p);
				return;
			}
		}
		Processors_List.Enqueue(proc);
	}
}

void Scheduler::Migrate_FCFS_to_RR(Process* p, int MaxW) {

	// checks whether the total wait time of process > MaxW threshhold
	if (p->get_wait_time() > MaxW) {
		int size = Processors_List.Count();
		for (int i = 0; i < size; i++) {
			Processor* proc = Processors_List.GetFront();
			Processors_List.Dequeue();

			//checks whether the current processor is RR and whether it is currently idle
			if (proc->Processor_Type() == "RR_processor" && proc->IS_IDLE()) {
				// If so, migrate the process into the queue_processes of the RR 
				proc->add_process(p);
				return;
			}
			Processors_List.Enqueue(proc);
		}
	}
}



void Scheduler::killOrphanProcesses(Queue<Processor>& processors) {
	// Iterate through all FCFS processors
	while (!processors.IsEmpty()) {
		Processor* processor = processors.GetFront()->GetItemReference();
		processors.Dequeue();
		if (processor->Processor_Type() != "FCFS_processor") {
			continue;
		}

		// Iterate through all processes in the processor's ready and running queues
		Queue<Process*> readyQueue = processor->get_ready();
		while (!readyQueue.IsEmpty()) {
			Process* process = readyQueue.GetFront();
			readyQueue.Dequeue();
			if (process->isOrphan()) {
				// Kill the orphan process and move it to the TRMlist
				process->set_state(4); // Setstate to TERMINATED
				processor->remove_process(process);
				processor->addToTerminatedList(process);

				// Kill all of its children and move them to the TRM list
				Queue<Process*> children = process->getChildren();
				while (!children.IsEmpty()) {
					Process* child = children.GetFront();
					children.Dequeue();
					process->set_state(4); // Set state to TERMINATED
					processor->remove_process(child);
					processor->addToTerminatedList(child);
				}
			}
		}

		Queue<Process*> runningQueue = processor->getRunningQueue();
		while (!runningQueue.IsEmpty()) {
			Process* process = runningQueue.GetFront();
			runningQueue.Dequeue();
			if (process->isOrphan()) {
				// Kill the orphan process and move it to the TRM list
				process->set_state(4); // Set state to TERMINATED
				processor->remove_process(process);
				processor->addToTerminatedList(process);

				// Kill all of its children and move them to the TRM list
				Queue<Process*> children = process->getChildren();
				while (!children.IsEmpty()) {
					Process* child = children.GetFront();
					children.Dequeue();
					process->set_state(4); // Set state to TERMINATED
					processor->remove_process(child);
					processor->addToTerminatedList(child);
				}
			}
		}
		// Add the updated processor back to the queue
		processors.Enqueue(*processor);
	}
}

//void Scheduler::print(Queue<Process*> TRM_Process_List)
//{
//	ofstream output;
//	output.open("OUTPUT.txt", ios::trunc);
//
//	output << "TT PID CT IO_D WT RT TRT\n";
//
//	/*selectionSort(trmList);*/
//
//	int sumWT = 0, sumRT = 0, sumTRT = 0;
//
//	for (int i = 0; i < trmList->getLength(); i++) {
//		trmList->getItem(i)->setRT();
//		trmList->getItem(i)->setTRT();
//		trmList->getItem(i)->setWT();
//
//		sumWT += trmList->getItem(i)->getWT();
//		sumRT += trmList->getItem(i)->getRT();
//		sumTRT += trmList->getItem(i)->getTRT();
//
//
//		output << trmList->getItem(i)->getTT() << " " << trmList->getItem(i)->getPID() << " " << trmList->getItem(i)->getCPUtime() << " " << trmList->getItem(i)->getTotal_IOD() << " ";
//		output << trmList->getItem(i)->getWT() << " " << trmList->getItem(i)->getRT() << " " << trmList->getItem(i)->getTRT() << "\n";
//	}
//
//	avgWT = sumWT / numOFProcesses;
//	avgRT = sumRT / numOFProcesses;
//	avgTRT = sumTRT / numOFProcesses;
//
//	output << "Processes: " << numOFProcesses << "\n";
//	output << "AVG WT = " << avgWT << "   " << "AVG RT = " << avgRT << "   " << "AVG TRT = " << avgTRT << "\n";
//
//	output << "Migration %: " << "\n";
//	output << "Work Steal %: " << "\n";
//	output << "Forked Processes %: " << "\n";
//	output << "Killed Processes %: " << "\n" << "\n";
//
//	output << "Processors: " << (numFCFS + numSJF + numRR) << " [" << numFCFS << " FCFS, " << numSJF << " SJF, " << numRR << " RR]\n";
//
//	output << "Processors Load\n";
//	output << "P1: " << "P1: " << "P1: " << "P1: " << "\n";
//
//	output << "Processors Utiliz\n";
//	output << "P1: " << "P1: " << "P1: " << "P1: " << "\n";
//
//	output << "AVG Utilization = ";
//
//
//
//
//	output.close();
//}
//
