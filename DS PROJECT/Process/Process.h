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
    int response_time = 0;
    int cpu_time;
    int T_cpu_time;
    int termination_time = 0;
    int turnaround_duration = 0; // Turnaround Duration = Termination time - Arrival time
    int waiting_time = 0;        // Waiting time = Turnaround duration - CPU time
    int io_request_number;
    int io_request_time;
    int io_totalduration=0;
    int Remaning_time;
    bool has_Forked_before = false;
    int BLK_counter = 0;
    
    Queue<io_request> io_requests;
    Queue<string> pairs_io_request;
    Process* child_pointr = nullptr;

    struct io_request {
        int io_duration;
        int io_request_time;
    };

    enum State { NEW, READY, RUNNING, BLOCKED, TERMINATED, ORPHAN };
    State state;
public:
    io_request req;

    
    Process(int arrival_time, int pid, int cpu_time, int io_request_number,Queue<io_request> io_requests);
    Process(int arrival_time, int pid, int cpu_time, int io_request_number);
    Process(); 


    Process* parent; // Pointer to the parent process
    Queue<Process*> children; // Queue of pointers to child processes

  /*  Process(int arrival_time, int pid, int cpu_time, io_request req);
   
    Process(int arrival_time, int pid, int cpu_time);
  */


    // Getters
    int get_pid();
    int get_arrival_time();
    int get_response_time();
    int get_termination_time();
    int get_turnaround_duration();
    int get_cpu_time();
    int get_Waiting_t();
    State get_state();
    bool is_ready(Process* p);
    int get_io_request_number();
    void incrementIO_D();
    int get_totalIOD();
    void set_io_request_number( int io_request_numbers);
    void set_id(int id);
    void set_arrival_time(int arrivalrime);
    void set_TT(int t);
    void set_cpu_time(int ct);
    void set_response_time(int response_time);
    void set_turnaround_duration(int turnaround_duration);
    void set_waiting_time(int waiting_time);
    void set_state(int state);
    Queue<io_request> get_iorequest();

    /*Queue<io_request> fill_IO_Requests(int io_request_number, int* io_durations, int* io_request_times);*/
    bool check_io_request(int current_time);

    int get_remainnig_time();
    void set_remainnig_time(int remaing);
    bool get_has_forked();
    void set_has_forked(bool state);
    void set_child_pointer(Process* p);
    Process* get_child_pointer();
    int get_N_ofIoR();
    int get_BLK_counter();
    void increament_BLK_counter();
    void reset_BLK_counter();
    void decrement_N_ofIoR();
    
    
    void set_parent(Process* parent);
    Queue<io_request> fill_IO_Requests(int io_request_number, int* io_durations, int* io_request_times);
    void addChild(Process* child); // Add a child process
    void removeChild(Process* child); // Remove a child process
    bool isOrphan() const;
    Process* get_parent() const;
    Queue<Process*> getChildren() const;
    int get_wait_time();
};


 