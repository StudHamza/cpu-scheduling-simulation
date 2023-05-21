#pragma once
#include <iostream>
#include "../Data_Structures/SharedClasses/Pair.h"
#include "../Data_Structures/LinkedQueue.h"


class Process
{
	// Constants //

	int PID;

	int ProcessorID;

	int Arrival_Time;

	int CPU_Time;

	int DeadLine;
	

	// Variables //

	int IOCounter;

	int Remaining_Time;

	int Executing_Time;


	int Termination_Time;
	int Response_Time;
	int Turn_Around_Time;
	int Waiting_Time;

	LinkedQueue<Pair<int,int>> IO_pairs;

	bool executing;
	bool done;
	Process* Child;


public:

	//  Operator //
	friend std::ostream& operator << (std::ostream & ,const Process &);



	// Constructor //

	Process(int, int, int,int, LinkedQueue<Pair<int, int>> );


	// Getters //
	int getID() const;

	int getAT()const;	//Arrival time

	int getRT() const; //Remaining Time if==0 process is done

	int getWT() const;  //Waiting time

	bool checkIO() const;	//Gets recent IO 

	int getCT() const;  //returns cpu time

	int getProcessorID() const;

	int getDeadLine() const;

	bool isDone() const;

	// Setters //

	void setTRT();

	void setTT(int);  //Termination time

	void setExecuting( bool);

	void setResponseT(  int clock); // Response time

	void setProcessorID( int);

	

	// Updaters

	bool popIO();

	bool updateIO();	//pops from pair and handels the counter

	Process* fork_process(const int &, int&);

	void updateWT();		//updates waiting time

	void update_();

	Process* terminate(const int&);

	///////////////////////////////////////////////////////////////////////////////////////////


	~Process();

};


inline std::ostream& operator << (std::ostream& out, const Process& P)
{
	out << P.PID;
	return out;
}