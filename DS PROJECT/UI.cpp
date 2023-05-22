#pragma once
#include "UI.h"
#include <iostream>
#include "Process/Process.h" // assuming you have a separate header file for your process class
#include "Processors/Processor.h" // assuming you have a separate header file for your processor class
#include "Data Structures/Linked_List.h"
#include "Data Structures/QUEUE.h"

using namespace std;

void UI::input() {
    cout << "Press any key to continue..." << endl;
    cin.ignore();
}

void UI::print_message(string s)
{
    cout << s << endl;
}


void UI::output(Scheduler* sched) {
    cout << "Current Timestep: " << sched->GettimeStep() << endl;
    cout << "------------------------- RDY Processes ---------------------------" << endl;
    // Print ready processes for each processor
    Processor** plist = sched->GetProcessorList();
    Queue<string> RunList;

    for (int i = 1; i < sched->size + 1; i++)
    {
        cout << "Processor " << i;
        cout << " [" << plist[i - 1]->Processor_Type() << "]: ";
        plist[i - 1]->PrintReady();
        Process* run = plist[i - 1]->get_run();
        if (run)
        {
            int id = run->get_pid();
            string run_P = to_string(id) + "(P" + to_string(i) + ")";
            RunList.Enqueue(run_P);
        }
        
        
    }

    cout << endl;

    // Print blocked processes
    cout << "------------------ BLK processes -----------------" << endl;
    Queue<Process*> blklist = sched->GetBLKList();


    Node1<Process*>* B = blklist.GetFront();
    cout << blklist.Count() << " BLK: ";
    while (B != nullptr)
    {
        cout << B->GetItem()->get_pid() << ", ";
        B = B->getNext();
    }
    cout << endl;



    // Print running processes



    Node1<string>* RL = RunList.GetFront();
    cout << RunList.Count() << " Run: ";
    while (RL != nullptr)
    {
        cout << RL->GetItem() << ", ";
        RL = RL->getNext();
    }
    cout << endl;


    cout << "------------------ TRM processes -----------------" << endl;
    Queue<Process*> trmlist = sched->GetTRMList();


    Node1<Process*>* TL = trmlist.GetFront();
    cout << trmlist.Count() << " TRM: ";
    while (TL != nullptr)
    {
        cout << TL->GetItem()->get_pid() << ", ";
        TL = TL->getNext();
    }
    cout << endl;

    input();
    system("cls");

}