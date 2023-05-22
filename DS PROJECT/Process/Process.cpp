#include"Process.h"


Process::Process(int arrival_time, int pid, int cpu_time, int io_request_number, Queue<io_request> io_requests){
    this->arrival_time = arrival_time;
    this->pid = pid;
    this->cpu_time = cpu_time;
    this->T_cpu_time = cpu_time;
    this->io_request_number = io_request_number;
    this->io_requests = io_requests;
    this->Remaning_time = cpu_time;
    this->state = State::NEW;
    this->turnaround_duration = termination_time - arrival_time;
    this->waiting_time = turnaround_duration - cpu_time;

    // Fill in the io_requests queue using the provided io_durations and io_request_times arrays
   /* this->io_requests = fill_IO_Requests(io_request_number, io_durations, io_request_times);*/
}

Process::Process(int arrival_time, int pid, int cpu_time, int io_request_number)
{
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->cpu_time = cpu_time;
    this->io_request_number = io_request_number;
    this->T_cpu_time = cpu_time;

}

//Process::Process(int arrival_time, int pid, int cpu_time, io_request req)
//{
//    this->pid = pid;
//    this->arrival_time = arrival_time;
//    this->cpu_time = cpu_time;
//    this->io_requests = io_requests;
//    this->state = NEW;
//    this->req.io_duration = req.io_duration;
//    this->req.io_request_time = req.io_duration;
//    this->T_cpu_time = cpu_time;
//}
//

//Process::Process(int arrival_time, int pid, int cpu_time)
//{
//    this->pid = pid;
//    this->arrival_time = arrival_time;
//    this->cpu_time = cpu_time;
//    this->T_cpu_time = cpu_time;
//
//}
//
//
Process::Process()
{
    this->state = NEW;
}


Queue<Process::io_request> Process::fill_IO_Requests(int io_request_number, int* io_durations, int* io_request_times) {
    Queue<Process::io_request> io_requests;
    for (int i = 0; i < io_request_number; i++) {
        Process::io_request req = { io_durations[i], io_request_times[i] };
        io_requests.Enqueue(req);
    }
    return io_requests;
}

bool Process::isOrphan() const {
    // If the parent process is terminated and its childern are still running return true
    return (parent == nullptr && !children.IsEmpty());
}

void Process::addChild(Process* child) {
    children.Enqueue(child);
}

void Process::removeChild(Process* child) {
    children.Dequeue(child);
}


// Getters

Queue<Process*> Process::getChildren() const {
    return children;
}

Process* Process::get_parent() const {
    return parent;
}

int Process::get_wait_time() {
    return waiting_time = turnaround_duration - arrival_time;
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

int Process::get_termination_time()
{
    return termination_time;
}

int Process::get_turnaround_duration()
{
    return  turnaround_duration;
}

int Process::get_cpu_time()
{
    return cpu_time;
}

int Process::get_Waiting_t()
{
    return waiting_time;
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

void Process::incrementIO_D()
{
    io_totalduration++;
}

int Process::get_totalIOD()
{
    return io_totalduration;
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

void Process::set_TT(int t)
{
    termination_time = t;
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


bool Process::check_io_request(int current_time)
{
    Node1<io_request>* rq = nullptr;
        io_requests.GetFront(rq);
        

    if (io_requests.IsEmpty()) {
        return false;
    }
    else{
        while (rq != nullptr)
        {
            int p = rq->GetItem().io_request_time;
            int t = cpu_time - T_cpu_time;
                
            if (t == p)
            {

                return true;

            }
            rq = rq->getNext();
        }
    }

    return false;
    
   
}
int Process::get_remainnig_time()
{
    return T_cpu_time;
}
void Process::set_remainnig_time(int remaing)
{
    T_cpu_time = remaing;
}
bool Process::get_has_forked()
{
    return has_Forked_before;;
}
void Process::set_has_forked(bool state)
{
    has_Forked_before = state;
}
void Process::set_child_pointer(Process* p)
{
	child_pointr = p;

}
Process* Process::get_child_pointer()
{
    return child_pointr;
}
int Process::get_N_ofIoR()
{
    return io_request_number;
}
int Process::get_BLK_counter()
{
    return BLK_counter;
}
void Process::increament_BLK_counter()
{
    BLK_counter;
}
void Process::reset_BLK_counter()
{
    BLK_counter = 0;
}
void Process::decrement_N_ofIoR()
{
    io_request_number--;
}
//Queue<Process::io_request> Process::fill_IO_Requests(int io_request_number, int* io_durations, int* io_request_times) {
//    Queue<Process::io_request> io_requests;
//    for (int i = 0; i < io_request_number; i++) {
//        Process::io_request req = { io_durations[i], io_request_times[i] };
//        io_requests.Enqueue(req);
//    }
//    return io_requests;
//}
