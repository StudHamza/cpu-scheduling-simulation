#pragma once

#include "Processor.h"
#include <cstdlib>
#include <time.h>

class FCFS_Processor : public Processor
{
	LinkedQueue<Process*> RDY;

	// Overloading //

	void Print_Processor(ostream& out) const override
	{
		if (RDY.isEmpty()) out << " EMPTY";
		else {
			out << RDY;
		}
		
	}


	int fork_p ;

public:

	FCFS_Processor(int , int);



	void Update() override;
	


	// Called by Scheduler to create //
	bool Fork();



	// Called by the scheduler to add //
	bool Add_Process_To_RDY(Process*& p) override;



	// Moves from RDY to RUN //
	void Add_Next_Process_To_Run() override;


	// ONLY used by RR, EDF and Scheduler //

	bool Remove_process_From_RUN(Process*& p);


	// ONLY USED FOR MIGRATION //
	/* Used By the Scheduler only */
	bool Remove_Process_From_RDY(Process*& p);



	// USED FOR KILL SIGNAL ONLY //
	bool Remove_Process_From_Processor(Process*& p);


	
	~FCFS_Processor();


		// RDY GETTER //

	LinkedQueue<Process*> getRDY();
};

