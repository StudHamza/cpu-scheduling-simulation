#pragma once

#include "Processor.h"

class EDF_Processor : public Processor
{
	Priority_Queue<Process*> RDY; // priorty queue

	void Print_Processor(ostream& out)  const override
	{
		out << RDY;
	}
public:

	EDF_Processor(int ID);

	void Add_Next_Process_To_Run() override;

	bool Add_Process_To_RDY(Process*& p) override;

	void Update() override;


	~EDF_Processor();
};