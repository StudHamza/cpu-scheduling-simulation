#include "FCFS_Processor.h"




FCFS_Processor::FCFS_Processor(int id , int fp) : Processor("FCFS", id)
{
	fork_p = fp;
}


void FCFS_Processor::Add_Next_Process_To_Run()
{
	if (RDY.dequeue(RunningProcess))
	{
		RunningProcess->setResponseT(clock);	//Happens only once in the Process (if statment used)

		RunningProcess->setExecuting(true);
	}

}




void FCFS_Processor::Update()
{
	clock++;

	//Update Running Process
	if (RDY.isEmpty() && RunningProcess == nullptr) return;

	if (RunningProcess != nullptr)
	{
		this->BUSY++;

		//IO checking is in Scheduler
		/* if(RunningProcess->checkIO() then popIO and Remove form running  */

		RunningProcess->update_();
	}
	else
	{
		this->IDE++;
		Add_Next_Process_To_Run();
	}

	//Updating RDY

	if (!RDY.isEmpty())
	{
		for (int i = 0; i < RDY.GetSize(); i++)
		{
			RDY[i]->update_();
		}
	}


	// Forking is performed in Scheduler //

	// Removing from RUN is in Scheduler //
	
}


bool FCFS_Processor::Fork()
{
	srand(time(0));

	int fork = rand() % 100;

	if (fork >= fork_p) return true;

	return false;
}



// Used to move from new to RDY //

bool FCFS_Processor::Add_Process_To_RDY(Process* &p)
{
	p->setProcessorID(ID);
		
	Length += p->getRT();

	return (RDY.enqueue(p));
}



//Pops from RUN //
/* Used by RR, Scheduler and EDF ONLY ...... No other processor should use it*/

bool FCFS_Processor::Remove_process_From_RUN(Process * & p)
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



// Pops process from RDY list for migration only //
bool FCFS_Processor::Remove_Process_From_RDY(Process * &p)
{
	if (RDY.isEmpty()) return false;

	Length -= p->getRT();

	RDY.DeleteNode(p);

	return true;
}


bool FCFS_Processor::Remove_Process_From_Processor(Process * &p)
{
	if (RunningProcess == p)
	{
		Remove_process_From_RUN(p);
		return true;
	}
	else if (!RDY.isEmpty())
	{
		Remove_Process_From_RDY(p);
		return true;
	}
	return false;
}


FCFS_Processor::~FCFS_Processor()
{
	RDY.~LinkedQueue();

}

LinkedQueue<Process*> FCFS_Processor::getRDY()
{
	return this->RDY;
};