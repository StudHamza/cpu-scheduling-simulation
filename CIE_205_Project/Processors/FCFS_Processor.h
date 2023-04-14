#pragma once

#include "Processor.h"

class FCFS_Processor : Processor
{
	LinkedQueue<Processor*> RDY;

public:

	FCFS_Processor() : Processor("FCFS") {}

	void Excute() override
	{
		if (RunningProcess)
		{
			RunningProcessRemainingTime = RunningProcessRemainingTime - 1;
			if (RunningProcessRemainingTime == 0)
			{
				//send it to termenate
			}
			if (true)//requested I O 
			{
				//send to BLK
				RunningProcess = nullptr;
				RunningProcessRemainingTime = 0;
			}
		}
		else
		{
			RDY.dequeue(RunningProcess);
			//RunningProcessRemainingTime = RunningProcess. get cpu time
		}
	}

	void Update() override
	{

	}
	
	void Add_Process_To_RDY(Processor* p) override
	{
		RDY.enqueue(p);
	}

	void Remove_Process_From_RDY() override
	{
		//Rdy.deleteat (index)
	}


	
	~FCFS_Processor()
	{

	}
};

