#pragma once
#include "Pair.h"

#ifndef MAX_HEAP_
#define MAX_HEAP_


template <typename T>
class maxHeap
{
private:
    Pair<T, int>* heap;
    int leaf;
    int capacity;

    void expand();

public:
    maxHeap();

    bool isEmpty() const;

    void getRoot(T& frntEntry) const;

    int parent(int);

    int lchild(int);

    int rchild(int);

    void insert(const Pair<T, int>&);

    void remove(T &);

    void print() const;

    template<class U>
    friend ostream& operator<<(ostream& os, const maxHeap<U>& L);

    ~maxHeap();
};

// Utility Functions //
template <typename T>
void maxHeap<T>::expand()
{
    Pair<T, int>* resized = new Pair<T, int>[capacity * 2];

    for (int i = 0; i < capacity; i++)
    {
        resized[i] = heap[i];
    }
    delete[] heap;
    heap = resized;


    capacity = capacity * 2;
}

//      //

template <typename T>
maxHeap<T>::maxHeap()
{
    leaf = -1;
    capacity = 1;
    heap = new Pair<T, int>[capacity];
}

template <typename T>
bool maxHeap<T>::isEmpty() const
{
    if (leaf == -1) return true;
    return false;
}

template <typename T>
int maxHeap<T>::parent(int i)
{
    return (int)i / 2;
}

template <typename T>
int maxHeap<T>::rchild(int i)
{
    return (2 * i + 1);
}

template <typename T>
int maxHeap<T>::lchild(int i)
{
    return (2 * i);
}

template <typename T>
void maxHeap<T>::insert(const Pair<T, int>& item)
{
    if (leaf == capacity - 1)expand();
    leaf += 1;
    heap[leaf] = item;

    int index = leaf;

    while (index != 0 && item.right > heap[parent(index)].right)
    {
        Pair<T, int> temp = heap[parent(index)];

        heap[parent(index)] = item;

        heap[index] = temp;

        index = parent(index);
    }
}

template <typename T>
void maxHeap<T>::remove(T & item)
{

    if (leaf > -1)
    {
        item = heap[0].left;

        heap[0] = heap[leaf];

        int index = 0;

        while (heap[index].right < heap[lchild(index)].right || heap[index].right < heap[rchild(index)].right)
        {
            if (heap[index].right < heap[lchild(index)].right)
            {
                Pair<T, int> temp = heap[lchild(index)];

                heap[lchild(index)] = heap[index];

                heap[index] = temp;

                index = lchild(index);
            }
            else
            {
                Pair<T, int> temp = heap[rchild(index)];

                heap[rchild(index)] = heap[index];

                heap[index] = temp;

                index = rchild(index);
            }
        }
    }
    else if (leaf == 0)
    {
        item = heap[0].left;
    }
    leaf--;
}

template <typename T>
void maxHeap<T>::print() const
{
    for (int i = 0; i <= leaf; i++)
    {
        std::cout << heap[i].left << " : " << heap[i].right << endl;
    }
}


template <typename T>
maxHeap<T>::~maxHeap() {
    delete[] heap;
}

template <typename T>
void maxHeap<T>::getRoot(T& frntEntry) const {
    frntEntry =  heap[0].left;
}



template<class T>
ostream& operator<<(ostream& os, const maxHeap<T>& L) {

    if(L.isEmpty())
    { 
        os << "List is Empty";
        return os;
    }
    else
    {
        for (int i = 0; i <= L.leaf; i++)
        {
            os << L.heap[i].left << ", ";
        }
        return os;
    }
}

#endif