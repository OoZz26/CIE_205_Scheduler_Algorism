#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
#include"..\Data Structures\QUEUE.h"
#include"../Struct.h"
using namespace std;
class Process
{
private:
    int pid;
    int arrival_time;
    int response_time;
    int cpu_time;
    int  T_cpu_time;
    int termination_time;
    int turnaround_duration; // Turnaround Duration = Termination time - Arrival time
    int waiting_time;        // Waiting time = Turnaround duration - CPU time
    int io_request_number;
    int io_request_time;
    int io_duration;
    bool has_Forked_before = false;
    
    Queue<io_request> io_requests;
    Queue<string> pairs_io_request;
    Process* child_pointr = nullptr;

    
    enum State { NEW, READY, RUNNING, BLOCKED, TERMINATED, ORPHAN };
    State state;
public:
    io_request req;

    
    Process(int arrival_time, int pid, int cpu_time, int io_request_number,Queue<io_request> io_requests);
    Process(int arrival_time, int pid, int cpu_time, int io_request_number);
    Process(); 

  /*  Process(int arrival_time, int pid, int cpu_time, io_request req);
   
    Process(int arrival_time, int pid, int cpu_time);
  */


    // Getters
    int get_pid();
    int get_arrival_time();
    int get_response_time();
    int get_cpu_time();
    State get_state();
    bool is_ready(Process* p);
    int get_io_request_number();
    void set_io_request_number( int io_request_numbers);
    void set_id(int id);
    void set_arrival_time(int arrivalrime);
    void set_cpu_time(int ct);
    void set_response_time(int response_time);
    void set_turnaround_duration(int turnaround_duration);
    void set_waiting_time(int waiting_time);
    void set_state(int state);
    void set_iorequest();
    /*Queue<io_request> fill_IO_Requests(int io_request_number, int* io_durations, int* io_request_times);*/
    bool check_io_request(int current_time);

    int get_remainnig_time();
    bool get_has_forked();
    void set_has_forked(bool state);
    void set_child_pointer(Process* p);
    Process* get_child_pointer();
    
    
    

   
};


 