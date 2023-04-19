#include "SJF_Processor.h"



SJF_Processor::SJF_Processor(int ID) : Processor("SJF", ID)
{

}



// FROM RDY to RUN //

void SJF_Processor::Add_Next_Process_To_Run()
{
	
	if (RDY.isEmpty()) return;

	RDY.dequeue(RunningProcess);

	RunningProcess->setResponseT(clock);	//Happens only once in the Process (if statment used)

	RunningProcess->setExecuting(true);
}



// Used By Scheduler only to move process from NEW to RDY //

bool SJF_Processor::Add_Process_To_RDY(Process*& p)
{
	p->setProcessorID(ID);

	Length += p->getRT();


	// Remaining Time * -1, highest priority goes to less RT //
	Pair< Process*, int> P (p, (-1 * (p->getRT())));

	return (RDY.enqueue(P));
}



// Main Update Function //
void SJF_Processor::Update()
{
	clock++;

	// Update Running Process //
	if (RDY.isEmpty() && RunningProcess == nullptr) return;

	if (RunningProcess != nullptr)
	{
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
		for (int i=0; i < RDY.size(); i++)
		{
			RDY[i]->update_();
		}
	}

}