#include "Process.h"



Process::Process(int ID, int AT, int CT, LinkedQueue<Pair<int, int>> IO_Pairs)
{
	PID = ID;
	Arrival_Time = AT;
	CPU_Time = CT;
	IO_pairs = IO_Pairs;

	//  //
	Remaining_Time = CT;
	Termination_Time = 0;
	Response_Time = -1;
	Turn_Around_Time = 0;
	Waiting_Time = 0;
	ProcessorID = 0;
	Executing_Time = 0;
	IOCounter = 0;
	executing = false;
	Child = nullptr;

}



/*     Getters and setters to variables  */

int const Process::getID() 
{
	return PID;
}


int const Process::getAT()
{
	return Arrival_Time;
}

int const Process::getCT()
{
	return CPU_Time;
}

int const Process::getRT()
{
	return Remaining_Time;
}

int const Process::getWT()
{
	return Waiting_Time;
}

int const Process::getProcessorID()
{
	return ProcessorID;
}


bool const Process::checkIO()
{
	Pair<int, int> IO;
	if (IO_pairs.isEmpty())return false;
	else if (IOCounter == 0)
	{
		IO_pairs.peek(IO);
		if (IO.left == Executing_Time)
		{
			return true;
		}	
	}
	return false;
}

void Process::setTRT()
{
	Turn_Around_Time = Termination_Time - Arrival_Time; 
}

void Process::setTT(int t)
{
	Termination_Time = t;
}

void Process::setResponseT(const int tclock)
{
	if (Response_Time == -1)
	{
		Response_Time = tclock - Arrival_Time;
	}
	
}


void Process::setExecuting(const bool t)
{
	executing = t;
}



//        UPDATORS         //


bool Process::popIO()
{
	try
	{
		//Pops IO

		Pair<int, int> temp;
		IO_pairs.dequeue(temp);
		

		//Sets Counter

		temp.right = IOCounter;

		return true;
		throw false;
	}
	catch (bool t)
	{
		return t;
	}
}

bool Process::updateIO()
{
	if (IOCounter)
	{
		IOCounter--;
		return true;
	}
	else return false;
	
}


// Called only in the FCFS run and Using fork probability 

Process* Process::fork_process(const int & clock)
{
	int id = PID + 1000;
	int ct = Remaining_Time;
	int at = clock;
	
	LinkedQueue<Pair<int, int>> IO;

	Process* P = new Process(id, at, ct, IO);

	Child = P;

	return P;
}


void Process::updateWT()
{
	if (!executing)
	{
		Waiting_Time++;
	}
}

void Process::update_()
{
	updateWT();

	if (executing)
	{
		Remaining_Time--;
		Executing_Time++;
	}
}