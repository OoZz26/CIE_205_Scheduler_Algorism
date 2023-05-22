#include "RR_processor.h"
#include"Scheduler.h"


RR_processor::RR_processor(int id, Scheduler* s,int T_s) : Processor(id, s)
{
	type = "RR_processor";
	Time_Slice = T_s;
	run = nullptr;
	counter = 0;
	counter1 = 0;

}

void RR_processor::add_process(Process* p)
{
	counter++;

	//if (RRqueue.IsEmpty()&& counter==1) {
	//	run = p;
	//	RRqueue.EnQueue(p);
	//}
	//else{ RRqueue.EnQueue(p); }
	RRqueue.Enqueue(p);


}

void RR_processor::remove_process(int id)
{
	

}

void RR_processor::ScheduleAlgo()
{



	if (RRqueue.IsEmpty() && IS_IDLE()) {
		return;
	}
	if (!RRqueue.IsEmpty() && IS_IDLE()) {
		RRqueue.Dequeue(run);
		//remove_process(run);
		run->set_state(2);
		cout << counter << endl;
		return;
	}
	if (!IS_IDLE()) {
		//not sure about the logic
		if (run->check_io_request(run->get_remainnig_time())) {
			run->set_state(3);
			run->set_remainnig_time(run->get_remainnig_time() - 1);
			ss->Add_to_BLK(run);
			run = nullptr;
			return;

		}
		if (run->get_remainnig_time() == 0) {
			run->set_state(4);
			ss->Add_to_TRM(run);
			run = nullptr;

			return;

		}



		else {
			if (counter1 < Time_Slice) {
				run->set_remainnig_time(run->get_remainnig_time() - 1);			
				++counter1;
				return;

			}
			else {
				run->set_state(1);

				RRqueue.Enqueue(run);
				run = nullptr;
				return;
			}




		}



	}

}
bool RR_processor::IS_IDLE()
{
	if (run) {
		cout << "false i" << endl;
		return false;

	}
	else {
		cout << "true i" << endl;
		return true;

	}

}

Queue<Process*> RR_processor::get_ready()
{
	return RRqueue;
}

string RR_processor::Processor_Type()
{
	return type;
}

Process* RR_processor::get_run()
{
	return run;
}

void RR_processor::set_run(Process* p)
{
	this->run = p;
}

void RR_processor::PrintReady()
{
	Node1<Process*>* R = nullptr;
		RRqueue.GetFront(R);
	cout << RRqueue.Count() << " RDY: ";
	while (R != nullptr)
	{
		cout << R->GetItem()->get_pid() << ", ";
		R = R->getNext();
	}
	cout << endl;
}


int RR_processor::RDY_Duration()
{

	Node1<Process*>* R = nullptr;
	RRqueue.GetFront(R);
	int cts = 0;

	while (R != nullptr)
	{
		cts += R->GetItem()->get_cpu_time();
		R = R->getNext();
	}
	return cts;
}

Process* RR_processor::get_fIrst_proces()
{
	Process* p;
	if (!RRqueue.IsEmpty()) {
		RRqueue.Dequeue(p);
		return p;
	}
	else {
		return nullptr;
	}
}

int RR_processor::get_busy_T()
{
	return busy_T;
}

int RR_processor::get_Idle_T()
{
	return Idle_T;
}

void RR_processor::increment_busy_time()
{

	if (run != NULL) {
		busy_T++;
	}
	else
	{
		Idle_T++;
	}

}

int  RR_processor::get_number()
{
	return number;
}

void RR_processor::set_number(int n)
{
	number = n;
}
