#pragma once

#include "Processor.h"

class SJF_Processor : public Processor
{
	LinkedQueue<Process*> RDY; // priorty queue

public:

	SJF_Processor() : Processor("SJF") {}

	void Update() override
	{
		RunningProcess->Update_Process();
	}

	void Add_Process_To_RDY(Process* p) override
	{
		RDY.enqueue(p);
		int time = p->Get_Time_Till_Next_IO();
		Length = Length + time;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}

	void Remove_Process(int ID) override
	{
		//process* temp = Rdy.delete(ID);
		int time; // = temp->Get_Time_Till_Next_IO();
		Length = Length - time;
		//delete temp;
		//temp = nullptr;
	}



	~SJF_Processor()
	{
	
	}
};