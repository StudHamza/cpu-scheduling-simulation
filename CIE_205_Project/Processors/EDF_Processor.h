#pragma once

#include "Processor.h"

class EDF_Processor : public Processor
{
	LinkedQueue<Process*> RDY; // priorty queue

public:

	EDF_Processor() : Processor("SJF") {}

	void Update() override
	{

	}

	void Add_Process_To_RDY(Process * p) override
	{
		RDY.enqueue(p);
		//int time; // = p->Get_Time_Till_Next_IO();
		//Length = Length + time;
	}


	void Remove_Process_From_RDY(int ID) override

	{
		//process* temp = Rdy.delete(ID);
		//int time; // = temp->Get_Time_Till_Next_IO();
		//Length = Length - time;
		//delete temp;
		//temp = nullptr;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}

	void Add_Next_Process_To_Run() override
	{}

	~EDF_Processor()
	{

	}
};