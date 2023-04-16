#pragma once

#include "../Data_Structures/SharedClasses/Pair.h"
#include "../Data_Structures/LinkedList.h"

struct IO_R_D
{
	int IO_Request_Time;
	int IO_Duration;
};


class Process
{
	//int PID;
	//int Arrival_Time;
	//int CPU_Time;
	LinkedList<Pair<int, int>>* IO_pairs;
	//int Termination_Time;
	//int Time_Left;
	//int Respose_Time;
	//int Turn_Around_Time;
	//int Waiting_Time;
	//bool Is_Running;
	//Process* Child;


public:
	Process(int ID, int AT,int CT, LinkedList<Pair<int, int>>* IO_Pairs)
	{
		/*PID = ID;
		Arrival_Time = AT;
		CPU_Time = CT;
		IO_pairs = IO_Pairs;
		Time_Left = CPU_Time;
		Is_Running = false;
		Child = nullptr;

		Respose_Time = NULL;
		Turn_Around_Time = NULL;
		Waiting_Time = NULL;*/

	}

	bool Need_IO_Now(int Current_Time)
	{
		return true;
	}

	int Get_PID()
	{
		/*return PID;*/
	}

	bool Is_Arrived(int Current_Time)
	{
		/*if (Current_Time == Arrival_Time)
		{
			return true;
		}
		return false;*/
	}

	int Get_CPU_Time()
	{
		/*return CPU_Time;*/
	}

	int Get_Time_Left()
	{
		/*return Time_Left;*/
	}

	int Get_Time_Till_Next_IO()
	{
		return 5;
	}

	void Update_Process()
	{

	}

	void Fork_Process()
	{

	}

	~Process()
	{

	}
};

