#include "FCFS_processor.h"

FCFS_processor::FCFS_processor(int id):Processor(id)
{}

void FCFS_processor::add_process(Process * p)
{
	FCFS_linked_list.InsertEnd(p);
}

void FCFS_processor::remove_process(Process* p)
{
	FCFS_linked_list.DeleteNode(p);
}

void FCFS_processor::ScheduleAlgo()
{
	if (FCFS_linked_list.ISEMPTY()) {
		cout << "done" << endl;
	}
	else {
		Process* Fork = FCFS_linked_list.Front();
		FCFS_linked_list.DeleteFirst();
		srand(time(0));
		int val = 1 + rand() % (35 - 1 + 1);
		if (val >= 1 && val <= 15)
		{
			cout << "move to block list" << endl;
			cout << val;
			Scheduler S;
			S.Add_to_BLK(Fork);

			
			//move to block list

		}
		else {
			if (val > 15 && val <= 25) {
				add_process(Fork);
				cout << "DDF" << endl;
				cout << val;
			}
			else {
				//add to terminated list
				cout << "/add to terminated list" << endl;
				cout << val;
			}
		}




		//for (int i = 0; i < Fork->get_cpu_time(); i++) {
		//	cout << "-----------------------" << endl;
		//	Fork->set_cpu_time(Fork->get_cpu_time() - 1);
		//	if (Fork->get_cpu_time() == Fork->get_io_request_time()) {
		//		// move to bloked queue
		//		ScheduleAlgo();
		//		break;
		//	}
		//	if (Fork->get_cpu_time() == 0) {
		//		//shift the process to end queue
		//		ScheduleAlgo();
		//		break;
		//	}
		//}
	}
}

