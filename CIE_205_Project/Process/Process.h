#pragma once
#include "..\Data_Structures\LinkedList.h"
#include "../Data_Structures/SharedClasses/Pair.h"
#include "../Data_Structures/LinkedList.h"


class Process
{
	int PID;
	int Arrival_Time;
	int CPU_Time;
	int CPU_Time_Left;
	int Termination_Time = 0;
	int Respose_Time = 0;
	int Turn_Around_Time = 0;
	int Waiting_Time = 0;

	LinkedList<Pair<int, int>>* IO_pairs;

	bool Started = false;
	Process* Child;


public:
	friend ostream& operator << (ostream & ,const Process &);

	Process(int ID, int AT,int CT, LinkedList<Pair<int, int>>* IO_Pairs)
	{
		PID = ID;
		Arrival_Time = AT;
		CPU_Time = CT;
		IO_pairs = IO_Pairs;
		CPU_Time_Left = CPU_Time;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	int Get_PID()
	{
		return PID;
	}

	int Get_Arrival_time()
	{
		return Arrival_Time;
	}

	bool Check_CPU_Time_Left(int STL)
	{
		if (CPU_Time_Left < STL)
		{
			return true;
		}
		return false;
	}

	bool Check_Waiting_Time(int MaxW)
	{
		if (Waiting_Time > MaxW)
		{
			return true;
		}
		return false;
	}

	int Get_Turn_Arround_Time()
	{
		if (Is_Finished())
		{
			return Termination_Time - Arrival_Time;
		}
		return 0;
	}

	int Get_Time_Till_Next_IO(int& Current_Time)
	{
		int temp = IO_pairs->GetNodeAt(0)->getItem().left - Current_Time;
		return temp;
	}

	Pair<int, int> Get_Next_IO_Pair()
	{
		Pair<int,int> temp = IO_pairs->DeleteFirst();
		return temp;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	bool Need_IO_Now(int Current_Time)
	{
		if (IO_pairs->GetNodeAt(0)->getItem().left == Current_Time)
		{
			return true;
		}
		return false;
	}

	bool Is_Finished()
	{
		if (CPU_Time_Left == 0)
		{
			return true;
		}
		return false;
	}

	bool Is_Arrived(int Current_Time)
	{
		if (Current_Time == Arrival_Time)
		{
			return true;
		}
		return false;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	void Update_Process(const int& time , bool running)
	{
		if (!Started)
		{
			Respose_Time = time - Arrival_Time;
			Started = true;
		}
		if (running)
		{
			CPU_Time_Left--;
			if (Is_Finished())
			{
				Termination_Time = time;
			}
		}
		else
		{
			Waiting_Time++;
		}
	}

	void Fork_Process()
	{

	}

	~Process()
	{

	}
};


inline ostream& operator << (ostream& out, const Process& P)
{
	out << P.PID;
	return out;
}