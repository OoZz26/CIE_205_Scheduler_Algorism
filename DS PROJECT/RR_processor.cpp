#include "RR_processor.h"
#include"Scheduler.h"


RR_processor::RR_processor(int id, Scheduler* s,int T_s) : Processor(id, s)
{
	type = "RR_processor";
	Time_Slice = T_s;
	run = nullptr;
	counter = 0;
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

void RR_processor::remove_process(Process* p)
{
	counter--;
}

void RR_processor::ScheduleAlgo()
{



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

	//		RRqueue.Dequeue(run);
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


	//	if (Fork->get_cpu_time() == 0) {
	//		//shift the process to end queue
	//	}
	//	else {
	//		for (int i = 1; i <= Time_Slice; i++) {
	//			cout << "-----------------------"<<endl;
	//			Fork->set_cpu_time(Fork->get_cpu_time() - 1);
	//			if (Fork->get_cpu_time() == Fork->get_io_request_time()) {
	//				// move to bloked queue
	//				ScheduleAlgo();
	//				break;
	//			}
	//			if (Fork->get_cpu_time() == 0) {
	//				//shift the process to end queue
	//				ScheduleAlgo();
	//				break;
	//			}
	//		}
	//		if (Fork->is_ready(Fork)) {
	//			RRqueue.EnQueue(Fork);
	//			ScheduleAlgo();
	//		}
	//		else
	//		{
	//			ScheduleAlgo();
	//		}
	//	}


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

void RR_processor::PrintReady()
{
	Node1<Process*>* R = RRqueue.GetFront();
	cout << RRqueue.Count() << " RDY: ";
	while (R != nullptr)
	{
		cout << R->GetItem()->get_pid() << ", ";
		R = R->getNext();
	}
	cout << endl;
}
