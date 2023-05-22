#pragma once

#include "Processor.h"

class EDF_Processor : public Processor
{
	Priority_Queue<Process*> RDY; // priorty queue

	void Print_Processor(ostream& out)  const override
	{
		if (RDY.isEmpty()) out << " EMPTY";
		else {
			out << RDY;
		}
	}

	bool CompareDeadline();

	//For OverHeat//
	//void EmptyProcessor() override;

public:

	EDF_Processor(int ID);

	void Add_Next_Process_To_Run() override;

	bool Add_Process_To_RDY(Process*& p) override;


	// ONLY used by RR, EDF and Scheduler //

	bool Remove_process_From_RUN(Process*& p);


	void Update() override;


	~EDF_Processor();
};