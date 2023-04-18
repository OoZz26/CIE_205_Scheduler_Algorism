#pragma once
#include<iostream>
using namespace std;
//First let's declare a single node in the list
template<typename T>
class Node
{
private:
	T item;	// A data item (can be any complex sturcture)
	Node<T>* next;	// Pointer to next node
public:

	Node() //default constructor
	{
		next = nullptr;
	}

	Node(T newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;

	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	T getItem() const
	{
		return item;
	} // end getItem

	Node<T>* getNext() const
	{
		 return next; 
	}
}; // end Node

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	Node<T>* Tail;
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
		Tail = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}

	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	bool ISEMPTY() {
		if (Head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	T Front() {
		return Head->getItem();
	}
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}

	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}

	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(T newitem)
	{
		Node<T>* newNode = new Node<T>(newitem);
		newNode->setItem(newitem);
		if (ISEMPTY()) {
			Head = newNode;
		}
		else
		{
			Node<T>* P = Head;
			while (P->getNext() != NULL)
			{
				P = P->getNext();
			}

			P->setNext(newNode);


			newNode->setNext(NULL);
			delete P;
		}
		
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.

	bool Find(T item)
	{
		bool found = false;
		Node<T>* P = Head;
		while (P != NULL)
		{
			if (P->getItem() == item)
				found = true;
			P = P->getNext();

		}
		return found;
	}


	//[3]CountOccurance
	//returns how many times a certain value appeared in the list

	int CountOccurance(T item)
	{
		int Counter = 0;
		bool found = false;
		Node<T>* P = Head;
		while (P != NULL)
		{
			if (P->getItem() == item)
			{
				Counter += 1;
			}

			P = P->getNext();

		}
		return Counter;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list

	void DeleteFirst()
	{
		if(Head->getNext()){ 
			Node<T>* delptr;
			delptr = Head;
			Head = Head->getNext(); 
			delete delptr;
		}
		else {
			return;
		}
	}

	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* delptr = Head;
		Node<T>* prev = NULL;
		while (delptr->getNext() != NULL)
		{
			prev = delptr;
			delptr = delptr->getNext();
		}
		prev->setNext(NULL);

		delete delptr;
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(T item)
	{


		int found = 0;
		bool F = false;
		Node<T>* Temp = Head;
		while (Temp != NULL)
		{
			if (Temp->getItem() == item)
			{
				found += 1;

			}

			Temp = Temp->getNext();

		}
		if (found != 0)
		{
			Node<T>* delptr;
			if (Head->getItem() == item)
			{
				delptr = Head;
				Head = Head->getNext();
				delete delptr;
			}
			else
			{
				delptr = Head;
				Node<T>* prev = NULL;
				while (delptr->getItem() != item)
				{
					prev = delptr;
					delptr = delptr->getNext();
				}
				prev->setNext(delptr->getNext());
				delete delptr;
			}
			F = true;
		}

		return F;

	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted

	void DeleteNodes(T item)
	{

		Node<T>* delptr = Head->getNext();
		Node<T>* prev = Head;
		while (delptr->getNext() != NULL)
		{

			if (delptr->getItem() == item)
			{

				prev->setNext(delptr->getNext());
				delete delptr;

			}
			else
				prev = delptr;
			delptr = prev->getNext();
		}


	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(LinkedList <T>  lst)
	{
		Node<T>* P = Head;
		while (P->getNext() != NULL)
		{
			P = P->getNext();
		}
		P->setNext(lst.Head);

	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)

	void Rverse()
	{
		Node<T>* current = Head;
		Node<T>* prev = NULL;
		Node<T>* Next = NULL;
		while (current != NULL)
		{
			Next = current->getNext();
			current->setNext(prev);
			prev = current;
			current = Next;
		}
		Head = prev;

	}

};





//
////example
//template<typename T>
//class Node
//{
//private:
//	T item;	// A data item (can be any complex sturcture)
//	Node<T>* next;	// Pointer to next node
//public:
//
//	Node() //default constructor
//	{
//		next = nullptr;
//	}
//
//	Node(T newItem) //non-default constructor
//	{
//		item = newItem;
//		next = nullptr;
//
//	}
//
//	void setItem(T newItem)
//	{
//		item = newItem;
//	} // end setItem
//
//	void setNext(Node<T>* nextNodePtr)
//	{
//		next = nextNodePtr;
//	} // end setNext
//
//	T getItem() const
//	{
//		return item;
//	} // end getItem
//
//	Node<T>* getNext() const
//	{
//		if (next) { return next; }
//		else
//		{
//			return NULL;
//		}
//
//	}
//}; // end Node
//
//
//template <typename T>
//class LinkedList
//{
//private:
//	Node<T>* Head;	//Pointer to the head of the list
//	Node<T>* Tail;
//	int Count;  //Counter to keep track of the number of elements in the list
//
//public:
//
//
//	LinkedList()
//	{
//		Head = nullptr;
//		Tail = nullptr;
//		Count = 0;
//	}
//
//	//List is being desturcted ==> delete all items in the list
//	~LinkedList()
//	{
//		DeleteAll();
//	}
//	bool ISEMPTY() {
//		if (Head == nullptr) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	T Front() {
//		return Head->getItem();
//	}
//	void PrintList()	const
//	{
//		cout << "\nprinting list contents:\n\n";
//		Node<T>* p = Head;
//
//		while (p)
//		{
//			cout << "[ " << p->getItem() << " ]";
//			cout << "--->";
//			p = p->getNext();
//		}
//		cout << "*\n";
//	}
//
//
//	void InsertBeg(const T& data)
//	{
//		Node<T>* R = new Node<T>(data);
//		R->setNext(Head);
//		Head = R;
//		Count++;
//	}
//
//
//	void DeleteAll()
//	{
//		Node<T>* P = Head;
//		while (Head)
//		{
//			P = Head->getNext();
//			delete Head;
//			Head = P;
//			Count--;
//		}
//		Tail = nullptr;
//	}
//
//
//	void InsertEnd(T newitem)
//	{
//		Node<T>* newNode = new Node<T>(newitem);
//		newNode->setItem(newitem);
//		if (ISEMPTY()) {
//			Head = newNode;
//			Tail = newNode;
//		}
//		else
//		{
//			Tail->setNext(newNode);
//			Tail = newNode;
//		}
//		Count++;
//	}
//
//
//	bool Find(T item)
//	{
//		bool found = false;
//		Node<T>* P = Head;
//		while (P != NULL)
//		{
//			if (P->getItem() == item)
//				found = true;
//			P = P->getNext();
//
//		}
//		return found;
//	}
//
//
//
//
//	//[4] DeleteFirst
//	//Deletes the first node in the list
//
//	void DeleteFirst()
//	{
//		if (Head->getNext()) {
//			Node<T>* delptr;
//			delptr = Head;
//			Head = Head->getNext();
//			delete delptr;
//			Count--;
//		}
//		else {
//			return;
//		}
//	}
//
//	//[5] DeleteLast
//	//Deletes the last node in the list
//	void DeleteLast()
//	{
//		Node<T>* delptr = Head;
//		Node<T>* prev = NULL;
//		while (delptr->getNext() != NULL)
//		{
//			prev = delptr;
//			delptr = delptr->getNext();
//		}
//		prev->setNext(NULL);
//		Tail = prev;
//
//		delete delptr;
//		Count--;
//	}
//
//	int GetCount()
//	{
//		return Count;
//	}
//
//};
