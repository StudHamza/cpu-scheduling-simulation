#pragma once

#include "Processor.h"

class SJF_Processor : public Processor
{
	Priority_Queue<Process*> RDY; // priorty queue

public:
	
	SJF_Processor() : Processor("SJF") {}

	void Update() override
	{
		RunningProcess->Update_Process();
	}

	void Add_Process_To_RDY(Process* p) override
	{
		Pair<Process*, int> x;
		x.left = p;
		x.right = 4;
		RDY.enqueue(x);
		int time = p->Get_Time_Till_Next_IO();
		Length = Length + time;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}

	void Remove_Process_From_RDY(int ID) override
	{
		//process* temp = Rdy.delete(ID);
		//int time; // = temp->Get_Time_Till_Next_IO();
		//Length = Length - time;
		//delete temp;
		//temp = nullptr;
	}



	~SJF_Processor()
	{
	
	}
};