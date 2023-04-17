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
	int ID;
	int Length = 0;
	string type;
	Process* RunningProcess;


	Processor(string type)
	{
		this->type = type;
	}

	virtual void Add_Next_Process_To_Run() = 0;
	virtual void Print_Processor(ostream&) const = 0;

public:
	friend ostream& operator << (ostream&, const Processor&);

	virtual void Update(const int& time) = 0;
	virtual bool Add_Process_To_RDY(Process* p, const int&) = 0;

	Process* Check_IO(int Current_time)
	{
		Process* temp = RunningProcess;
		if (RunningProcess)
		{
			if (RunningProcess->Need_IO_Now(Current_time))
			{
				Add_Next_Process_To_Run();
				return temp;
			}
			return nullptr;
		}
		else
		{
			Add_Next_Process_To_Run();
			return nullptr;
		}
	}

	Process* Check_Runnuig_process_If_Finished()
	{
		Process* temp = RunningProcess;
		if (RunningProcess)
		{
			if (RunningProcess->Is_Finished())
			{
				Add_Next_Process_To_Run();
				return temp;
			}
			return nullptr;
		}
		else
		{
			Add_Next_Process_To_Run();
			return nullptr;
		}
	}

	string getType() { return this->type; }

	int Get_Time_Expected_To_Finish() {	return Length; }
};


inline ostream& operator << (ostream& out, const Processor& P)
{
	P.Print_Processor(out);
	return out;
}



