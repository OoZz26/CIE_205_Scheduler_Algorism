#pragma once
#include"Process/Process.h"
#include"Processors/Processor.h"
#include"Data Structures/QUEUE.h"
class RR_processor :public Processor
{

private:
	int Time_Slice;
	Queue< Process*> RRqueue;

public:

	RR_processor(int id, int T_s) ;
	void add_process(Process* p) override;
	void remove_process(Process* p) override;
	void ScheduleAlgo() override;
};

