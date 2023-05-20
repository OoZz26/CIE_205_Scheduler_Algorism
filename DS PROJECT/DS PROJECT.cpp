#include<iostream>
#include"Data Structures/Linked_List.h"
#include"Data Structures/QUEUE.h"
#include"Process/Process.h"
#include"RR_processor.h"
#include"FCFS_processor.h"
#include"Scheduler.h"
#include "SJF.h"
#include <iostream>
#include"UI.h"
#include<fstream>
#include<string>
#include <sstream>
using namespace std;
int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    PriorityQueue p1;
    Scheduler* S1 = new Scheduler();

    Process* processes = new Process[num_processes];
    FCFS_processor F1(4,S1);
    SJF_processor S( 8, S1);
    RR_processor R(9, S1,1);


    for (int i = 0; i < num_processes; i++) {
        int arrival_time, pid, cpu_time, io_request_number;
        cout << "Enter process #" << i + 1 << " Arrival time: ";
        cin >> arrival_time;

        cout << "Enter process #" << i + 1 << " ID: ";
        cin >> pid;

        cout << "Enter process #" << i + 1 << " CPU time: ";
        cin >> cpu_time;

        cout << "Enter process #" << i + 1 << " Number of I/O requests: ";
        cin >> io_request_number;

        

        
        processes[i].set_arrival_time(arrival_time);
        processes[i].set_id(pid);
        processes[i].set_cpu_time(cpu_time);
        processes[i].set_io_request_number(io_request_number);



//
//        R1.add_process(&processes[i]);
//        R1.ScheduleAlgo();
        //F1.add_process(processes);
       
    }

    //Process* processes = new Process(4, 1, 10);
    F1.ScheduleAlgo();
    R.ScheduleAlgo();
    S.ScheduleAlgo();

    
    
    
    



    //S1.LoadData("Test1.txt");
    //S1.Dispaly_New_Process_List();
    //S1.Display_input_file_Data();
    //UI u();
    //delete[] processes;
    return 0;

}