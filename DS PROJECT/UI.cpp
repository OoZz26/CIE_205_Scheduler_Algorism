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
  
}


















//class UI {
//public:
//    void input() {
//        std::cout << "Press any key to continue..." << std::endl;
//        std::cin.ignore(); // waits for user to input a key
//    }
//
//    void output(Process* process_list, Processor* processor_list) {
//        // print header
//        cout << "PROCESS LIST" << endl;
//        cout << "ID\tArrival\tBurst" << endl;
//
//        // loop through process list and print data
//        Process* current_process = process_list;
//        while (current_process != nullptr) {
//            std::cout << current_process->getID() << "\t" << current_process->getArrivalTime() << "\t" << current_process->getBurstTime() << std::endl;
//            current_process = current_process->getNext();
//        }
//
//        std::cout << std::endl;
//
//        // print header
//        std::cout << "PROCESSOR LIST" << std::endl;
//        std::cout << "ID\tCurrent Process" << std::endl;
//
//        // loop through processor list and print data
//        Processor* current_processor = processor_list;
//        while (current_processor != nullptr) {
//            std::cout << current_processor->getID() << "\t";
//            if (current_processor->getCurrentProcess() != nullptr) {
//                std::cout << current_processor->getCurrentProcess()->getID() << std::endl;
//            }
//            else {
//                std::cout << "Idle" << std::endl;
//            }
//            current_processor = current_processor->getNext();
//        }
//
//        std::cout << std::endl;
//    }
//};


//#pragma once
//#include <iostream>
//#include"Data Structures/QUEUE.h"
//using namespace std;
//
//class UI {
//public:
//    UI() = default;
//    // Function to read input from the user
//    void readInput() {
//        // Read input from the user using std::cin
//        // Store the input in appropriate data structures
//    }
//    // Function to print the output screen
//    void printOutput(const Queue<Process>& processQueue,
//        const list<Processor>& processorList) {
//        // Clear the screen
//        system("cls");
//        // Print the header
//        cout << "Timestep: " << timestep << std::endl;
//        cout << "Processes in Queue: " << processQueue.size() << std::endl;
//        cout << "Processors: " << processorList.size() << std::endl;
//        // Print the process queue
//        cout << "Process Queue: ";
//        for (const auto& process : processQueue) {
//            std::cout << process << " ";
//        }
//        cout << std::endl;
//        // Print the processors
//        cout << "Processors: ";
//        for (const auto& processor : processorList) {
//            cout << processor << " ";
//        }
//        cout << std::endl;
//        // Increment the timestep
//        timestep++;
//    }
//private:
//    int timestep = 0;
//};
