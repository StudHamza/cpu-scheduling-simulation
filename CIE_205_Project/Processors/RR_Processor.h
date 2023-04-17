#pragma once

#include "Processor.h"

class RR_Processor : public Processor
{
	LinkedQueue<Process*> RDY;
	int slice_time;
	int Reamaing_time_to_change;

	void Print_Processor(ostream& out)  const override
	{
		out << "I Am RR";
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
	
	bool Add_Process_To_RDY(Process* p) override
	{
		RDY.enqueue(p);
		int time = p->Get_Time_Till_Next_IO();
		Length = Length + time;
		return true;
	}

	void Add_Next_Process_To_Run() override
	{
		RDY.dequeue(RunningProcess);
	}

	bool Remove_process_From_RUN(Process* p)
	{
		Add_Next_Process_To_Run();
		int time = p->Get_Time_Till_Next_IO();
		Length = Length - time;
		return true;
	}

	bool Remove_Process_From_RDY(Process* p)
	{
		int time = p->Get_Time_Till_Next_IO();
		Length = Length - time;
		RDY.DeleteNode(p);
		return true;
	}

	Process* Remove_Process_On_Top()
	{
		Process* temp;
		RDY.dequeue(temp);
		int time = temp->Get_Time_Till_Next_IO();
		Length = Length - time;
		return temp;
	}


	bool Remove_Process_From_Processor(Process* p)
	{
		if (RunningProcess == p)
		{
			Remove_process_From_RUN(p);
			return true;
		}
		else
		{
			Remove_Process_From_RDY(p);
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
};