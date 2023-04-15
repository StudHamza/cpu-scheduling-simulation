#pragma once

#include "Processor.h"

class EDF_Processor : public Processor
{
	LinkedQueue<Processor*> RDY; // priorty queue

public:

	EDF_Processor() : Processor("SJF") {}

	void Update() override
	{

	}

	void Add_Process_To_RDY(Process* p) override
	{
		RDY.enqueue(p);
		int time; // = p->Get_Time_Till_Next_IO();
		Length = Length + time;
	}

	void Remove_Process_From_RDY() override
	{
		
	}


	~EDF_Processor()
	{

	}
};