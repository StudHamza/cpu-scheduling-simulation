#pragma once

#include "Processor.h"

class SJF_Processor : public Processor
{
	Priority_Queue<Process*> RDY; // priorty queue

	void Print_Processor(ostream& out)  const override
	{
		if (RDY.isEmpty()) out << " EMPTY";
		else {
			out << RDY;
		}
	}
public:

	SJF_Processor(int ID);

	void Add_Next_Process_To_Run() override;

	bool Add_Process_To_RDY(Process*& p) override;

	void Update() override;

	~SJF_Processor();
};