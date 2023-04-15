#pragma once

#include "Processor.h"

class RR_Processor : public Processor
{
	LinkedQueue<Processor*> RDY;
	int slice_time;
	int Remaing_time_to_change;


public:

	RR_Processor(int slice_t) : Processor("RR") { slice_time = slice_t; }

	void Excute() override
	{
		if (RunningProcess)
		{
			RunningProcessRemainingTime = RunningProcessRemainingTime - 1;
			Reamaing_time_to_change--;
			if (RunningProcessRemainingTime == 0)
			{
				//send it to termenate
			}
			if (Reamaing_time_to_change == 0)
			{
				RDY.enqueue(RunningProcess);
				RDY.dequeue(RunningProcess);
				Reamaing_time_to_change = slice_time;
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
			Reamaing_time_to_change = slice_time;
			//RunningProcessRemainingTime = RunningProcess. get cpu time
		}
	}
	
	void Update() override
	{

	}
	
	void Add_Process_To_RDY(Processor* p) override
	{

	}



	void Get_Time_Expected_To_Finish() override
	{

	}
	
	~RR_Processor() 
	{
	
	}
};