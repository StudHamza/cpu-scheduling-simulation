#pragma once
#include <iostream>
#include "../Process/Process.h" 
#include "../Processors/Processor.h"
#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/SharedClasses/Pair.h"
#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/LinkedQueue.h"

#include <fstream>



class Scheduler
{
private:
	//Variables//


	int time;
	bool Is_Finish;

	LinkedList<Process*> NEW;
	LinkedQueue<Process*> BLK;
	Process* TRM;

	int pro_n;	//no of processors

	Processor** Processors;		// = new Processor * [pro_n];		//dynamic array of processors

	int time = 0;
	int RRTimeSlice;


	LinkedQueue<Pair<int, int>> SIGKILL;


	LinkedList<Process*> NEW;
	Process* TRM;
	LinkedQueue<Process*> BLK;

	Processor** Processors;
	LinkedList<Pair<int, int>> SIGKILL;


	// Constants //
	int RTF;
	int MaxW;
	int STL;

	int Fork_Probability;

	
	// Utility Functions for rad file//

	void setProcessors(string &);

	void setRRTimeSlice(string&);

	void setConstants(string&);

	void setProcesses(string&);

	void setKillSignal(string&);




	// Utility Functions //

	void setProcessors(string&);

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

	bool read_file(string name); //populates data into objects of every type, intializes all attributes

	void update_() {}		//contains the logic of all memeber functions


	void steal_work(); //Performed every STL, moves shortest processor queue will steal from longest processor queue

	bool Is_Finished() { return Is_Finish; }

	friend ostream& operator<< (ostream& out, const Scheduler& Sch);
};




