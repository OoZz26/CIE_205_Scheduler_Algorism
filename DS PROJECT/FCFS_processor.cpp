#include "FCFS_processor.h"

FCFS_processor::FCFS_processor(int id) :Processor(id)
{
	type = "FCFS_processor";
}

void FCFS_processor::add_process(Process* p)
{
	counter++;
	FCFS_linked_list.InsertEnd(p);
}

void FCFS_processor::remove_process(Process* p)
{
	counter--;
	FCFS_linked_list.DeleteNode(p);
}

void FCFS_processor::ScheduleAlgo()
{
	if (FCFS_linked_list.ISEMPTY() || !IS_IDLE()) {
		cout << "done" << endl;
	}
	else {
		if (counter == 0) {
			cout << "mmmmmm" << endl;
		}
		else {
			cout << "--------------------------------------------" << endl;
			if (IS_IDLE() == true) {

				cout << "--------------------///////////------------------------" << endl;
				srand(time(0));
				int val = 1 + rand() % (35 - 1 + 1);
				run = FCFS_linked_list.Front();
				FCFS_linked_list.DeleteFirst();
				counter--;
				if (val >= 1 && val <= 15)
				{
					cout << "move to block list" << endl;
					cout << val;
					run = nullptr;
					//ScheduleAlgo();
					//move to block list

				}
				else {
					if (val > 15 && val <= 25) {
						add_process(run);
						cout << "DDF" << endl;
						counter++;
						cout << val;
						run = nullptr;
						//ScheduleAlgo();
					}
					else {
						//add to terminated list
						cout << "/add to terminated list" << endl;
						cout << val;
						run = nullptr;
						//ScheduleAlgo();
					}
				}

			}
			else {
				//IS_IDLE();
				cout << "not Idle or empty" << endl;
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

bool FCFS_processor::IS_IDLE()
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

int FCFS_processor::get_counter() const
{
	return counter;
}

string FCFS_processor::Processor_Type()
{
	return type;
}

LinkedList<Process*> FCFS_processor::get_ready()
{
	return FCFS_linked_list;
}

Process* FCFS_processor::get_run()
{
	return run;
}

