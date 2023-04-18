#pragma once
#include"Process/Process.h"

class Node2
{
private:
    Process* item;	// A data item (can be any complex sturcture)
    Node2* next;	// Pointer to next Node2
public:

    Node2() //default constructor
    {
        next = nullptr;
    }

    Node2(Process* newItem) //non-default constructor
    {
        item = newItem;
        next = nullptr;

    }

    void setItem(Process* newItem)
    {
        item = newItem;
    } // end setItem

    void setNext(Node2* nextNode2Ptr)
    {
        next = nextNode2Ptr;
    } // end setNext

    Process* getItem() const
    {
        return item;
    } // end getItem

    Node2* getNext() const
    {
        return next;
    }
}; 

// end Node2
//template <typename T>
//struct Task {
//    int id;
//    T duration_time;
//    Task* next;
//    // Constructor
//    Task(int id, T duration_time) : id(id), duration_time(duration_time), next(nullptr) {}
//};

//template <typename T>
class PriorityQueue {
    private:
    Node2* head;
public:
    PriorityQueue() : head(nullptr) {}

    void enqueue(Process* task) {
        Node2* new_task = new Node2(task);
        if (!head || task->get_cpu_time() < head->getItem()->get_cpu_time()) {
            new_task->setNext(head) ;
            head = new_task;
            cout << "lol vv" << endl;
        }
        else {
            Node2* current = head;
            while (current->getNext() && current->getNext()->getItem()->get_cpu_time() <= task->get_cpu_time()) {
                current = current->getNext();
            }
            new_task->setNext(current->getNext()) ;
            current->setNext( new_task);
            cout << "lol" << endl;
            
        }
    }

    Process* dequeue() {
        if (!head) {
            // Handle empty queue
            throw "Queue is empty"; 
        }
        Node2* removed_task = head;
        head = head->getNext();
        Process* task = removed_task->getItem();
        delete removed_task;
        return task;
    }
    bool IsEmpty()
    {
        if (head == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    void Display() {
        if (!head) {
            throw ("empty queue");
        }
        else {
            Node2* temp = head;
            while (temp != NULL)
            {
                cout << temp->getItem()->get_cpu_time() << " ";
                temp = temp->getNext();
            }
            cout << endl;

        }
    }


};
