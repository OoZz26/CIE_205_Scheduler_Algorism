#include "FCFS_processor.h"
#include"Scheduler.h"

FCFS_processor::FCFS_processor(int id, Scheduler* s) :Processor(id,s)
{
	run = nullptr;
	counter = 0;
	type = "FCFS_processor";
}



void FCFS_processor::add_process(Process* p)
{
	counter++;
	FCFS_linked_list.InsertEnd(p);
}

void FCFS_processor::remove_process(int id)
{

	/*if (run->get_pid() == id) {
		run->set_state(4);
		run = nullptr;
		return;
	}
	else {
		Node<Process*>* F;
		FCFS_linked_list.GetHead(F);
		Process* m = nullptr;
		if (F->getItem()->get_pid() == id) {
			m = FCFS_linked_list.Front();
			FCFS_linked_list.DeleteFirst();
			
			m->set_state(4);
			ss->Add_to_TRM(m);

			return;
		}
		while (F->getNext(F)->getNext(F) != nullptr)
		{
			if (F-getNext(F)->getItem()->get_pid() == id) {
				m = F->getNext(F)->getItem();
				F->setNext(F->getNext(F)->getNext());
				m->set_state(4);
				ss->Add_to_TRM(m);
				break;

			}
			F->getNext(F);
		}
	}
	cout << endl;*/


	/*counter--;
	FCFS_linked_list.DeleteNode(p);*/
}

void FCFS_processor::ScheduleAlgo()
{
	if (FCFS_linked_list.ISEMPTY() && IS_IDLE()) {
		return;
	}
	if (!FCFS_linked_list.ISEMPTY() && IS_IDLE()) {
		run = FCFS_linked_list.Front();
		FCFS_linked_list.DeleteFirst();
		run->set_state(2);
		return;
	}
	if (!IS_IDLE()) {
		if (run->check_io_request(run->get_remainnig_time())) {
			run->set_state(3);
			run->set_remainnig_time(run->get_remainnig_time() - 1);
			ss->Add_to_BLK(run);
			run = nullptr;
			return;

		}
		if (run->get_remainnig_time() == 0) {
			run->set_state(4);
			run->set_remainnig_time(run->get_remainnig_time() - 1);
			ss->Add_to_TRM(run);
			run = nullptr;
			return;

		}
		else {
			
			run->set_remainnig_time(run->get_remainnig_time() - 1);
			return;
		}


	}


	//if (FCFS_linked_list.ISEMPTY() || !IS_IDLE()) {
	//	cout << "done" << endl;
	//}
	//else {
	//	if (counter == 0) {
	//		cout << "mmmmmm" << endl;
	//	}
	//	else {
	//		cout << "--------------------------------------------" << endl;
	//		if (IS_IDLE() == true) {

	//			cout << "--------------------///////////------------------------" << endl;
	//			srand(time(0));
	//			int val = 1 + rand() % (35 - 1 + 1);
	//			run = FCFS_linked_list.Front();
	//			FCFS_linked_list.DeleteFirst();
	//			counter--;
	//			if (val >= 1 && val <= 15)
	//			{
	//				cout << "move to block list" << endl;
	//				cout << val;
	//				run = nullptr;
	//				//ScheduleAlgo();
	//				//move to block list

	//			}
	//			else {
	//				if (val > 15 && val <= 25) {
	//					add_process(run);
	//					cout << "DDF" << endl;
	//					counter++;
	//					cout << val;
	//					run = nullptr;
	//					//ScheduleAlgo();
	//				}
	//				else {
	//					//add to terminated list
	//					cout << "/add to terminated list" << endl;
	//					cout << val;
	//					run = nullptr;
	//					//ScheduleAlgo();
	//				}
	//			}

	//		}
	//		else {
	//			//IS_IDLE();
	//			cout << "not Idle or empty" << endl;
	//		}
	//	}




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

bool FCFS_processor::IS_IDLE()
{
	if (run) {
		return false;

	}
	else {
		return true;
	}
}

int FCFS_processor::get_counter() const
{	return counter;
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

void FCFS_processor::set_run(Process* p)
{
	this->run = p;
}

void FCFS_processor::PrintReady()
{

	Node<Process*>* F;
	FCFS_linked_list.GetHead(F);
	cout << FCFS_linked_list.GetCount() << " RDY: ";
	while (F != nullptr)
	{
		cout << F->getItem()->get_pid() << ", ";
		F->getItem();
		F->getNext(F);
	}
	cout << endl;
}


int FCFS_processor::RDY_Duration()
{
	Node<Process*>* F;
	 FCFS_linked_list.GetHead(F);
	int cts = 0;

	while (F != nullptr)
	{
		cts += F->getItem()->get_cpu_time();
		
		F->getNext(F);
	}
	return cts;
}

Process* FCFS_processor::get_fIrst_proces()
{
	
	if (!FCFS_linked_list.ISEMPTY()) {
		Process* p = FCFS_linked_list.Front();
		FCFS_linked_list.DeleteFirst();
		return p;
	}
	else {
		return nullptr;
	}
}
void FCFS_processor::KillProcess(int pid, int killtime) {

	Process* KilledP = nullptr;

	if (run != nullptr && run->get_pid() == pid && ss->GettimeStep() == killtime) {
		KilledP =run;

		run = nullptr;
		SIGKILL s1;
		ss->Signal_Kill_List.Dequeue(s1);


		
		ss->Add_to_TRM(KilledP);
	}
	else {
		
		for (int i = 0; i < FCFS_linked_list.GetCount(); i++)
		{
			Node<Process*>* F = nullptr;
			FCFS_linked_list.GetHead(F);


			if (F->getItem()->get_pid() == pid)
			{
				KilledP = F->getItem();
				FCFS_linked_list.DeleteNode(KilledP);
				KilledP->set_state(4);
				ss->Add_to_TRM(KilledP);
			}
			else {
				FCFS_linked_list.DeleteFirst();
				FCFS_linked_list.InsertEnd(F->getItem());
			}
		}
	}


}

