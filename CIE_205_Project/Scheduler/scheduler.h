#pragma once
#include <iostream>
#include "../Process/Process.h" 
#include "../Processors/Processor.h"
#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/SharedClasses/Pair.h"

#include <fstream>



class Scheduler
{
private:
	//Variables//

	int pro_n;	//no of processors
	int time = 0;


	LinkedList<Process*> NEW;
	Process* TRM;
	LinkedQueue<Process*> BLK;
	Processor** Processors;		// = new Processor * [pro_n];		//dynamic array of processors
	LinkedQueue<Pair<int, int>> SIGKILL;


	// Constants //
	int RR_TimeSlice;
	int RTF;
	int MaxW;
	int STL;


	// Utility Functions //

	void setProcessors(string&);

	void setRRTimeSlice(string &);

	void setConstants(string &);

	void setProcesses(string &);

	void setKillSignal(string &);


	//Memebers//

	void checkIOs();	//Check for ios in running list

	void updateIOs();	//If Process in blk list, check its progress (if blk ! empty)

	void new_ready_scheduler(Process*);		//Shortest rdy queue of all processors

	void RR_SJF_migration(); //if process in RR processor and (RT) < RTF move to SJF processor

	void FCFS_RR_migration(); //if process in FCFS and has WT>MaxW, move it to SJF

	void kill_process(); // kill signal AND in run or ready state AND in FCFS

	void terminate(Process&); //CT is done (process is executed)

	void write_statistics(); //called along with terminate function, will append to file

	

public:

	Scheduler();

	void read_file(std::ifstream&); //populates data into objects of every type, intializes all attributes

	void update_();		//contains the logic of all memeber functions


	void steal_work(); //Performed every STL, moves shortest processor queue will steal from longest processor queue


};

