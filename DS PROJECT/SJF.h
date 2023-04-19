#pragma once
#include"PRIORITY_QUEUE.h"
#include"Process/Process.h"
#include"Processors/Processor.h"
class SJF_processor :public Processor
{
private:
	PriorityQueue SJF_Pqueue;
	Process* run;
	int counter;
public:
	SJF_processor(int id);
	void add_process(Process* p) override;
	void remove_process(Process* p) override;
	void ScheduleAlgo() override;
	bool IS_IDLE() override;
	int get_counter() const;
	Process* get_run() override;
	PriorityQueue  get_ready();

	string Processor_Type() override;
	void PrintReady() override;


};

