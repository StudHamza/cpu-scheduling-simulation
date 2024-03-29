#pragma once


template<class T>
class QueueADT
{
public:
    virtual bool isEmpty() const = 0;

    virtual bool enqueue(const T& newEntry) { return true; }

    virtual bool dequeue(T& FrontEntry) = 0;


    virtual bool peek(T& FrontEntry) const = 0;

    virtual ~QueueADT() { }
};
