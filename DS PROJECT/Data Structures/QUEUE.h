#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Node1
{
private:
	T item;	// A data item (can be any complex sturcture)
	Node1<T>* next;	// Pointer to next Node1
public:

	Node1() //default constructor
	{
		next = nullptr;
	}

	Node1(T newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;

	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node1<T>* nextNode1Ptr)
	{
		next = nextNode1Ptr;
	} // end setNext

	T GetItem() const
	{
		return item;
	} // end getItem

	Node1<T>* getNext() const
	{
		return next;
	}
};// end Node1

template <typename T>
class Queue
{
private:
    Node1<T>* backPtr;
    Node1<T>* frontPtr;
    int count;

public:
    Queue();
    bool IsEmpty() const;
    bool Enqueue(const T& newEntry);
    bool Dequeue(T& frntEntry);
    bool Peek(T& frntEntry) const;
    void PrintQueue() const;
    int Count() const;
    Node1<T>* GetFront() { return frontPtr; }
    ~Queue();

};

template <typename T>
Queue<T>::Queue()
{
    backPtr = nullptr;
    frontPtr = nullptr;
    count = 0;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
    return (frontPtr == nullptr);
}

template <typename T>
bool Queue<T>::Enqueue(const T& newEntry)
{
    Node1<T>* newNodePtr = new Node1<T>(newEntry);
    // Insert the new node
    if (IsEmpty())  //special case if this is the first node to insert
        frontPtr = newNodePtr; // The queue is empty
    else
        backPtr->setNext(newNodePtr); // The queue was not empty

    backPtr = newNodePtr; // New node is the last node now
    count++;
    return true;
} // end Enqueue

template <typename T>
bool Queue<T>::Dequeue(T& frntEntry)
{
    if (IsEmpty())
        return false;

    Node1<T>* nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    // Queue is not empty; remove front
    if (nodeToDeletePtr == backPtr)  // Special case: last node in the queue
        backPtr = nullptr;

    // Free memory reserved for the dequeued node
    delete nodeToDeletePtr;

    count--;
    return true;
}

template <typename T>
bool Queue<T>::Peek(T& frntEntry) const
{
    if (IsEmpty())
        return false;

    frntEntry = frontPtr->getItem();
    return true;
}

template <typename T>
void Queue<T>::PrintQueue() const
{
    Node1<T>* temp = frontPtr;
    while (temp != nullptr)
    {
        cout << temp->GetItem() << " ";
        temp = temp->getNext();
    }
    cout << endl;
}

template <typename T>
int Queue<T>::Count() const
{
    return count;
}

template <typename T>
Queue<T>::~Queue()
{
    cout << "\nStarting LinkedQueue destructor...";
    cout << "\nFreeing all nodes in the queue...";

    //Free all nodes in the queue
    T temp;
    while (Dequeue(temp));

    cout << "\nIs LinkedQueue Empty now?? ==> " << boolalpha << IsEmpty();
    cout << "\nEnding LinkedQueue destructor..." << endl;
}





//
//template <typename T>
//class Queue
//{
//private:
//	Node1<T>* Front;
//	Node1<T>* Rear;
//	int count;
//public:
//
//
//	Queue()
//	{
//		Front = nullptr;
//		Rear = nullptr;
//	}
//
//
//	bool IsEmpty()
//	{
//		if (Front == NULL && Rear == NULL)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//
//	}
//	void EnQueue(T item)
//	{
//		Node1<T>* newNode1 = new Node1<T>(item);
//		newNode1->setItem(item);
//		if (IsEmpty())
//		{
//			Front = newNode1;
//			Rear = newNode1;
//			count++;
//
//		}
//		else
//		{
//			Rear->setNext(newNode1);
//			Rear = newNode1;
//			count++;
//		}
//
//	}
//
//	void DeQueue()
//	{
//		if (IsEmpty())
//		{
//			cout << "The Queue is Empty";
//		}
//		else if (Front == Rear)
//		{
//			delete Front;
//			Front = Rear = NULL;
//			count--;
//
//		}
//		else
//		{
//			Node1<T>* delptr = Front;
//			Front = Front->getNext();
//			delete delptr;
//			count--;
//		}
//	}
//	int GetCount()const { return count; }
//	void Display()
//	{
//		Node1<T>* temp = Front;
//		while (temp != NULL)
//		{
//			cout << temp->getItem() << " ";
//			temp = temp->getNext();
//		}
//		cout << endl;
//	}
//	T FRONT() {
//		if (IsEmpty())
//		{
//			return 0;
//		}
//		else {
//			return Front->getItem();
//		}
//	}
