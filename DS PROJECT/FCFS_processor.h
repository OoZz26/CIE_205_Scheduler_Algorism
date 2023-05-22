#pragma once
#include"Process/Process.h"
#include"Processors/Processor.h"
#include"Data Structures/Linked_List.h"


//class Scheduler;
class FCFS_processor :public Processor
{
private:
	 
	Process* run;
	int counter;
	LinkedList<Process*> FCFS_linked_list;
	int busy_T = 0;
	int Idle_T = 0;
	int number;
	
public:

	FCFS_processor(int id, Scheduler* s);

	void add_process(Process* p) override;
	void remove_process(int id) override;
	void ScheduleAlgo() override;
	bool IS_IDLE() override;
	int get_counter() const;
	string Processor_Type() override;
	LinkedList<Process*> get_ready();
	Process* get_run() override;
	void set_run(Process* p) override;

	void PrintReady() override;
	int RDY_Duration() override;
	Process* get_fIrst_proces() override;
	int get_busy_T() override;
	int get_Idle_T() override;
	void increment_busy_time() override;
	int get_number()override;
	void set_number(int n) override;
	void KillProcess(int pid, int killtime);
};

