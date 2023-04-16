#include "RR_processor.h"

RR_processor::RR_processor(int id, int T_s) : Processor(id)
{
	Time_Slice = T_s;
}

void RR_processor::add_process(Process* p)
{
	RRqueue.EnQueue(p);
}

void RR_processor::remove_process(Process* p)
{
}

void RR_processor::ScheduleAlgo()
{
	if (RRqueue.IsEmpty()) {
		cout << "there no process";
	}
	else {
		cout << "oooooooooooooooo"<<endl;

		Process* Fork = RRqueue.FRONT();
		RRqueue.DeQueue();
		if (Fork->get_cpu_time() == 0) {
			//shift the process to end queue
		}
		else {
			for (int i = 1; i <= Time_Slice; i++) {
				cout << "-----------------------"<<endl;
				Fork->set_cpu_time(Fork->get_cpu_time() - 1);
				if (Fork->get_cpu_time() == Fork->get_io_request_time()) {
					// move to bloked queue
					ScheduleAlgo();
					break;
				}
				if (Fork->get_cpu_time() == 0) {
					//shift the process to end queue
					ScheduleAlgo();
					break;
				}
			}
			if (Fork->is_ready(Fork)) {
				RRqueue.EnQueue(Fork);
				ScheduleAlgo();
			}
			else
			{
				ScheduleAlgo();
			}
		}
	}
}