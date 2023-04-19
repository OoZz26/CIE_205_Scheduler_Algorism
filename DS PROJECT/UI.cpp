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

void UI::output(Scheduler* sched){
   cout << "Current Timestep: " << sched->GettimeStep()<< endl;
    cout << "------------------------- RDY Processes ---------------------------" << endl;
    // Print ready processes for each processor
    Queue<Processor*> plist = sched->GetProcessorList();

        Node1<Processor*>* temp = plist.GetFront();
        int c = 1;
        Queue<string> RunList;
        while (temp != nullptr)
        {
            cout << "Processor " << c; 
            Processor* P = temp->GetItem();
            cout<< " [" << P->Processor_Type() << "]: ";
            P->PrintReady();
            Process* run = P->get_run();
            int id = run->get_pid();

            string run_P = to_string(id) + "(P" +to_string(c) + ")";
            RunList.Enqueue(run_P);

        }
        cout << endl;
    

    // Print blocked processes
    cout << "------------------ BLK processes -----------------" << endl;
    Queue<Process*> blklist = sched->GetBLKList();


    Node1<Process*>* B = blklist.GetFront();
    cout << blklist.Count() << " BLK: ";
    while (B != nullptr)
    {
        cout  << B->GetItem()->get_pid() << ", ";
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