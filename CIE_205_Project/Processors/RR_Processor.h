#pragma once

#include "Processor.h"

class RR_Processor : public Processor
{
	LinkedQueue<Process*> RDY;
	int slice_time;
	int Reamaing_time_to_change;

	void Print_Processor(ostream& out)  const override
	{
		out << RDY;
	}
public:

	RR_Processor(int slice_t) : Processor("RR") { slice_time = slice_t; Reamaing_time_to_change = slice_t; }



	void Update(const int& time) override
	{
		RunningProcess->Update_Process(time , true);
		for (int i = 0; i < RDY.GetSize(); i++)
		{
			RDY[i]->Update_Process(time, false);
		}
		Reamaing_time_to_change--;
		if (Reamaing_time_to_change == 0)
		{
			RDY.enqueue(RunningProcess);
			RDY.dequeue(RunningProcess);
			Reamaing_time_to_change = slice_time;
		}
	}
	
	bool Add_Process_To_RDY(Process* p, const int & time) override
	{
		RDY.enqueue(p);
		int t = p->Get_Time_Till_Next_IO(time);
		Length = Length + t;
		return true;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}

	bool Remove_process_From_RUN(Process* p, const int & time)
	{
		Add_Next_Process_To_Run();
		int t = p->Get_Time_Till_Next_IO(time);
		Length = Length - t;
		return true;
	}

	bool Remove_Process_From_RDY(Process* p, const int& time)
	{
		int t = p->Get_Time_Till_Next_IO(time);
		Length = Length - t;
		RDY.DeleteNode(p);
		return true;
	}

	Process* Remove_Process_On_Top(const int& time)
	{
		Process* temp;
		RDY.dequeue(temp);
		int t = temp->Get_Time_Till_Next_IO(time);
		Length = Length - t;
		return temp;
	}


	bool Remove_Process_From_Processor(Process* p, const int& time)
	{
		if (RunningProcess == p)
		{
			Remove_process_From_RUN(p, time);
			return true;
		}
		else
		{
			Remove_Process_From_RDY(p, time);
			return true;
		}
		return false;
	}

	~RR_Processor() 
	{
	
	}


	void setSlice(int t)
	{
		slice_time = t;

	};

	LinkedQueue<Process*> getRDY()
	{ return RDY; }
};