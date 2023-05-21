#include "Process.h"



Process::Process(int ID, int AT, int CT,int DL, LinkedQueue<Pair<int, int>> IO_Pairs)
{
	PID = ID;
	Arrival_Time = AT;
	CPU_Time = CT;
	IO_pairs = IO_Pairs;
	DeadLine = DL;

	//  //
	Remaining_Time = CT;
	Termination_Time = 0;
	Response_Time = -1;
	Turn_Around_Time = 0;
	Waiting_Time = 0;
	ProcessorID = -1;
	Executing_Time = 0;
	IOCounter = 0;
	executing = false;
	Child = nullptr;
	done = false;

}



/*     Getters and setters to variables  */

int Process::getID()  const
{
	return PID;
}


int Process::getAT() const
{
	return Arrival_Time;
}

int Process::getCT() const
{
	return CPU_Time;
}

int Process::getRT() const
{
	return Remaining_Time;
}

int Process::getWT() const
{
	return Waiting_Time;
}

int Process::getProcessorID() const
{

	return ProcessorID;
}

int Process::getDeadLine() const
{
	return this->DeadLine;
}

bool Process::isDone() const
{
	return done;
}

bool Process::checkIO() const
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
	this->done = true;
}

void Process::setResponseT(const int tclock)
{
	if (Response_Time == -1)
	{
		Response_Time = tclock - Arrival_Time;
	}
	
}

void Process::setProcessorID(int id)
{
	ProcessorID = id;
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

		IOCounter = temp.right;

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

Process* Process::fork_process(const int & clock, int &Id)
{
	if (Child != nullptr) return nullptr;
	Id++;
	int id = Id ;
	int ct = Remaining_Time;
	int at = clock;
	srand(time(0));
	int dl = (rand() % at) + clock;
	LinkedQueue<Pair<int, int>> IO;

	Process* P = new Process(id, at, dl,ct, IO);

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

Process * Process::terminate(const int &time)
{
	this->setProcessorID(-1);
	this->setTT(time);
	this->setTRT();
	this->setExecuting(false);
	
	return Child;

}