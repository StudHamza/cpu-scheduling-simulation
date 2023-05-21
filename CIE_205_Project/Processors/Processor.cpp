#include "Processor.h"




Processor::Processor(string t ,int id)
{
	this->type = t;
	this->clock = 0;
	this->ID = id;
	this->BUSY = 0;
	this->IDE = 0;
	this->RunningProcess = nullptr;
	this->Length = 0;
}


//Checks if current running process needs IO

bool Processor::Check_IO(Process * & p)
{
	if (RunningProcess)
	{
		if (RunningProcess->checkIO())
		{
			p = RunningProcess; 
			
			RunningProcess = nullptr;

			p->popIO();

			p->setExecuting(false);

			return true;
		}
	}

	return false;
}



//  Checks if current running process is finished

bool Processor::Check_Running_process_If_Finished(Process* & p)
{
	if (RunningProcess)
	{
		if (RunningProcess->getRT() == 0)
		{
			p = RunningProcess;

			RunningProcess = nullptr;

			return true;
		}	
	}
	return false;
}



// Getters

string Processor::getType()
{
	return this->type; 
}


int Processor::getLength()
{
	return this->Length;
}


bool Processor::getRunning(Process * &p)
{
	if (RunningProcess != nullptr)
	{
		p = RunningProcess;
		return true;
	}
	
	else return false;
}
