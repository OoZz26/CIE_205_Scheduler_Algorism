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
    this->T_cpu_time = cpu_time;
}

Process::Process(int arrival_time, int pid, int cpu_time, int io_request_number)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
    this->io_request_number = io_request_number;
    this->T_cpu_time = cpu_time;

}

Process::Process(int arrival_time, int pid, int cpu_time)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
    this->T_cpu_time = cpu_time;

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

void Process::set_state(int states)
{

    //enum { NEW, READY, RUNNING, BLOCKED, TERMINATED, ORPHAN }
    switch (states) {
    case 0:
        this->state = State::NEW;
        break;
    case 1:
        this->state = State::READY;
        break;
    case 2:
        this->state = State::RUNNING;
        break;
    case 3:
        this->state = State::BLOCKED;
        break;
    case 4:
        this->state = State::TERMINATED;
        break;
    case 5:
        this->state = State::ORPHAN;
        break;
    default:
        break;
    }

   
}

void Process::set_iorequest()
{
}

bool Process::check_io_request(int current_time)
{
    Node1<io_request>* rq= io_requests.GetFront();
    if (io_requests.IsEmpty()) {
        return false;
    }
    else{
        while (rq != nullptr)
        {
            int t = T_cpu_time - rq->GetItem().io_request_time;

            if (t == current_time)
            {
                return true;

            }
            rq = rq->getNext();
        }
    }

    return false;
    
   
}
