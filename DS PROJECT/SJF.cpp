//#include "SJF.h"
//#include "FCFS_processor.h"
//
//SJF_processor::SJF_processor(int id) :Processor(id)
//{}
//
//void SJF_processor::add_process(Process* p)
//{
//	SJF_LInkedlist.InsertEnd(p);
//}
//
//void SJF_processor::remove_process(Process* p)
//{
//	SJF_LInkedlist.DeleteNode(p);
//}
//
//void SJF_processor::ScheduleAlgo()
//{
//	if (SJF_LInkedlist.ISEMPTY()) {
//		cout << "done" << endl;
//	}
//	else {
//		Process* Fork = SJF_LInkedlist.Front();
//		SJF_LInkedlist.DeleteFirst();
//		srand(time(0));
//		int val = 2 + rand() % (35 - 2 + 1);
//		if (val >= 1 && val <= 15)
//		{
//			cout << "move to block list" << endl;
//			cout << val;
//			//move to block list
//
//		}
//		else {
//			if (val > 15 && val <= 25) {
//				add_process(Fork);
//				cout << "DDF" << endl;
//				cout << val;
//			}
//			else {
//				//add to terminated list
//				cout << "/add to terminated list" << endl;
//				cout << val;
//			}
//		}
//
//
//
//
//		//for (int i = 0; i < Fork->get_cpu_time(); i++) {
//		//	cout << "-----------------------" << endl;
//		//	Fork->set_cpu_time(Fork->get_cpu_time() - 1);
//		//	if (Fork->get_cpu_time() == Fork->get_io_request_time()) {
//		//		// move to bloked queue
//		//		ScheduleAlgo();
//		//		break;
//		//	}
//		//	if (Fork->get_cpu_time() == 0) {
//		//		//shift the process to end queue
//		//		ScheduleAlgo();
//		//		break;
//		//	}
//		//}
//	}
//}
//
