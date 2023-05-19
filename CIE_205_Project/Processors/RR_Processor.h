#pragma once

#include "Processor.h"

class RR_Processor : public Processor
{
	LinkedQueue<Process*> RDY;
	int time_slice;

	int slice_counter;

	void Print_Processor(ostream& out)  const override
	{
		out << RDY;
	}
public:

	RR_Processor( int ID);

	void Update() override;


	
	bool Add_Process_To_RDY(Process* &p) override;


	void Add_Next_Process_To_Run() override;

	//If slice counter is == 0 //
	/* Used by Scheduler during IOs and by the processor to perform RR */
	bool Remove_process_From_RUN(Process*& p);



	// For Migration \\
	bool Remove_Process_From_RDY(Process* p, const int& time)


	//Setter
	void setTimeSlice(int);


	~RR_Processor();


	LinkedQueue<Process*> getRDY()
	{ return RDY; }
};