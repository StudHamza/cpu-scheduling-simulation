#pragma once

struct IO_R_D
{
	int IO_Request_Time;
	int IO_Duration;
};


class Process
{
	int PID;
	int Arrival_Time;
	int CPU_Time;
	IO_R_D Pair;
	int Termination_Time;
	int Time_Left;
	int Respose_Time;
	int Turn_Around_Time;
	int Waiting_Time;
	bool Is_Running;
	Process* Child;


public:
	Process(int ID, int AT,int CT, IO_R_D pair)
	{
		PID = ID;
		Arrival_Time = AT;
		CPU_Time = CT;
		Pair = pair;
		Time_Left = CPU_Time;
	}

	int Get_PID()
	{
		return PID;
	}

	int Get_CPU_Time()
	{
		return CPU_Time;
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

