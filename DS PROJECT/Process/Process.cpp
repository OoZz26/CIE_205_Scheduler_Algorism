#include"Process.h"
Process::Process(int arrival_time, int pid, int cpu_time, io_request req)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
    this->io_requests = io_requests;
    this->state = NEW;
    this->req.io_duration = req.io_duration;
    this->req.io_request_time = req.io_duration;
}

Process::Process(int arrival_time, int pid, int cpu_time, int io_request_number)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
    this->io_request_number = io_request_number;
}

Process::Process(int arrival_time, int pid, int cpu_time)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
}


Process::Process()
{
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

Process::State Process::get_state()
{
    return State();
}


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

void Process::set_io_request_number(int io_request_numbers)
{
    io_request_number = io_request_numbers;
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


void Process::set_response_time(int response_time)
{
    this->response_time = response_time;
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
