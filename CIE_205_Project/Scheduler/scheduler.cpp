#include "Scheduler.h"
#include <string>
#define timestep  1
#include "../Processors/FCFS_Processor.h"
#include "../Processors/EDF_Processor.h"
#include "../Processors/RR_Processor.h"
#include "../Processors/SJF_Processor.h"

Scheduler::Scheduler()
{}

void Scheduler::read_file(std::ifstream& load)
{

	load.open("Name.txt");

	std::string myText;

	int line = 0;
	int processes = 0;

	while (getline(load, myText))
	{
		line++;
		if (line == 1) { setProcessors(myText); }

		else if (line == 2) { setRRTimeSlice(myText); }

		else if (line == 3) { setConstants(myText); }

		else if (line == 4) { processes = stoi(myText); }

		else if(line> 4+processes){}

		else { setProcesses(myText); }
	}

	load.close();
}


void Scheduler::new_ready_scheduler(Process* p)
{

	int min_index = 0;

	int min_num = (Processors[0])->getLength();

	for (int i = 0; i < pro_n; i++) {

		int val = (Processors[i]->getLength());

		if (val < min_num) { min_num = val; min_index = i; }
	}
	Processors[min_index]->Add_Process_To_RDY(p);
}



//void Scheduler::checkIOs()
//{
//	for (int i = 0; i < pro_n; i++)
//	{
//		if ((Processors[i]->
//		{
//			//move to blk list
//			
//		}
//		
//	}
//}
//
//void Scheduler::updateIOs()
//{
//	if (BLK.front()->get_IOs().right == IO_counter)
//	{
//		new_ready_scheduler(BLK.front());
//		BLK.pop();
//	}
//	else IO_counter + 1;
//}
//
//
//void Scheduler::RR_SJF_migration()
//{
//	//O(n^2)
//	for (int i = 0; i < pro_n; i++)
//	{
//
//	}
//
//}
//
//
//
//
//
//
//void Scheduler::update_()
//{
//	time += timestep;
//
//	while (NEW.front()->getAT() == time)
//	{
//		new_ready_scheduler( NEW.front() );	//moving process of new to rdy
//		NEW.pop_front();
//	}
//
//	checkIOs();		//From RUN to BLK
//
//	if (!BLK.empty()) updateIOs();	//From BLK to RDY
//
//	//Updating Processors
//	for (int i=0 ; i < pro_n ; i++)
//	{
//		Processors[i].update_();
//		//Process from RUN to TRM list
//		if (RUN[i].getRT() == 0) terminate(RUN[i]);
//	}
//
//	//steal work
//	if (time % STL == 0) steal_work();
//
//	//Kill signal chack
//	kill_process();
//
//
//	//Migrations
//
//	RR_SJF_migration();
//
//	FCFS_RR_migration();
//		
//}





// UTILITY FUNCTIONS for read file//

void Scheduler::setProcessors(string &mytext)
{
	//string var;

	//int p_count = 0;

	//for (int i = 4; i != 0; i--)
	//{
	//	var = mytext.substr(0, mytext.find(" "));

	//	mytext = mytext.erase(0, var.size() + 1);
	//	
	//	int n = stoi(var);

	//	if(i==4){
	//		for (int i = 0; i < n; i++) {
	//			Processors[p_count] = new FCFS_Processor;
	//			p_count++;
	//		}
	//	}
	//	if(i==3){
	//		for (int i = 0; i < n; i++) {
	//			Processors[p_count] = new SJF_Processor;
	//			p_count++;
	//		}
	//	}
	//	if(i==2){
	//		for (int i = 0; i < n; i++) {
	//			Processors[p_count] = new RR_Processor(0);
	//			p_count++;
	//		}
	//	}
	//	if(i==1){
	//		for (int i = 0; i < n; i++) {
	//			//Processors[p_count] = new EDF_Processor();
	//			p_count++;
	//		}
	//	}

	//	i--;
	//}
}

void Scheduler::setRRTimeSlice(string &mytext)
{}

void Scheduler::setConstants(string& mytext)
{}

void Scheduler::setProcesses(string & mytext)
{}

void Scheduler::setKillSignal(string& mytext)
{}