#pragma once

#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/Array.h"
#include "../Data_Structures/LinkedQueue.h"
#include "../Data_Structures/Priority_Queue.h"
#include "../Process/Process.h"


#include <iostream>
using namespace std;

class Processor {
protected:
	int ID;
	int Length;
	string type;


	Process* RunningProcess;


	Processor(string type)
	{
		this->type = type;
	}

	virtual void Add_Next_Process_To_Run() = 0;

public:

	int GetID() const
	{
		return ID;
	}

	string GetType() const
	{
		return type;
	}

	Process* GetRunningProcess() const
	{
		return RunningProcess;
	}
	
	virtual void Add_Process_To_RDY(Process* p) {};		//Change to pure later

	virtual void Remove_Process_From_RDY(int ID) {};		//change to pure later




	virtual void Update() = 0;

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

	int Get_Time_Expected_To_Finish() {	return Length; }

};