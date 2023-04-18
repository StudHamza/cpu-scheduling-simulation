//#pragma once
//
//#include "Processor.h"
//
//class SJF_Processor : public Processor
//{
//	Priority_Queue<Process*> RDY; // priorty queue
//	void Print_Processor(ostream& out)  const override
//	{
//		out << "I Am SJF";
//	}
//public:
//	
//	SJF_Processor() : Processor("SJF") {}
//
//	void Update(const int& time) override
//	{
//		if (RunningProcess != nullptr)
//		{
//			RunningProcess->Update_Process(time, true);
//		}
//		
//		//for (int i = 0; i < RDY.GetSize(); i++)
//		//{
//		//	RDY[i]->Update_Process(time, false);
//		//}
//	}
//
//	bool Add_Process_To_RDY(Process* p, const int& time) override
//	{
//		int t = p->Get_Time_Till_Next_IO(time);
//		Pair<Process*, int> x;
//		x.left = p;
//		x.right = t * -1;
//		RDY.enqueue(x);
//		Length = Length + t;
//		return true;
//	}
//
//	void Add_Next_Process_To_Run() override
//	{
//		RDY.dequeue(RunningProcess);
//	}
//
//
//
//	~SJF_Processor()
//	{
//	
//	}
//};