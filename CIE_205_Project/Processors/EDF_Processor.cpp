#include "EDF_Processor.h"

EDF_Processor::EDF_Processor(int ID): Processor("EDF", ID)
{
}

void EDF_Processor::Add_Next_Process_To_Run()
{
	if (RDY.isEmpty()) return;

	RDY.dequeue(RunningProcess);

	RunningProcess->setResponseT(clock);	//Happens only once in the Process (if statment used)

	RunningProcess->setExecuting(true);
}

bool EDF_Processor::Add_Process_To_RDY(Process*& p)
{
	p->setProcessorID(ID);

	Length += p->getRT();


	// DeadLine * -1, highest priority goes to closest Deadline //
	Pair< Process*, int> P(p, (-1 * (p->getDeadLine())));

	return (RDY.enqueue(P));
}


// Main Update Function //
void EDF_Processor::Update()
{
	clock++;

	// Update Running Process //

	// First OverHeat: Empty processor
	if(overHeatCounter == OverHeat)

	if (RDY.isEmpty() && RunningProcess == nullptr) return;

	
	if (RunningProcess != nullptr)
	{
		// Check DeadLines
		if(CompareDeadline());
		{
			Process* P = nullptr;
			Remove_process_From_RUN(P);
			Add_Process_To_RDY(P);
			Add_Next_Process_To_Run();
		}
		this->BUSY++;

		//IO checking is in Scheduler
		/* if(RunningProcess->checkIO() then popIO and Remove form running  */

		RunningProcess->update_();
	}
	else if (!RDY.isEmpty())
	{
		this->IDE++;
		Add_Next_Process_To_Run();
	}

	// Updating RDY	//

	if (!RDY.isEmpty())
	{
		for (int i = 0; i < RDY.size(); i++)
		{
			RDY[i]->update_();
		}
	}


	// Check OverHeating // 




}


bool EDF_Processor::CompareDeadline()
{
	Process* temp = nullptr;
	RDY.peek(temp);
	if (temp->getDeadLine() < RunningProcess->getDeadLine()) return true;
	return false;
}










//Pops from RUN //
/* Used by RR, Scheduler and EDF ONLY ...... No other processor should use it*/

bool EDF_Processor::Remove_process_From_RUN(Process*& p)
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






