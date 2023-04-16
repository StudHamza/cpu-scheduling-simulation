#include "Scheduler.h"
#include <string>
#define timestep  1
#include "../Processors/FCFS_Processor.h"
#include "../Processors/EDF_Processor.h"
#include "../Processors/RR_Processor.h"


#define timestep 1

Scheduler::Scheduler()
{
	cout << "Creating cpu" << endl;
}

void Scheduler::read_file(std::ifstream& myFile)
{
	string myText;
	int line = 0;
	int p_number = 0;

	while (getline(myFile, myText))
	{
		line++;

		if (line == 1) { setProcessors(myText); std::cout << "Instantiating Processors" << endl; }

		else if (line == 2) { setRRTimeSlice(myText); std::cout << "RR slice time"<<endl; }

		else if (line == 3) { setConstants(myText); std::cout << "Setting constants"<<endl; }

		else if (line == 4) { p_number = stoi(myText); std::cout << "Proccesses" << endl; }

		else if (line > 4 + p_number) { setKillSignal(myText); std::cout << "Kill signal" << endl; }

		else { setProcesses(myText); }
	}



void Scheduler::new_ready_scheduler(Process* p)
{
	//for(Processor processor : Processors[pro_n])
	int min_index = 0;

	int min_num = Processors[0]->Get_Time_Expected_To_Finish();

	for (int i = 1; i < pro_n; i++) {

		int val = Processors[i]->Get_Time_Expected_To_Finish();

		if (val < min_num) { min_num = val; min_index = i; }
	}
	Processors[min_index]->Add_Process_To_RDY(p);
}



//void Scheduler::checkIOs()
//{
//	for (int i = 0; i < pro_n; i++)
//	{
//		if ((RUN[i].get_IOs()).left == time)
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
//	//O(n^2) change my making 4 processors lists
//
//	// Brute force
//
//	for (int i = RR-1; i < EDF; i++)
//	{
//		if (Processors[i]->getType() == "RR")
//		{
//			//Loop over ready queue 
//			//If Process.RT > RTF
//			//Move to SJF
//		}
//	}
//
//}







void Scheduler::update_()
{
	cout << "Updating cpu" << endl;
	//time += timestep;

	//while (NEW.front()->getAT() == time)
	//{
	//	new_ready_scheduler( NEW.front() );	//moving process of new to rdy
	//	NEW.pop_front();
	//}

	//checkIOs();		//From RUN to BLK

	//if (!BLK.empty()) updateIOs();	//From BLK to RDY

	////Updating Processors
	//for (int i=0 ; i < pro_n ; i++)
	//{
	//	Processors[i].update_();
	//	//Process from RUN to TRM list
	//	if (RUN[i].getRT() == 0) terminate(RUN[i]);
	//}

	////steal work
	//if (time % STL == 0) steal_work();

	////Kill signal chack
	//kill_process();


	////Migrations

	//RR_SJF_migration();

	//FCFS_RR_migration();
		
}




void Scheduler::setProcessors(string& myText)
{
	string var;
	int p_count=0;

	for (int i = 0; i < 4; i++)
	{
		var = myText.substr(0, myText.find(" "));
		if(i==0){
			FCFS = std::stoi(var);
			for (int i = 0; i < FCFS ; i++) {
				Processors[p_count] = new FCFS_Processor();
				cout << " FCFS Proccessors : " << i<<endl;
				p_count++;
			}
		}

		if(i==1){
			SJF = std::stoi(var);
			for (int i = 0; i < SJF; i++) {
				//Processors[p_count] = new SJF_Processor;
				cout << " SJF Proccessors : " << i << endl;
				p_count++;
			}
		}

		if(i==2){
			RR = std::stoi(var);
			for (int i = 0; i < RR; i++) {
				//Processors[p_count] = new RR_Processor(0);
				cout << " RR Proccessors : " << i << endl;
				p_count++;
			}
		}

		if(i==3){
			EDF = std::stoi(var);
			for (int i = 0; i < EDF; i++) {
				//Processors[p_count] = new EDF_Processor;
				cout << " EDF Proccessors : " << i << endl;
				p_count++;
			}
		}
}





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

void Scheduler::setConstants(string &myText)
{
	string var;
	for (int i = 1; i >=4; i--)
	{
		var = myText.substr(0, myText.find(" "));

		myText = myText.erase(0, var.size() + 1);
		if (i == 1) { RTF = stoi(var); }
		if (i == 2 ) { MaxW = stoi(var); }
		if (i == 3) { STL = stoi(var); }
		if (i == 2) { Fork_Probability = stoi(var); }

	}
}

void Scheduler::setKillSignal(string &myText)
{
	string var;

	var = myText.substr(0, myText.find(" "));

	myText = myText.erase(0, var.size() + 1);

	const Pair<int, int> KS(stoi(var), stoi(myText));

	SIGKILL.InsertEnd(KS);
}

void Scheduler::setProcesses(string &myText)
{
	string var = "";
	string p;
	string p2;
	int AT, PID, CT, N;
	LinkedList<Pair<int, int>>IO_R_D;

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

		IO_R_D.InsertBeg(I);
	}
	//Process *R = new Process(PID, AT, CT,IO_R_D );		//Question Regarding using io_r_d as linked list (not dynamically allocated)

	//NEW.InsertEnd(R);
}

void Scheduler::setRRTimeSlice(string &myText)
{
	RRTimeSlice = stoi(myText);
}


bool Scheduler::End() { return false; }


void Scheduler::Ouput(ostream&)
{
	//for (int i = 0; i < pro_n; i++)Processors[i]->Output();
}

Scheduler::~Scheduler()
{
	NEW.DeleteAll();

	TRM.DeleteAll();

	BLK.~LinkedQueue();

	//for (int i = 0; i < pro_n; i++) Processors[i]->~Processor();

	delete[] Processors;

	SIGKILL.DeleteAll();


}