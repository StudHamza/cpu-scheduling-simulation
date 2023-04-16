#pragma once

#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_


#include "SharedClasses/Node.h"
#include "SharedClasses/QueueADT.h"
#include "SharedClasses/MaxHeap.h"


template <typename T>
class Priority_Queue : public QueueADT<T>
{
private:
	maxHeap<T> heap;
	
public:
	Priority_Queue();
	bool isEmpty() const override;
	bool enqueue(const Pair<T,int> & newEntry);
	bool dequeue(T & frntEntry) override;
	bool peek(T & frntEntry)  const override;

	void print() const;

	~Priority_Queue();
};

template <typename T>
Priority_Queue<T>::Priority_Queue()
{

}


template <typename T>
bool Priority_Queue<T>::isEmpty() const
{
	return heap.isEmpty();
}

template <typename T>
bool Priority_Queue<T>::enqueue(const Pair<T, int>& newEntry)
{
	heap.insert(newEntry);
	return true;
}

template <typename T>
bool Priority_Queue<T>::dequeue(T & frntEntry)
{
	heap.remove(frntEntry);
	return true;
}

template <typename T>
bool Priority_Queue<T>::peek(T& frntEntry) const
{
	heap.getRoot(frntEntry);
	return true;
}

template <typename T>
void Priority_Queue<T>::print() const
{
	heap.print();
}

template <typename T>
Priority_Queue<T>::~Priority_Queue()
{

	T temp;
	while (dequeue(temp));

}

#endif