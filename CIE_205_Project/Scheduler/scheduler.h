#pragma once
#include <iostream>
#include "../Process/Process.h" 
#include "../Processors/Processor.h"
#include "../Data_Structures/SharedClasses/Pair.h"
#include "../Data_Structures/LinkedList.h"
#include "../Data_Structures/LinkedQueue.h"


#include <queue>
#include <list>
#include <fstream>



class Scheduler
{
private:
	//Variables//

	int pro_n;	//no of processors
	int time = 0;
	int RRTimeSlice;


	int FCFS;
	int SJF;
	int RR;
	int EDF;

	LinkedList<Process*> NEW;
	LinkedList<Process*> TRM;
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

	bool End();

	void Ouput(ostream&);

	~Scheduler();


};

