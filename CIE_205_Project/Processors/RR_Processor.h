#pragma once

#include "Processor.h"

class RR_Processor : public Processor
{
	LinkedQueue<Process*> RDY;
	int slice_time;
	int Reamaing_time_to_change;


public:

	RR_Processor(int slice_t) : Processor("RR") { slice_time = slice_t; Reamaing_time_to_change = slice_t; }



	void Update() override
	{
		if (RunningProcess)
		{
			RunningProcess->Update_Process();
			Reamaing_time_to_change--;
			if (Reamaing_time_to_change == 0)
			{
				RDY.enqueue(RunningProcess);
				RDY.dequeue(RunningProcess);
				Reamaing_time_to_change = slice_time;
			}
		}
		else
		{
			RDY.dequeue(RunningProcess);
			Reamaing_time_to_change = slice_time;
		}
	}
	
	void Add_Process_To_RDY(Process* p) override
	{
		RDY.enqueue(p);
		int time = p->Get_Time_Till_Next_IO();
		Length = Length + time;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}

	void Remove_Process(int ID) override
	{
		//Process* temp;// = Rdy.delete(ID);
		//int time = temp->Get_Time_Till_Next_IO();
		//Length = Length - time;
		//delete temp;
		//temp = nullptr;
	}
	
	~RR_Processor() 
	{
	
	}
};