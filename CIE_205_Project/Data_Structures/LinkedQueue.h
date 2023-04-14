#pragma once


#include "SharedClasses/Node.h"
#include "SharedClasses/QueueADT.h"

template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:

	LinkedQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}

	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ)
	{
		frontPtr = backPtr = nullptr;
		Node<T>* NodePtr = LQ.frontPtr;	//start at the front node in LQ
		while (NodePtr)
		{
			enqueue(NodePtr->getItem());	//get data of each node and enqueue it in this queue 
			NodePtr = NodePtr->getNext();
		}
	}

	~LinkedQueue()
	{
		//Note that the cout statements here is just for learning purpose
		//They should be normally removed from the destructor
		cout << "\nStarting LinkedQueue destructor...";
		cout << "\nFreeing all nodes in the queue...";

		//Free all nodes in the queue
		T temp;
		while (dequeue(temp));

		cout << "\n Is LinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
		cout << "\nEnding LinkedQueue destructor..." << endl;
	}




	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}


	void PrintList() const
	{
		if (Last_Index == -1)
		{
			cout << "there is no elements in the list";
			return;
		}
		cout << "\nprinting queue contents:\n\n";
		Node<T>* p = backPtr;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}


	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);

		if (isEmpty())
			frontPtr = newNodePtr;
		else
			backPtr->setNext(newNodePtr);

		backPtr = newNodePtr;
		return true;
	}


	bool dequeue(T& frntEntry)
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

		return true;
	}


	bool peek(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}



};