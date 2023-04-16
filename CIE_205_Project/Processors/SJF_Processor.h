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

	bool Add_Process_To_RDY(Process* p) override
	{
		int time = p->Get_Time_Till_Next_IO();
		Pair<Process*, int> x;
		x.left = p;
		x.right = time * -1;
		RDY.enqueue(x);
		Length = Length + time;
		return true;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}



	~SJF_Processor()
	{
	
	}
};