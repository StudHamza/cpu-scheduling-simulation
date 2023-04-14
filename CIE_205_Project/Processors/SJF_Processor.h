#pragma once

#include "Processor.h"

class SJF_Processor : Processor
{
	LinkedQueue<Processor*> RDY; // priorty queue

public:

	SJF_Processor() : Processor("SJF") {}

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

	}

	void Remove_Process_From_RDY() override
	{

	}



	~SJF_Processor()
	{
	
	}
};