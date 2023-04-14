#pragma once

#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/Array.h"
#include "../Data_Structures/LinkedQueue.h"


#include <iostream>
using namespace std;

class Processor {
protected:
	string type;
	int BUSY_t;
	int IDE_t;
	int Length;

	//Process* RunningProcess;
	int RunningProcessRemainingTime;

	//Process* Process_To_Be_Killed

	int Overload;


	Processor(string type)
	{
		this->type = type;
	}

	void Set_process_to_be_killed(Processor* p)
	{
		//Process_To_Be_Killed = 
	}

public:

	virtual void Excute() = 0;

	virtual void Update() = 0;
	
	virtual void Add_Process_To_RDY(Processor* p) = 0;

	virtual void Remove_Process_From_RDY() = 0;

	virtual void Get_Time_Expected_To_Finish()
	{
		int time = 0;
		for (int i = 0;/* i < RDY.count*/; i++)
		{
			//time = time + RDY[i].get time
		}
		time = time + RunningProcessRemainingTime;
	}

	static void Kill_Process(int id)
	{
		//Processpr* temp = p.getprocessorID
		//temp.set_Process_To_Be_Killed(p)
	}

	void getRunningProcess()
	{

	}

	int getOverload()
	{

	}
};