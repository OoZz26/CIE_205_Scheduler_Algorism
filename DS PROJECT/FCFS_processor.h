#pragma once
#include"Process/Process.h"
#include"Processors/Processor.h"
#include"Data Structures/Linked_List.h"
#include"Scheduler.h"
class FCFS_processor :public Processor
{
private:
	Process* run;
	int counter;
	LinkedList<Process*> FCFS_linked_list;
public:
	FCFS_processor(int id);
	void add_process(Process* p) override;
	void remove_process(Process* p) override;
	void ScheduleAlgo() override;
	bool IS_IDLE() override;
	int get_counter() const;
	Process* get_run();
};

