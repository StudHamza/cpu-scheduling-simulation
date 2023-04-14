#pragma once

#include "Processor.h"

class EDF_Processor : Processor
{
	LinkedQueue<Processor*> RDY; // priorty queue

public:

	EDF_Processor() : Processor("SJF") {}

	void Excute() override
	{

	}

	void Update() override
	{

	}

	void Add_Process_To_RDY(Processor* p) override
	{
		
	}

	void Remove_Process_From_RDY() override
	{
		
	}


	~EDF_Processor()
	{

	}
};