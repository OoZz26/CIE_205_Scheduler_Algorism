#pragma once
#include"PRIORITY_QUEUE.h"
#include"Process/Process.h"
#include"Processors/Processor.h"
class SJF_processor :public Processor
{
private:
	PriorityQueue<Process*> SJF_LInkedlist;
public:
	SJF_processor(int id);
	void add_process(Process* p) override;
	void remove_process(Process* p) override;
	void ScheduleAlgo() override;

};

