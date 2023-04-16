#pragma once
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

	T getItem() const
	{
		return item;
	} // end getItem

	Node1<T>* getNext() const
	{
		return next;
	}
}; // end Node1
template <typename T>
class Queue
{
private:
	Node1<T>* Front;
	Node1<T>* Rear;
public:


	Queue()
	{
		Front = nullptr;
		Rear = nullptr;
	}


	bool IsEmpty()
	{
		if (Front == NULL && Rear == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	void EnQueue(T item)
	{
		Node1<T>* newNode1 = new Node1<T>(item);
		newNode1->setItem(item);
		if (IsEmpty())
		{
			Front = newNode1;
			Rear = newNode1;

		}
		else
		{
			Rear->setNext(newNode1);
			Rear = newNode1;
		}

	}

	void DeQueue()
	{
		if (IsEmpty())
		{
			cout << "The Queue is Empty";
		}
		else if (Front == Rear)
		{
			delete Front;
			Front = Rear = NULL;
		}
		else
		{
			Node1<T>* delptr = Front;
			Front = Front->getNext();
			delete delptr;
		}
	}
	void Display()
	{
		Node1<T>* temp = Front;
		while (temp != NULL)
		{
			cout << temp->getItem() << " ";
			temp = temp->getNext();
		}
		cout << endl;
	}
	T FRONT() {
		if (IsEmpty())
		{
			return 0;
		}
		else {
			return Front->getItem();
		}
	}
};