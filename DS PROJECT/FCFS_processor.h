#pragma once
#include"Process/Process.h"
#include"Processors/Processor.h"
#include"Data Structures/Linked_List.h"
#include"Scheduler.h"
class FCFS_processor :public Processor
{
private:
	LinkedList<Process*> FCFS_linked_list;
public:
	FCFS_processor(int id);
	void add_process(Process* p) override;
	void remove_process(Process* p) override;
	void ScheduleAlgo() override;
};

