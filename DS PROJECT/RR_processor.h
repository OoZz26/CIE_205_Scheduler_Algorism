#pragma once
#include"Process/Process.h"
#include"Processors/Processor.h"
#include"Data Structures/QUEUE.h"



//class Scheduler;
class RR_processor :public Processor
{

private:
	Process* run;
	int counter;
	int Time_Slice;
	int counter1;
	int busy_T = 0;
	int Idle_T = 0;
	int number;
	
	Queue< Process*> RRqueue;

public:
	RR_processor(int id, Scheduler* s,int T_s);
	void add_process(Process* p) override;
	void remove_process(int id) override;
	void ScheduleAlgo() override;
	bool IS_IDLE() override;
	Queue< Process*>  get_ready();
	string Processor_Type() override;
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
};

