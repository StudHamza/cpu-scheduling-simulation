#include "Scheduler.h"
#define timestep  1

Scheduler::Scheduler()
{
}

void Scheduler::read_file(std::fstream&)
{
}


void Scheduler::new_ready_scheduler(Process* p)
{
	//for(Processor processor : Processors[pro_n])
	int min_index = 0;

	int min_num = Processors[0].getLenght();

	for (int i = 0; i < pro_n; i++) {

		int val = Processors[i].getLenght();

		if (val < min_num) { min_num = val; min_index = i; }
	}
	Processors[min_index].addToRDY(p);
}



void Scheduler::checkIOs()
{
	for (int i = 0; i < pro_n; i++)
	{
		if ((RUN[i].get_IOs()).left == time)
		{
			//move to blk list
			
		}
		
	}
}

void Scheduler::updateIOs()
{
	if (BLK.front()->get_IOs().right == IO_counter)
	{
		new_ready_scheduler(BLK.front());
		BLK.pop();
	}
	else IO_counter + 1;
}


void Scheduler::RR_SJF_migration(Processor& p)
{
	//for (Process* process : p.getRdylist()) {
	//	if (process->getRT() < RTF)
	//	{
	//		//Move to the shortest SJF queue
	//	}
	//}

}

void Scheduler::FCFS_RR_migration(Processor& p)
{
	//for (Process* process : p) {
	//	if (process->getWT() > MaxW)
	//	{
	//		//Move to the shortest RR queue
	//	}
	//}
}


void Scheduler::kill_process()
{

	while (SIGKILL.front().left == time)
	{
		//Search in Rdy queues, Run list and BLK list
		for (int i = 0; i < pro_n; i++)
		{
			Processor p = Processors[i];
			Process trm = *p.FindProcess(SIGKILL.front().right);
			terminate(trm);	//Terminate signal
		}
		
	}
}


void Scheduler::terminate(Process&)
{
	//
}


void Scheduler::update_()
{
	time += timestep;

	while (NEW.front()->getAT() == time)
	{
		new_ready_scheduler( NEW.front() );	//moving process of new to rdy
		NEW.pop_front();
	}

	checkIOs();		//From RUN to BLK

	if (!BLK.empty()) updateIOs();	//From BLK to RDY

	//Updating Processors 
	for (int i=0 ; i < pro_n ; i++)
	{
		Processors[i].update_();
		//Process from RUN to TRM list
		if (RUN[i].getRT() == 0) terminate(RUN[i]);
	}

	//steal work
	if (time % STL == 0) steal_work();

	//Kill signal check
	kill_process();


	//Migrations
	//O(n^2)
	for (int i = 0; i < pro_n; i++)
	{
		if (Processors[i].getType() == "RR")  RR_SJF_migration(Processors[i]);
		else if (Processors[i].getType() == "FCFS")  FCFS_RR_migration(Processors[i]) ;
	}

	
}


void Scheduler::steal_work()
{

}


void Scheduler::write_statistics()
{

}