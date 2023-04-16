#include "Scheduler.h"
#include <string>
#define timestep  1
#include "../Processors/FCFS_Processor.h"
#include "../Processors/EDF_Processor.h"
#include "../Processors/RR_Processor.h"
#include "../Processors/SJF_Processor.h"

Scheduler::Scheduler()
{
	time = 0;
	Is_Finish = false;
}


// UTILITY FUNCTIONS for read file//
void Scheduler::setProcessors(string& mytext)
{
	int line_values[5];

	for (int i = 0; i < 5; i++)
	{
		string var = mytext.substr(0, mytext.find(" "));
		mytext = mytext.erase(0, var.size() + 1);
		line_values[i] = stoi(var);
	}

	int sum = line_values[0] + line_values[1] + line_values[2] + line_values[3];
	Processors = new Processor * [sum];

	string var;
	int p_count = 0;
	for (int i = 4; i != 0; i--)
	{
		if (i == 4) {
			for (int i = 0; i < line_values[0]; i++) {
				Processors[p_count] = new FCFS_Processor;
				p_count++;
			}
		}
		if (i == 3) {
			for (int i = 0; i < line_values[1]; i++) {
				Processors[p_count] = new SJF_Processor;
				p_count++;
			}
		}
		if (i == 2) {
			for (int i = 0; i < line_values[2]; i++) {
				Processors[p_count] = new RR_Processor(line_values[4]);
				p_count++;
			}
		}
		if (i == 1) {
			for (int i = 0; i < line_values[3]; i++) {
				Processors[p_count] = new EDF_Processor();
				p_count++;
			}
		}
	}
}

void Scheduler::setConstants(string& mytext)
{
	int line_values[4];

	for (int i = 0; i < 4; i++)
	{
		string var = mytext.substr(0, mytext.find(" "));
		mytext = mytext.erase(0, var.size() + 1);
		line_values[i] = stoi(var);
	}

	RTF = line_values[0];
	MaxW = line_values[1];
	STL = line_values[2];
	Fork_Probability = line_values[3];
}

void Scheduler::setProcesses(string& myText)
{
	string var = "";
	string p;
	string p2;
	int AT, PID, CT, N;
	LinkedList<Pair<int, int>>* IO_R_D = new LinkedList<Pair<int, int>>;

	for (int i = 4; i != 0; i--)
	{
		var = myText.substr(0, myText.find(" "));

		myText = myText.erase(0, var.size() + 1);
		if (i == 4) { AT = stoi(var); }
		if (i == 3) { PID = stoi(var); }
		if (i == 2) { CT = stoi(var); }
		if (i == 1) { N = stoi(var); }
	}
	while (myText.size())
	{
		var = myText.substr(1, myText.find(")") - 1);
		myText = myText.erase(0, var.size() + 3);
		p = var.substr(0, var.find(","));

		p2 = var.substr(p.size() + 1, var.size());

		Pair<int, int> I(stoi(p), stoi(p2));

		(*IO_R_D).InsertBeg(I);
	}
	Process* R = new Process(PID, AT, CT, IO_R_D);		//Question Regarding using io_r_d as linked list (not dynamically allocated)

	NEW.InsertEnd(R);
}

void Scheduler::setKillSignal(string& myText)
{
	string var;

	var = myText.substr(0, myText.find(" "));

	myText = myText.erase(0, var.size() + 1);

	const Pair<int, int> KS(stoi(var), stoi(myText));

	//SIGKILL.InsertEnd(KS);
}

bool Scheduler::read_file(string name)
{
	ifstream load;
	load.open("input.txt");
	if (load.fail())
	{
		return false;
	}

	string myText;

	string var;
	getline(load, myText);
	var = myText;
	getline(load, myText);
	var += " ";
	var += myText;
	setProcessors(var);


	getline(load, myText);
	setConstants(myText);

	getline(load, myText);
	int processes = stoi(myText);
	

	for (int i = 0; i < processes; i++)
	{
		getline(load, myText);
		setProcesses(myText);
	}

	while (getline(load, myText))
	{
		setKillSignal(myText);
	}

	load.close();
	return true;
}





void Scheduler::new_ready_scheduler(Process* p)
{

	int min_index = 0;

	int min_num = (Processors[0])->Get_Time_Expected_To_Finish();

	for (int i = 0; i < pro_n; i++) {

		int val = (Processors[i]->Get_Time_Expected_To_Finish());

		if (val < min_num) { min_num = val; min_index = i; }
	}
	Processors[min_index]->Add_Process_To_RDY(p);
}



void Scheduler::checkIOs()
{
	for (int i = 0; i < pro_n; i++)
	{
		Process* p = Processors[i]->Check_IO(time);
		if (p)
		{
			BLK.enqueue(p);
			//move to blk list
		}	
	}
}


//void Scheduler::updateIOs()
//{
//	if (BLK.front()->get_IOs().right == IO_counter)
//	{
//		new_ready_scheduler(BLK.front());
//		BLK.pop();
//	}
//	else IO_counter + 1;
//}


//void Scheduler::RR_SJF_migration()
//{
//	//O(n^2)
//	for (int i = 0; i < pro_n; i++)
//	{
//
//	}
//
//}






 
 

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







ostream& operator << (ostream& out, const Scheduler& Sch)
{
	out << "iam here";
	/*out << "------------------------ RDY Processes -------------------------\n";
	for (int i = 0; i < Sch.pro_n; i++)
	{
		out << Sch.Processors[i] << "\n";
	}
	out << "------------------------ BLK Processes -------------------------\n";
*/





	return out;
}