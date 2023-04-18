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
	DONE = false;

}

bool Scheduler::read_file(string Fname)
{
	cout << "-----------------------READING--------------------" << endl;
	string myText;
	int line = 0;
	int p_number = 0;
	int process_counter= 0;

	ifstream myFile;

	myFile.open( "../Sample/" + Fname + ".txt");

	if (myFile.fail())return false;

	while (getline(myFile, myText))
	{
		line++;

		if (line == 1) { setProcessors(myText); }

		else if (line == 2) { setRRTimeSlice(myText);  }

		else if (line == 3) { setConstants(myText);  }

		else if (line == 4) { p_number = stoi(myText); allProcesses = new Process*[p_number]; }

		else if (line >  4 + p_number) { setKillSignal(myText);  }

		else { setProcesses(myText, process_counter); process_counter++; }
		
	}
	return true;
}



void Scheduler::new_ready_scheduler(Process*& p)
{
	//for(Processor processor : Processors[pro_n])
	int min_index = 0;

	int min_num = Processors[0]->getLength();

	for (int i = 1; i < pro_n; i++) {

		if (Processors[i])
		{
			int val = Processors[i]->getLength();

			if (val < min_num) { min_num = val; min_index = i; }
		}
	}
	Processors[min_index]->Add_Process_To_RDY(p);
}




void Scheduler::checkIOs()
{
	for (int i = 0; i < pro_n; i++)
	{
		Process* p;
		if (Processors[i])
		{
			if (Processors[i]->Check_IO(p))
			{
				p->setProcessorID(-1);

				BLK.enqueue(p);
			}
		}
	
	}
}



void Scheduler::updateIOs()
{
	Process* p;
	BLK.peek(p);
	if (!(p->updateIO()))
	{
		BLK.dequeue(p);

		new_ready_scheduler(p);
	}
	return;


}


void Scheduler::steal_work()
{

}


/*Loop over HASH get process*and then pop it
If Process.RT > RTF
Move to SJF 
O(n^3)*/
void Scheduler::RR_SJF_migration()
{
	//O(n^3) change my making 4 processors lists

	// Brute force
}



void Scheduler::FCFS_RR_migration()
{
	//for (int i = 0; i < FCFS; i++)
	//{
	//	if (Processors[i]->getType() == "FCFS")
	//	{

	//		LinkedQueue<Process*> P = static_cast<FCFS_Processor*>(Processors[i])->getRDY();
	//		while (!P.isEmpty())
	//		{
	//			Process* temp;
	//			P.dequeue(temp);
	//			if (temp->getWT() > MaxW) {

	//				int min_index = 0;

	//				int min_num = Processors[SJF - 1]->Get_Time_Expected_To_Finish();

	//				for (int i = SJF; i < RR; i++) {

	//					if ((Processors[i]->getType()) == "RR")
	//					{
	//						int val = Processors[i]->Get_Time_Expected_To_Finish();

	//						if (val < min_num) { min_num = val; min_index = i; }
	//					}
	//				}
	//				Processors[min_index]->Add_Process_To_RDY(temp, time);
	//			}

	//		}
	//	}
	//}
}






void Scheduler::terminate(Process*& p)
{
	TRM.InsertEnd(p);
}

void Scheduler::kill_process()
{
	if (!SIGKILL.isEmpty()) {
		Pair<int, int> t;
		SIGKILL.peek(t);


		while (t.right == time)
		{
			SIGKILL.dequeue(t);

			try
			{
				Process* p = allProcesses[t.left];


				int id = p->getProcessorID();

				if (id != -1)
				{
					FCFS_Processor* temp = static_cast<FCFS_Processor*>(Processors[id]);

					temp->Remove_Process_From_Processor(p);

					TRM.InsertBeg(p);

					SIGKILL.peek(t);
				}
			}
			catch (exception&)
			{
				cout << " Error in Kill signal" << endl;
			}

		}
	}
}



void Scheduler::update_()
{
	time += timestep;

	// IO movments \\

	checkIOs();

	if (!BLK.isEmpty()) updateIOs();

	//	NEW to RDY movments \\

	if (!(NEW.isEmpty()))
	{
		while (NEW[0]->getAT() == time)
		{

			Process* temp = nullptr;

			NEW.DeleteFirst(temp);

			new_ready_scheduler(temp);

			if ((NEW.isEmpty())) break;

		}
	}




	//  Updating Processors		//
	for (int i = 0; i < pro_n; i++)
	{
		Processors[i]->Update();

		// Forking // 

		/* Only on FCFS*/
		//fork(Processors[i]);

		// Termination //

		Process* p;

		if (Processors[i]->Check_Running_process_If_Finished(p))
		{
			terminate(p);
		}

	}

	//  Kill signal check  \\

	kill_process();



	// Migrations //



	//Check if DONE //

	DONE = Done();
}




	////  Updating Processors		//

	//for (int i=0 ; i < pro_n ; i++)
	//{
	//	Processors[i]->Update();
	//	
	//	Process* p = Processors[i]->Check_Runnuig_process_If_Finished();

	//	if (p != nullptr) terminate(p);
	//}

	//// steal work //

	//if (time % STL == 0) steal_work();


	////		Migrations		//

	//RR_SJF_migration();

	//FCFS_RR_migration();
		





void Scheduler::setProcessors(string& myText)
{
	string var;
	string temp = myText;


	int p_num = 0;

	for (int i = 0; i < 4; i++)
	{
		var = temp.substr(0, temp.find(" "));
		temp.erase(0, var.size() + 1);
		p_num += stoi(var);
	}

	Processors = new Processor*[p_num];

	pro_n = p_num;

	int p_count=0;

	var = "";

	for (int i = 0; i < 4; i++)
	{
		var = myText.substr(0, myText.find(" "));
		myText.erase(0, var.size() + 1);


		if (i == 0) {
			FCFS = stoi(var);
			for (int i = 0; i < FCFS; i++) {
				Processors[p_count] = new FCFS_Processor(i , Fork_Probability);
				p_count++;
			}
		}

		if (i == 1) {
			SJF = std::stoi(var);
			for (int i = 0; i < SJF; i++) {
				//Processors[p_count] = new SJF_Processor;
				p_count++;
			}
		}

		if (i == 2) {
			RR = std::stoi(var);
			for (int i = 0; i < RR; i++) {
				//Processors[p_count] = new RR_Processor(0);
				p_count++;
			}
		}

		if (i == 3) {
			EDF = std::stoi(var);
			for (int i = 0; i < EDF; i++) {
				//Processors[p_count] = new EDF_Processor;
				p_count++;
			}
		}
	}
}






ostream& operator << (ostream& out, const Scheduler& Sch)
{
	out << "----------------------------- NEW ------------------------------\n";
	if (!(Sch.NEW.isEmpty()))
	{
		out << "NEW " << Sch.NEW << endl;
	}
	out << "------------------------ RDY Processes -------------------------\n";
	for (int i = 0; i < Sch.pro_n; i++)
	{
		if (Sch.Processors[i] != nullptr)
		{
			out << "PROCESSOR " << i + 1 << ": " << *(Sch.Processors[i]) << "\n";
		}
	}
	out << "------------------------ BLK Processes -------------------------\n";
	out << "BLK " << Sch.BLK << endl;
	out << "----------------------------- RUN ------------------------------\n";
	for (int i = 0; i < Sch.pro_n; i++)
	{
		if (Sch.Processors[i] != nullptr)
		{
			Process* T;
			if (Sch.Processors[i]->getRunning(T))
			{
				out << "PROCESSOR " << i + 1 << ": ID->" << *T << "\n";
			
			}
			else
			{
				out << "PROCESSOR " << i + 1 << ": EMPTY" << "\n";
			}
			
			
		}
	}
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

	SIGKILL.enqueue(KS);
}

void Scheduler::setProcesses(string &myText , int process_counter)
{
	string var = "";
	string p;
	string p2;
	int AT = 0;
	int PID = 0;
	int CT = 0;
	int N = 0;
	LinkedQueue<Pair<int, int>> IO_R_D;

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

		IO_R_D.enqueue(I);
		
	}

	Process *R = new Process(PID, AT, CT, IO_R_D);		//Question Regarding using io_r_d as linked list (not dynamically allocated)

	allProcesses[process_counter] = R;

	NEW.InsertEnd(R);
	
}

void Scheduler::setRRTimeSlice(string &myText)
{
	RRTimeSlice = stoi(myText);

	//for (int i = SJF - 1; i <= RR; i++) static_cast<RR_Processor*>(Processors[i])->setSlice(RRTimeSlice);
}



bool Scheduler::Is_Finished()
{
	return DONE;
}

bool Scheduler::Done()
{

	// Check in ALL processes done 

	return false;
}




void Scheduler::fork(Processor * & p)
{
	if (dynamic_cast<FCFS_Processor*>(p))
	{
		bool fork = static_cast<FCFS_Processor*>(p)->Fork();

		if (fork)
		{

			Process* P; 
			if (p->getRunning(P))
			{
				P =P->fork_process(time);
			} 

			new_ready_scheduler(P);
		}
	}
}


Scheduler::~Scheduler()
{
	NEW.DeleteAll();

	TRM.DeleteAll();

	BLK.~LinkedQueue();

	//for (int i = 0; i < pro_n; i++) Processors[i]->~Processor();

	delete[] Processors;

	SIGKILL.~LinkedQueue();


}

