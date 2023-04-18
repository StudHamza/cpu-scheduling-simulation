#include <iostream>
using namespace std;
#include "UI/UI.h"
#include "Data_Structures/Priority_Queue.h"


int main()
{

	Priority_Queue<string> p;

	Pair<string, int> Name_1("Hamza", 10);

	Pair<string, int> Name_12("Amr", 16);

	Pair<string, int> Name_123("Yara", 17);

	Pair<string, int> Name_13("OMAR", 111);

	Pair<string, int> Name_22("AHMED", 2222);




	p.enqueue(Name_12);

	p.enqueue(Name_22);

	cout << p;



	// CREATE OBJECT //
	//UI program;


	// Start the Interface //
	//program.Start();

}


