#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
#include"..\Data Structures\QUEUE.h"
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
    struct io_request {
        int io_duration;
        int io_request_time;
    };
    Queue<io_request> io_requests;
    Queue<string> pairs_io_request;

    
    enum State { NEW, READY, RUNNING, BLOCKED, TERMINATED, ORPHAN };
    State state;
public:
    io_request req;
    


    Process(int arrival_time, int pid, int cpu_time, io_request req);
    Process(int arrival_time, int pid, int cpu_time, int io_request_number);
    Process(int arrival_time, int pid, int cpu_time);
    Process();


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
    bool check_io_request(int current_time);
    
    
    

   
};


