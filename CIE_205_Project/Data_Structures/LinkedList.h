#pragma once

#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "SharedClasses/Node.h"
#include <iostream>
using namespace std;


template <typename T>
class LinkedList
{
private:
	Node<T>* Head;
	int Last_Index;
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Last_Index = -1;
		Head = nullptr;
	}

	template<class U>
	friend ostream& operator<< (ostream& out, const LinkedList<U>&);

	~LinkedList()
	{
		DeleteAll();
	}

	T operator[](int index)
	{
		if (index < 0 || index > Last_Index) {
			throw out_of_range("Index out of range");
		}
		return GetNodeAt(index)->getItem();
	}

	int GetSize()
	{
		return Last_Index + 1;
	}

	bool isEmpty() const
	{
		if (Last_Index == -1)
		{
			return true;
		}
		return false;
	}

	Node<T>* GetNodeAt(int index)
	{
		if (Last_Index == -1)
		{
			cout << "there is no items in the list\n";
			return nullptr;
		}
		if ((index < 0) || (index > Last_Index))
		{
			cout << "index bigger than list\n";
			return nullptr;
		}

		Node<T>* curPtr = Head;
		for (int i = 0; i < index; i++)
		{
			curPtr = curPtr->getNext();
		}
		return curPtr;
	}

	Node<T>* GetLastNode()
	{
		if (Last_Index == -1)
		{
			cout << "there is no items in the list\n";
			return nullptr;
		}
		Node<T>* curPtr = Head;
		while (curPtr->getNext() != nullptr)
		{
			curPtr = curPtr->getNext();
		}
		return curPtr;
	}



	void PrintList() const
	{
		if (Last_Index == -1)
		{
			cout << "there is no elements in the list";
			return;
		}
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

	bool InsertAt(const T& data, int index)
	{
		Node<T>* R = new Node<T>(data);
		if (index == 0)
		{
			R->setNext(Head);
			Head = R;
			Last_Index++;
			return true;
		}
		else if (index == Last_Index + 1)
		{
			Node<T>* last = GetLastNode();
			last->setNext(R);
			Last_Index++;
			return true;
		}
		else if ((index > Last_Index + 1) || (index < 0))
		{
			cout << "index out of range\n";
			return false;
		}
		else
		{
			Node<T>* prevPtr = GetNodeAt(index - 1);
			Node<T>* curPtr = prevPtr->getNext();
			prevPtr->setNext(R);
			R->setNext(curPtr);
			Last_Index++;
			return true;
		}
	}

	bool InsertBeg(const T& data)
	{
		bool x = InsertAt(data,0);
		return x;
	}

	bool InsertEnd(const T& data)
	{
		bool x = InsertAt(data, Last_Index + 1);
		return x;
	}



	bool Find(const T& data)
	{
		if (Last_Index == -1)
		{
			return false;
		}

		Node<T>* curPtr = Head;
		while (true)
		{
			if (curPtr->getItem() == data)
			{
				return true;
			}
			if (curPtr->getNext() == nullptr)
			{
				return false;
			}
			curPtr = curPtr->getNext();
		}
	}

	int CountOccurance(const T& data)
	{
		if (Last_Index == -1)
		{
			return 0;
		}

		int appearance_count = 0;
		Node<T>* curPtr = Head;
		while (true)
		{
			if (curPtr->getItem() == data)
			{
				appearance_count++;
			}
			if (curPtr->getNext() == nullptr)
			{
				return appearance_count;
			}
			curPtr = curPtr->getNext();
		}
	}



	T DeleteAt(int index)
	{
		if (index == 0)
		{
			if (Last_Index == -1)
			{
				cout << "there is no element to delete\n";
				return NULL;
			}
			Node<T>* curPtr = Head;
			Head = Head->getNext();
			T temp = curPtr->getItem();
			delete curPtr;
			Last_Index--;
			return temp;
		}
		else if (index == Last_Index)
		{
			if (Last_Index == -1)
			{
				cout << "there is no element to delete\n";
				return NULL;
			}
			if (Last_Index == 0)
			{
				T temp = Head->getItem();
				delete Head;
				Head = nullptr;
				Last_Index--;
				return temp;
			}

			Node<T>* prevPtr = GetNodeAt(Last_Index - 1);
			Node<T>* curPtr = prevPtr->getNext();
			T temp = curPtr->getItem();
			delete curPtr;
			prevPtr->setNext(nullptr);
			Last_Index--;
			return temp;
		}
		else if ((index > Last_Index) || (index < 0))
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
			Last_Index--;
			return temp;
		}
	}


	T DeleteFirst()
	{
		T temp = DeleteAt(0);
		return temp;
	}


	T DeleteLast()
	{
		T temp = DeleteAt(Last_Index);
		return temp;
	}

	

	bool DeleteNode(const T& data)
	{
		for (int i = 0; i <= Last_Index; i++)
		{
			if (GetNodeAt(i)->getItem() == data)
			{
				DeleteAt(i);
				return true;
			}
		}
		return false;
	}

	bool DeleteNodes(const T& data)
	{
		int deleted_count = 0;
		for (int i = 0; i <= Last_Index; i++)
		{
			if (GetNodeAt(i)->getItem() == data)
			{
				DeleteAt(i);
				deleted_count++;
				i--;
			}
		}
		if (deleted_count > 0)
		{
			return true;
		}
		return false;
	}

	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
			Last_Index--;
		}
	}

	//void Merge(LinkedList* temp)
	//{
	//	if (temp->isEmpty())
	//	{
	//		return;
	//	}
	//	if (isEmpty())
	//	{
	//		Head = temp->GetNodeAt(0);
	//		count = temp->GetCount();
	//		temp->Head = nullptr;
	//		temp->count = -1;
	//		return;
	//	}

	//	Node<T>* last = GetLastNode();
	//	last->setNext(temp->GetNodeAt(0));
	//	count = count + temp->GetCount() + 1;
	//}

	void Reverses()
	{
		Node<T>* currentPtr = Head;
		Node<T>* prevPtr = nullptr, * nextPtr = nullptr;

		while (currentPtr != nullptr) {
			nextPtr = currentPtr->getNext();
			currentPtr->setNext(prevPtr);
			prevPtr = currentPtr;
			currentPtr = nextPtr;
		}

		Head = prevPtr;
	}
};



template<typename T>
ostream& operator << (ostream& out, const LinkedList<T>& List)
{
	if (List.Last_Index == -1)
	{
		cout << "there is no elements in the list";
		return out;
	}

	Node<T>* p = List.Head;

	while (p)
	{
		out << *(p->getItem());
		if (p->getNext() != nullptr) out << ", ";
		p = p->getNext();
	}
	return out;
}



#endif	
