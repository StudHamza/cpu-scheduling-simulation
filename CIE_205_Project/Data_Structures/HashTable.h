#pragma once

#include "SharedClasses/Pair.h"
#include "../Processors/Processor.h"

class HashTable
{
	Pair<int, Processor*>* my_array;


public:
	HashTable(int size)
	{
		my_array = new Pair<int, Processor*>[size];
	}

	bool AddToTable(int ID, Processor* p)
	{
		Pair<int, Processor*> temp;
		temp.left = ID;
		temp.right = p;
		my_array[ID] = temp;
		return true;
	}

	void Modify(int ID, Processor* new_p)
	{
		my_array[ID].right = new_p;
	}

	Processor* Find(int ID)
	{
		return my_array[ID].right;
	}


};