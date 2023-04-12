#pragma once
#include <iostream>
#include "Process.h" 
#include "Processor.h"
#include "Pair.h"
#include <queue>
#include <list>

class Scheduler
{
private:
	//Variables//

	int pro_n;	//no of processors

	std::queue<Process*> NEW;
	std::list<Process*> TRM;
	std::queue<Process*> BLK;
	std::list<Process*> RUN;
	Processor * Processors = new Processor[pro_n];
	std::list<Pairs<int, int>> SIGKILL;

	int RTF;
	int MaxW;

	//Memebers//

	void checkIOs();	//Check for ios in running list

	void updateIOs();	//If Process in blk list, check its progress (if blk ! empty)

	void RR_SJF_migration(); //if process in RR processor and (RT) < RTF move to SJF processor

	void FCFS_RR_migration(); //if process in FCFS and has WT>MaxW, move it to SJF

	void kill_process(); //recives kill signal AND in run or ready state AND in FCFS

	void terminate(); //CT is done (process is executed)

	void write_statistics(); //called along with terminate function, will append to file
	

public:

	Scheduler(Process* pro, int processors_num, Pairs<int,int> *kill );

	void update_();		//contains the logic of all memeber functions

	void new_ready_scheduler();		//Shortest rdy queue of all processors

	void steal_work(); //Performed every STL, moves shortest processor queue will steal from longest processor queue

};

