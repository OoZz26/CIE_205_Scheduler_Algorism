#include "SJF.h"
#include"Scheduler.h"



SJF_processor::SJF_processor(int id, Scheduler* s) :Processor(id, s)
{
	type = "SJF_processor";
	run = nullptr;
	counter = 0;
}

void SJF_processor::add_process(Process* p)
{
	SJF_Pqueue.enqueue(p);
	counter++;
} 
void SJF_processor::remove_process(Process* p)
{
	counter--;
}
void SJF_processor::ScheduleAlgo()

{
	 

	if (SJF_Pqueue.IsEmpty() && IS_IDLE()) {
		return;
	}
	if (!SJF_Pqueue.IsEmpty() && IS_IDLE()) {
		SJF_Pqueue.dequeue(run);
		remove_process(run);
		run->set_state(2);
		cout << counter << endl;
		return;
	}
	if (!IS_IDLE()) {
		if (run->check_io_request(run->get_cpu_time())) {
			run->set_state(3);
			run->set_cpu_time(run->get_cpu_time() - 1);
			ss->Add_to_BLK(run);
			run = nullptr;
			return;

		}
		if (run->get_cpu_time() == 0) {
			run->set_state(4);
			run->set_cpu_time(run->get_cpu_time() - 1);
			ss->Add_to_TRM(run);
			run = nullptr;

			return;

		}
		else {
			run->set_cpu_time(run->get_cpu_time() - 1);
			return;


		}


	}
		//if (counter == 0) {
		//	cout << "mmmmmm" << endl;
		//}
		//else {
		//	cout << "--------------------------------------------" << endl;
		//	if (IS_IDLE() == true) {

		//		cout << "--------------------///////////------------------------" << endl;
		//		srand(time(0));
		//		int val = 1 + rand() % (35 - 1 + 1);
		//		cout << val << endl;

		//		SJF_Pqueue.dequeue(run);
		//		counter--;
		//		if (val >= 1 && val <= 15)
		//		{
		//			cout << "move to block list" << endl;
		//			cout << val;
		//			run = nullptr;
		//			//ScheduleAlgo();
		//			//move to block list

		//		}
		//		else {
		//			if (val > 15 && val <= 25) {
		//				add_process(run);
		//				cout << "DDF" << endl;
		//				counter++;
		//				cout << val;
		//				run = nullptr;
		//				//ScheduleAlgo();
		//			}
		//			else {
		//				//add to terminated list
		//				cout << "/add to terminated list" << endl;
		//				cout << val;
		//				run = nullptr;
		//				//ScheduleAlgo();
		//			}
		//		}

		//	}
		//	else {
		//		//IS_IDLE();
		//		cout << "not Idle or empty" << endl;
		//	}
		//}

}
bool SJF_processor::IS_IDLE()
{
	if (run) {
		//cout << "false i" << endl;
		return false;

	}
	else {
		//cout << "true i" << endl;
		return true;

	}

}

int SJF_processor::get_counter() const
{
	return counter;
}

Process* SJF_processor::get_run()
{
	
	return run;
}

void SJF_processor::set_run(Process* p)
{
	this->run = p;
}

PriorityQueue SJF_processor::get_ready()
{
	return SJF_Pqueue;
}

string SJF_processor::Processor_Type()
{
	return type;
}

void SJF_processor::PrintReady()
{
	Node2* R = SJF_Pqueue.GetHead();
	cout << SJF_Pqueue.GetCount() << " RDY: ";
	while (R != nullptr)
	{
		cout << R->getItem()->get_pid() << ", ";
		R = R->getNext();
	}
	cout << endl;
}


int SJF_processor::RDY_Duration()
{

	Node2* R = SJF_Pqueue.GetHead();
	int cts = 0;

	while (R != nullptr)
	{
		cts += R->getItem()->get_cpu_time();
		R = R->getNext();
	}
	return cts;
}

Process* SJF_processor::get_fIrst_proces()
{
	Process* p = new Process();
	if (!SJF_Pqueue.IsEmpty()) {
		SJF_Pqueue.dequeue(p);
		return p;
	}
	else {
		return nullptr;
	}
	
}
