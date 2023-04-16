#include "Scheduler.h"
#include <string>
#define timestep  1
#define stealLimit 40
#include "../Processors/FCFS_Processor.h"
#include "../Processors/EDF_Processor.h"
#include "../Processors/RR_Processor.h"
#include "../Processors/SJF_Processor.h"


Scheduler::Scheduler()
{
}

bool Scheduler::read_file(string Fname)
{
	cout << "-----------------------READING--------------------" << endl;
	string myText;
	int line = 0;
	int p_number = 0;

	ifstream myFile;

	myFile.open( "../Sample/" + Fname + ".txt");

	if (myFile.fail())return false;

	while (getline(myFile, myText))
	{
		line++;

		if (line == 1) { setProcessors(myText); std::cout << "Instantiating Processors....." << endl; }

		else if (line == 2) { setRRTimeSlice(myText); std::cout << "RR slice time...." << endl; }

		else if (line == 3) { setConstants(myText); std::cout << "Setting constants..." << endl; }

		else if (line == 4) { p_number = stoi(myText); std::cout << "Proccesses...." << endl; }

		else if (line > 4 + p_number) { setKillSignal(myText); std::cout << "Kill signal...." << endl; }

		else { setProcesses(myText); }
		
	}
	return true;
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
void Scheduler::updateIOs()
{
	Process* p;
	BLK.peek(p);
	//if (p->get.right == IO_counter)
	//{
	//	new_ready_scheduler(BLK.front());
	//	BLK.pop();
	//}
	//else IO_counter + 1;
}


void Scheduler::steal_work()
{
	int min_index = 0;
	int max_index = 0;

	int min_num = Processors[0]->Get_Time_Expected_To_Finish();
	int max_num = Processors[0]->Get_Time_Expected_To_Finish();

	for (int i = 1; i < pro_n; i++) {

		int val = Processors[i]->Get_Time_Expected_To_Finish();

		if (val < min_num) { min_num = val; min_index = i; }
		else if (val > max_num) { max_num = val; max_index = i; }
	}

	if (((max_num - min_num) / max_num) * 100 > (int)stealLimit)
	{
		//Process* p;
			//= (Processors[max_index]->Remove_On_Top());
		//Processors[min_index]->Add_Process_To_RDY(p);
	}

}

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



void Scheduler::terminate(Process*& p)
{
	TRM.InsertEnd(p);
}




void Scheduler::update_()
{
	time += timestep;

	if (!NEW.isEmpty())
	{
		while (NEW[0]->Is_Arrived(time))
		{
			new_ready_scheduler(NEW[0]);	//moving process of new to rdy
			NEW.DeleteFirst();
		}
	}



	//  Kill signal check  \\

	//kill_process();

	//checkIOs();		//From RUN to BLK

	//if (!BLK.isEmpty()) updateIOs();	//From BLK to RDY

	//  Updating Processors		//
	for (int i=0 ; i < pro_n ; i++)
	{
		Processors[i]->Update();
		//Process from RUN to TRM list
		Process* p = Processors[i]->Check_Runnuig_process_If_Finished();
		if (p != nullptr) terminate(p);
	}

	//steal work
	if (time % STL == 0) steal_work();


	//Migrations

	//RR_SJF_migration();

	//FCFS_RR_migration();
		
}




void Scheduler::setProcessors(string& myText)
{
	string var;
	int p_num = 0;

	var = myText.substr(0, myText.find(" "));

	p_num += stoi(var);

	var = myText.substr(0, myText.find(" "));

	p_num += stoi(var);

	var = myText.substr(0, myText.find(" "));

	p_num += stoi(var);

	Processors = new Processor*[p_num];

	pro_n = p_num;

	int p_count=0;

	for (int i = 0; i < 4; i++)
	{
		var = myText.substr(0, myText.find(" "));
		if (i == 0) {
			FCFS = stoi(var);
			for (int i = 0; i < FCFS; i++) {
				Processors[p_count] = new FCFS_Processor;
				p_count++;
			}
		}

		if (i == 1) {
			SJF = std::stoi(var);
			for (int i = 0; i < SJF; i++) {
				Processors[p_count] = new SJF_Processor;
				p_count++;
			}
		}

		if (i == 2) {
			RR = std::stoi(var);
			for (int i = 0; i < RR; i++) {
				Processors[p_count] = new RR_Processor(0);
				p_count++;
			}
		}

		if (i == 3) {
			EDF = std::stoi(var);
			for (int i = 0; i < EDF; i++) {
				Processors[p_count] = new EDF_Processor;
				p_count++;
			}
		}
	}
}





ostream& operator << (ostream& out, const Scheduler& Sch)
{
	
	out << "----------------------------- NEW ------------------------------\n";
	out << "NEW " << Sch.NEW << endl;
	out << "------------------------ RDY Processes -------------------------\n";
	for (int i = 0; i < Sch.pro_n; i++)
	{
		out << Sch.Processors[i] << "\n";

	}
	out << "------------------------ BLK Processes -------------------------\n";
	out << "BLK " << Sch.BLK << endl;
	out << "----------------------------- RUN ------------------------------\n";
	out << "RUN "<<endl;
	out << "----------------------------- TRM ------------------------------\n";
	out << "TRM : " << Sch.TRM << endl;//<< Sch.TRM; 


	return out;
}

void Scheduler::setConstants(string &myText)
{
	string var;
	for(int i =1 ; i<=4 ; i++){
		var = myText.substr(0, myText.find(" "));

		myText = myText.erase(0, var.size() + 1);
		if (i == 1) { RTF = stoi(var); }
		if (i == 2 ) { MaxW = stoi(var); }
		if (i == 3) { STL = stoi(var); }
		if (i == 4) { Fork_Probability = stoi(var); }

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
	LinkedList<Pair<int, int>>*IO_R_D = new LinkedList<Pair<int, int>>;

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

		IO_R_D->InsertEnd(I);
	}
	Process *R = new Process(PID, AT, CT,IO_R_D );		//Question Regarding using io_r_d as linked list (not dynamically allocated)

	NEW.InsertEnd(R);
}

void Scheduler::setRRTimeSlice(string &myText)
{
	RRTimeSlice = stoi(myText);

	for (int i = SJF - 1; i <= RR; i++) static_cast<RR_Processor*>(Processors[i])->setSlice(RRTimeSlice);
}



bool Scheduler::Is_Finished()
{
	return 0;
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


