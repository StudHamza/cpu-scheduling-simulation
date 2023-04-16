#pragma once

#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/Array.h"
#include "../Data_Structures/LinkedQueue.h"
#include "../Process/Process.h"
#include "../Process/Process.h"


#include <iostream>
using namespace std;

class Processor {
protected:
	string type;

	int Length;

	Process* RunningProcess;


	Processor(string type)
	{
		this->type = type;
	}


public:

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
			if (RunningProcess->Get_Time_Left() == 0)
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

	int Get_Time_Expected_To_Finish()
	{
		return Length;
	}


	virtual void Update() = 0;
	

	virtual void Add_Process_To_RDY(Process* p) = 0;

	
	virtual void Add_Next_Process_To_Run() = 0;

	
	virtual void Remove_Process(int ID) = 0;


};