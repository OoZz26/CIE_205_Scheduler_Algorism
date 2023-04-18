#include "SJF.h"
SJF_processor::SJF_processor(int id) :Processor(id)
{
    run = nullptr;
    counter = 0;
}
void SJF_processor::add_process(Process* p)
{
    SJF_Pqueue.enqueue(p);
    counter++;
}
void SJF_processor::remove_process(Process* p)
{
}
void SJF_processor::ScheduleAlgo()
{
    if (SJF_Pqueue.IsEmpty()) {
        run = nullptr;
        throw "empty queue";
    }
    else {

        Process* Fork = SJF_Pqueue.dequeue();
        run = SJF_Pqueue.dequeue();
        srand(time(0));
        int val = 2 + rand() % (35 - 2 + 1);
        if (val >= 1 && val <= 15)
        {
            //Processor_Scheduler->Add_to_BLK(Fork);

            cout << "move to block list" << endl;
            cout << val;


            //move to block list

        }
        else {
            if (val > 15 && val <= 25) {
                add_process(Fork);
                cout << "DDF" << endl;
                cout << val;
            }
            else {
                //add to terminated list
                //Processor_Scheduler->Add_to_TRM(Fork);
                cout << "/add to terminated list" << endl;
                cout << val;
            }
        }

    }
}

int SJF_processor::get_counter() const
{
    return counter;
}

Process* SJF_processor::get_run()
{
    return run;
}