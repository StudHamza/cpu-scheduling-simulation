#pragma once



#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/Array.h"
#include "../Data_Structures/LinkedQueue.h"
#include "../Data_Structures/Priority_Queue.h"
#include "../Process/Process.h"
#include "../Process/Process.h"


#include <iostream>
using namespace std;

class Processor {
protected:


	// Variables //
	int ID;

	int Length ;

	string type;

	Process* RunningProcess;

	int clock;

	int BUSY;
	int IDE; 


	Processor(string, int ID);

	virtual void Add_Next_Process_To_Run() = 0;

	virtual void Print_Processor(ostream&) const = 0;

public:

	//    Over loader   //
	friend ostream& operator << (ostream&, const Processor&);

	// Pure virual Functions //

	virtual void Update() = 0;

	virtual bool const isIDE() = 0; 

	virtual bool Add_Process_To_RDY(Process* &p) = 0;

	// Memeber functions //

	bool Check_IO(Process * &);		//Only checks Io

	bool Check_Running_process_If_Finished(Process * &);

	string getType();

	int getLength();

	bool getRunning(Process * &);


};



// Overloading

inline ostream& operator << (ostream& out, const Processor& P)
{
	P.Print_Processor(out);
	return out;
}



