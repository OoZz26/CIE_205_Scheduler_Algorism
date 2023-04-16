#include"Process.h"
Process::Process(int arrival_time, int pid, int cpu_time, const vector<pair<int, int>>& io_requests)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
    this->io_requests = io_requests;
    this->state = NEW;
}
Process::Process()
{   
    //this->pid = 0;
    //this->arrival_time = 0;
    //this->cpu_time = 0;
    this->state = NEW;
}
// Getters
int Process::get_pid()
{
    return pid;
}

int Process::get_arrival_time() {
    return arrival_time;
}

int Process::get_response_time()
{
    return response_time;
}

int Process::get_cpu_time()
{
    return cpu_time;
}

int Process::get_termination_time()
{
    return termination_time;
}

int Process::get_turnaround_duration()
{
    return turnaround_duration;
}

int Process::get_waiting_time()
{
    return waiting_time;
}

int Process::get_io_request_time()
{
    return io_request_time;
}

int Process::get_io_duration()
{
    return io_duration;
}

Process::State Process::get_state()
{
    return State();
}

//State Process::get_state()  
//{
//    return state;
//}



bool Process::is_ready(Process* p)
{
    if (p->get_state() == State::READY) {
        return true;
    }
    else
    {
        return false;
    }

}

int Process::get_io_request_number()
{
    return io_request_number;
}

//const vector<pair<int, int>>& Process::get_io_requests()
//{
//   
//    // TODO: insert return statement here
//}

void Process::set_io(vector<pair<int, int>> io)
{
    io_requests = io;
}

void Process::set_id(int id)
{
    pid = id;
}

void Process::set_arrival_time(int arrivalrime)
{
    arrival_time = arrivalrime;
}


void Process::set_cpu_time(int ct)
{
    cpu_time = ct;
}

//const Process:: vector<pair<int, int>>& get_io_requests() 
//{
//    return io_requests;
//}
 //Setters
void Process::set_response_time(int response_time)
{
    this->response_time = response_time;
}

void Process::set_termination_time(int termination_time)
{
    this->termination_time = termination_time;
}

void Process::set_turnaround_duration(int turnaround_duration)
{
    this->turnaround_duration = turnaround_duration;
}

void Process::set_waiting_time(int waiting_time)
{
    this->waiting_time = waiting_time;
}

void Process::set_state(State state)
{
    this->state = state;
}
// Create a new Process (edit to read from file later)
//Process Process::Create_New_Process(int num_Processes)
//{
//    int arrival_time, pid, cpu_time, io_request_number;
//    vector<pair<int, int>> io_requests;
//
//    Process* Processes = new Process[num_Processes];
//
//    // Create objects of type Process using the argument constructor
//    for (int i = 0; i < num_Processes; i++) {
//
//        // Create pairs of I/O requests <request_time, request_duration>
//        for (int j = 0; j < io_request_number; j++) {
//            int io_request_time, io_duration;
//            io_requests.push_back(make_pair(io_request_time, io_duration));
//        }
//        //return Process(arrival_time, pid, cpu_time, io_request_number, io_requests);
//        return Process(arrival_time, pid, cpu_time, io_requests);
//    }
//}


// Termination of a Process happens when:
// 1- CPU time ends
// 2- Reccieve a sigkill (only for FCFS and when in ready_q and run_q ) 
void Process::Terminate_Process()
{
    // 1- IF CPU TIME ENDS
    // if CPU == 0
        // move from where it is (ready list or run list) to terminate list
        // 
     // 2- IF WE RECIEVE A SIGKILL 
    // if not applicable 
        // ignore signal
    // else
        // move from where it is (ready list or run list) to terminate list
}