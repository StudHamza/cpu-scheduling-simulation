/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General Queue case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single Node Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					-----------
					|item| next| -->NULL
					-----------

*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_
#include <iostream>
using namespace std;
#include "SharedClasses/Node.h"
#include "SharedClasses/QueueADT.h"

template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int Counter;
public:
	LinkedQueue();

	friend ostream& operator<< <T>(ostream& out, const LinkedQueue<T>& queue);
	T operator[](int index);

	bool isEmpty() const;
	int GetSize() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool DeleteNode(const T& data);
	Node<T>* GetNodeAt(int index);
	T DeleteAt(int index);
	bool peek(T& frntEntry)  const;
	~LinkedQueue();
};

template <typename T>
T LinkedQueue<T>::operator[](int index)
{
	if (index < 0 || index >(Counter - 1)) {
		throw out_of_range("Index out of range");
	}
	return GetNodeAt(index)->getItem();
}

template <typename T>
int LinkedQueue<T>::GetSize() const
{
	return Counter;
}

template <typename T>
ostream& operator << (ostream& out, const LinkedQueue<T>& queue)
{
	if (queue.isEmpty())
	{
		out << "0";
		return out;
	}
	Node<T>* p = queue.frontPtr;
	while (p)
	{
		out << *(p->getItem());
		p = p->getNext();
		if (p)
		{
			out << ", ";
		}
	}
	return out;
}

template <typename T>
Node<T>* LinkedQueue<T>::GetNodeAt(int index)
{
	if (Counter == 0)
	{
		cout << "there is no items in the list\n";
		return nullptr;
	}
	if ((index < 0) || (index >= Counter))
	{
		cout << "index bigger than list\n";
		return nullptr;
	}

	Node<T>* curPtr = frontPtr;
	for (int i = 0; i < index; i++)
	{
		curPtr = curPtr->getNext();
	}
	return curPtr;
}

template <typename T>
bool LinkedQueue<T>::DeleteNode(const T& data)
{
	for (int i = 0; i <= Counter; i++)
	{
		if (GetNodeAt(i)->getItem() == data)
		{
			DeleteAt(i);
			return true;
		}
	}
	return false;
}

template <typename T>
T LinkedQueue<T>::DeleteAt(int index)
{
	if (index == 0)
	{
		if (Counter == 0)
		{
			cout << "there is no element to delete\n";
			return NULL;
		}
		Node<T>* curPtr = frontPtr;
		frontPtr = frontPtr->getNext();
		T temp = curPtr->getItem();
		delete curPtr;
		Counter--;
		return temp;
	}
	else if (index == Counter - 1)
	{
		if (Counter == 0)
		{
			cout << "there is no element to delete\n";
			return NULL;
		}
		if (Counter == 1)
		{
			T temp = frontPtr->getItem();
			delete frontPtr;
			frontPtr = nullptr;
			backPtr = nullptr;
			Counter--;
			return temp;
		}

		Node<T>* prevPtr = GetNodeAt(Counter - 2);
		Node<T>* curPtr = prevPtr->getNext();
		T temp = curPtr->getItem();
		delete curPtr;
		prevPtr->setNext(nullptr);
		backPtr = prevPtr;
		Counter--;
		return temp;
	}
	else if (index > (Counter - 1) || (index < 0))
	{
		cout << "index out of range\n";
		return NULL;
	}
	else
	{
		Node<T>* prevPtr = GetNodeAt(index - 1);
		Node<T>* curPtr = prevPtr->getNext();
		prevPtr->setNext(curPtr->getNext());
		T temp = curPtr->getItem();
		delete curPtr;
		Counter--;
		return temp;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	Counter = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.
=======
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/


template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	Counter++;
	return true;
} // end enqueue

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.


Input: None.
Output: True if the operation is successful; otherwise false.
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;


	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	Counter--;
	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{

	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor


	//Free all nodes in the queue
	/*T temp;
	while (dequeue(temp));*/
}



#endif