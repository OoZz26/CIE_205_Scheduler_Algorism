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
    int count;
public:
    PriorityQueue() : head(nullptr) { count = 0; }

    void enqueue(Process* task) {
        Node2* new_task = new Node2(task);
        if (!head || task->get_cpu_time() < head->getItem()->get_cpu_time()) {
            new_task->setNext(head) ;
            head = new_task;

        }
        else {
            Node2* current = head;
            while (current->getNext() && current->getNext()->getItem()->get_cpu_time() <= task->get_cpu_time()) {
                current = current->getNext();
            }
            new_task->setNext(current->getNext()) ;
            current->setNext( new_task);
            
        }
        count++;
    }


    Node2* GetHead() { return head; }



    int GetCount() { return count; }

    bool dequeue(Process* &frntEntry) {
        if (IsEmpty())
            return false;

        Node2* nodeToDeletePtr = head;
        frntEntry = head->getItem();
        head = head->getNext();
        // Queue is not empty; remove front
        //if (nodeToDeletePtr == backPtr)  // Special case: last node in the queue
        //    backPtr = nullptr;

        // Free memory reserved for the dequeued node
        delete nodeToDeletePtr;
        return true;
        count--;
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
