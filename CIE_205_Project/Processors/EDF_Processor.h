//#pragma once
//
//#include "Processor.h"
//
//class EDF_Processor : public Processor
//{
//	Priority_Queue<Process*> RDY; // priorty queue
//	void Print_Processor(ostream& out)  const override
//	{
//		out << RDY;
//	}
//public:
//
//	EDF_Processor() : Processor("SJF") {}
//
//	void Update(const int& time) override
//	{
//
//	}
//
//	bool Add_Process_To_RDY(Process * p, const int & time) override
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
//
//	void Add_Next_Process_To_Run() override
//	{
//		RDY.dequeue(RunningProcess);
//	}
//
//	~EDF_Processor()
//	{
//
//	}
//};