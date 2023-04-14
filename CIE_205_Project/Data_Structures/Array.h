#pragma once


#include <iostream>
using namespace std;


template <typename T>
class Array
{
private:
	T* my_array;
	int Last_Index;
	int size;
	//You can add tail pointer too (depending on your problem)
public:

	///////////////////////////////////////Constructors/////////////////////////////////////////////
	Array(int size) : Last_Index(-1), size(size), my_array(new T[size]) {} //O(n)


	~Array() // O(1)
	{
		delete[] my_array;
	}





	/////////////////////////////////////Operators Overloads////////////////////////////////////////
	T operator[](int index) // O(1)
	{
		if (index < 0 || index > Last_Index) {
			throw out_of_range("Index out of range");
		}
		return my_array[index];
	}




	///////////////////////////////////////////Getters//////////////////////////////////////////////
	int GetSize() const // O(1)
	{
		return size;
	}

	int GetCount() const // O(1)
	{
		return Last_Index;
	}

	T GetElementAt(int index) const // O(n)
	{
		if (Last_Index == -1)
		{
			throw out_of_range("The list is empty");
		}
		if (index < 0 || index > Last_Index) {
			throw out_of_range("Index out of range");
		}
		return my_array[index];
	}

	T GetLastElement() const // O(n)
	{
		if (Last_Index == -1)
		{
			throw out_of_range("The list is empty");
		}
		return my_array[Last_Index];
	}
	


	///////////////////////////////////////////Setters//////////////////////////////////////////////
	bool InsertAt(const T& data, int index)
	{
		if ((index > Last_Index + 1) || (index < 0))
		{
			throw out_of_range("Index out of range");
		}

		if (Last_Index == size - 1)
		{
			throw out_of_range("Array is full");
		}

		my_array[index] = data;
		Last_Index++;
		return true;
	}

	bool InsertBeg(const T& data)
	{
		bool x = InsertAt(data, 0);
		return x;
	}

	bool InsertEnd(const T& data)
	{
		bool x = InsertAt(data, Last_Index + 1);
		return x;
	}


	///////////////////////////////////////////Deletions//////////////////////////////////////////////

	bool DeleteAt(int index)
	{
		if ((index > Last_Index) || (index < 0))
		{
			cout << "index out of range\n";
			return false;
		}
		else
		{
			for (int i = index; i < Last_Index; i++)
			{
				my_array[i] = my_array[i + 1];
			}
			my_array[Last_Index] = NULL;
			Last_Index--;
			return true;
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
			if (GetElementAt(i) == data)
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
			if (GetElementAt(i)->getItem() == data)
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
		Last_Index = -1;
	}


	///////////////////////////////////////////Searching//////////////////////////////////////////////

	bool Find(const T& data)
	{
		if (Last_Index == -1)
		{
			return false;
		}

		for (int i = 0; i <= Last_Index; i++)
		{
			if (my_array[i] == data)
			{
				return true;
			}
		}
		return false;
	}

	int CountOccurance(const T& data)
	{
		if (Last_Index == -1)
		{
			return 0;
		}

		int appearance_count = 0;

		for (int i = 0; i <= Last_Index; i++)
		{
			if (my_array[i] == data)
			{
				appearance_count++;
			}
		}
		return appearance_count;
	}

	///////////////////////////////////////////Other Operations//////////////////////////////////////////////

	void Merge(Array to_merge)
	{
		int new_size = size + to_merge.GetSize();
		int new_count = Last_Index + to_merge.GetCount();
		T* new_array = new T[new_size];
		
		for (int i = 0; i < Last_Index; i++)
		{
			new_array[i] = my_array[i];
		}
		for (int i = 0; i < to_merge.GetCount(); i++)
		{
			new_array[i + Last_Index] = to_merge[i];
		}

		delete[] my_array;
		my_array = new_array;
		size = new_size;
		Last_Index = new_count;
	}
	
	void Reverses()
	{
		int n = Last_Index + 1;
		for (int i = 0; i < n / 2; i++) {
			T temp = my_array[i];
			my_array[i] = my_array[n - i - 1];
			my_array[n - i - 1] = temp;
		}
	}


	void PrintList() const
	{
		if (Last_Index == -1)
		{
			cout << "there is no elements in the list";
			return;
		}
		cout << "\nprinting list contents:\n\n";
		for (int i = 0; i <= Last_Index; i++)
		{
			cout << "[ " << my_array[i] << " ] ";
		}
		for (int i = Last_Index + 1; i < size; i++)
		{
			cout << "[ * ] ";
		}
	}
};
