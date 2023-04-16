#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<vector>
#include <queue> 
using namespace std;
class Process
{
private:
    int pid;
    int arrival_time;
    int response_time;
    int cpu_time;
    int termination_time;
    int turnaround_duration; // Turnaround Duration = Termination time - Arrival time
    int waiting_time;        // Waiting time = Turnaround duration - CPU time
    int io_request_number;
    int io_request_time;
    int io_duration;
    vector<pair<int, int>> io_requests;
    enum State { NEW, READY, RUNNING, BLOCKED, TERMINATED, ORPHAN };
    State state;
public:
    Process(int arrival_time, int pid, int cpu_time, const vector<pair<int, int>>& io_requests);
    Process();
    // Getters
    int get_pid();
    int get_arrival_time();
    int get_response_time();
    int get_cpu_time();
    int get_termination_time();
    int get_turnaround_duration();
    int get_waiting_time();
    int get_io_request_time();
    int get_io_duration();
    State get_state();
    bool is_ready(Process* p);
    int get_io_request_number();
    //const vector<pair<int, int>>& get_io_requests();
    // Setters
    void set_io(vector<pair<int, int>> io);
    void set_id(int id);
    void set_arrival_time(int arrivalrime);
    void set_cpu_time(int ct);
    void set_response_time(int response_time);
    void set_termination_time(int termination_time);
    void set_turnaround_duration(int turnaround_duration);
    void set_waiting_time(int waiting_time);
    void set_state(State state);
    // Create a new Process (edit to read from file later)
    /*Process Create_New_Process(int num_Processes);*/
    // Termination of a Process happens when:
    // 1- CPU time ends
    // 2- Reccieve a sigkill (only for FCFS and when in ready_q and run_q ) 
    void Terminate_Process();

};
