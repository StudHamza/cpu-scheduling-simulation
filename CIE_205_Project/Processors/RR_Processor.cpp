#include "RR_Processor.h"

RR_Processor::RR_Processor( int ID): Processor("RR", ID)
{
	time_slice = 0;
	slice_counter = 0;
}

void RR_Processor::Update()
{
	clock++;

	// Update Running Process //

	if (RDY.isEmpty() && RunningProcess == nullptr)
	{
		this->IDE++;
		return;
	}

	// Slice time is not done yet and process is still running //
	else if (RunningProcess != nullptr && slice_counter !=0)
	{
		this->BUSY++;

		//IO checking is in Scheduler
		/* if(RunningProcess->checkIO() then popIO and Remove form running  */

		RunningProcess->update_();

		slice_counter--;
	}

	// Slice time is up during process running //
	else if (RunningProcess != nullptr && slice_counter==0)
	{
		Process* P;
		if (Remove_process_From_RUN(P))
		{
			Add_Process_To_RDY(P);
		}

	}
	// Nothing is running at this current time step //
	else
	{
		this->IDE++;
		if (slice_counter == 0)
		{
			Add_Next_Process_To_Run();
		}
		else
		slice_counter--;
	}

	// Updating RDY //

	if (!RDY.isEmpty())
	{
		for (int i = 0; i < RDY.GetSize(); i++)
		{
			RDY[i]->update_();
		}
	}

}

bool RR_Processor::Add_Process_To_RDY(Process*& p)
{
	p->setProcessorID(ID);

	Length += p->getRT();

	return (RDY.enqueue(p));
}

void RR_Processor::Add_Next_Process_To_Run()
{
	if (RDY.dequeue(RunningProcess))
	{
		RunningProcess->setResponseT(clock);	//Happens only once in the Process (if statment used)

		slice_counter = time_slice;

		RunningProcess->setExecuting(true);
	}
}

bool RR_Processor::Remove_process_From_RUN(Process*& p)
{
	if (RunningProcess)
	{
		p = RunningProcess;

		p->setExecuting(false);

		RunningProcess = nullptr;

		Length = Length - p->getRT();

		return true;
	}
	return false;
}

void RR_Processor::setTimeSlice(int i)
{
	time_slice = i;
}

RR_Processor::~RR_Processor()
{
	RDY.~LinkedQueue();
}




