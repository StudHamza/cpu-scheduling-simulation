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
	Process_Killed = 0;

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

		try
		{
			if (line == 1) { setProcessors(myText); }

			else if (line == 2) { setRRTimeSlice(myText); }

			else if (line == 3) { setConstants(myText); }

			else if (line == 4) { p_number = stoi(myText); allProcesses = new Process * [p_number]; processes_number = p_number; }

			else if (line > 4 + p_number) { setKillSignal(myText); }

			else { setProcesses(myText, process_counter); process_counter++; }
		}
		catch (const std::exception& exc)
		{
			cout << endl<<"File format is wrong "<<endl<<exc.what();
			exit(0);
		}
		
	}
	return true;
}



void Scheduler::new_ready_scheduler(Process*& p)
{
	//for(Processor processor : Processors[pro_n])
	int min_index = 0;

	int min_num = Processors[0]->getLength();

	for (int i = 1; i < pro_n; i++) {

		if (!Processors[i]->isOverHeat())
		{
			int val = Processors[i]->getLength();

			if (val < min_num) { min_num = val; min_index = i; }
		}
	}
	Processors[min_index]->Add_Process_To_RDY(p);
}




void Scheduler::Add_To_FCFS(Process*& p)
{
	int min_index = 0;

	int min_num = Processors[0]->getLength();

	for (int i = 1; i < FCFS-1; i++) {

		if (!Processors[i]->isOverHeat() && Processors[i]->getType() == "FCFS")
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
				p->setProcessorID(-2);

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



void Scheduler::RR_SJF_migration()
{
	//O(n^3) change my making 4 processors lists

	// Brute force
}



void Scheduler::FCFS_RR_migration()
{}






void Scheduler::terminate(Process*& p)
{
	if (p != nullptr)
	{


		Process* P = p->terminate(time);	//Kills orphans
		TRM.InsertEnd(p);

		//Remove child
		if (P != nullptr)
		{
			int processor_id = P->getProcessorID();

			FCFS_Processor* processor = static_cast<FCFS_Processor*>(Processors[processor_id]);

			processor->Remove_Process_From_Processor(P);
		}
		
		
		terminate(P);
		
	}
	return;
}

void Scheduler::kill_process()
{

	Pair<int, int> t;

	if (SIGKILL.peek(t))
	{
		if (t.right == time)	//left is id, right is time
		{
			SIGKILL.dequeue(t);
			Process* p = allProcesses[t.left];	//Get process
			int id = p->getProcessorID();	//get processor ID

			if (id < 0) return;

			if (Processors[id]->getType() == "FCFS")
			{
				FCFS_Processor* temp = static_cast<FCFS_Processor*>(Processors[id]);

				temp->Remove_Process_From_Processor(p);

				terminate(p);

				this->Process_Killed++;

				kill_process();
			}

		}
		return;
	}

}



void Scheduler::update_()
{
	time += timestep;


	//Check if DONE //

	DONE = Done();

	// IO movments \\

	checkIOs();

	if (!BLK.isEmpty()) updateIOs();

	//	NEW to RDY movments \\

	if (!(NEW.isEmpty()))
	{
		while (NEW[0]->getAT() == time)
		{

			Process* temp = nullptr;

			if (NEW.DeleteFirst(temp))
			{
				new_ready_scheduler(temp);
			
			}
			if ((NEW.isEmpty())) break;

		}
	}




	//  Updating Processors		//
	for (int i = 0; i < pro_n; i++)
	{
		

		// Forking // 

		/* Only on FCFS*/
		fork(Processors[i]);

		// Termination //

		Process* p;

		if (Processors[i]->Check_Running_process_If_Finished(p))
		{
			terminate(p);
		}

		Processors[i]->Update();
	}

	//  Kill signal check  \\

	kill_process();



	// Migrations //

}




		





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
				Processors[p_count] = new FCFS_Processor(p_count);
				p_count++;
			}
		}

		if (i == 1) {
			SJF = std::stoi(var);
			for (int i = 0; i < SJF; i++) {
				Processors[p_count] = new SJF_Processor(p_count);
				p_count++;
			}
		}

		if (i == 2) {
			RR = std::stoi(var);
			for (int i = 0; i < RR; i++) {
				Processors[p_count] = new RR_Processor(p_count);
				p_count++;
			}
		}

		if (i == 3) {
			EDF = std::stoi(var);
			for (int i = 0; i < EDF; i++) {
				Processors[p_count] = new EDF_Processor(p_count);
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
		if (Sch.Processors[i] != nullptr)
		{
			out << "PROCESSOR " 
				<< Sch.Processors[i]->getType()
				<<i + 1 << ": " << *(Sch.Processors[i]) << "\n";
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
				out << "PROCESSOR "<< Sch.Processors[i]->getType()
					<< i + 1 << ": ID->" << *T << "\n";
			
			}
			else
			{
				out << "PROCESSOR " 
					<< Sch.Processors[i]->getType() 
					<<i + 1 << ": EMPTY" << "\n";
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
	for(int i =1 ; i<6 ; i++){
		var = myText.substr(0, myText.find(" "));

		myText = myText.erase(0, var.size() + 1);
		if (i == 1) { RTF = stoi(var); }
		else if (i == 2 ) { MaxW = stoi(var); }
		else if (i == 3) { STL = stoi(var); }
		else if (i == 4) { Fork_Probability = stoi(var); }
		else if (i == 5) {
			int oh = stoi(var);
			for (int i = 0; i < pro_n; i++)
			{
				Processors[i]->setOverHeat(oh);
			}
		}

	}
}

void Scheduler::setKillSignal(string &myText)
{
	if (myText.size() > 0)
	{
		string var;

		var = myText.substr(0, myText.find(" "));

		myText = myText.erase(0, var.size() + 1);

		const Pair<int, int> KS(stoi(var), stoi(myText));

		SIGKILL.enqueue(KS);
	}

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
	int DL = 0;
	LinkedQueue<Pair<int, int>> IO_R_D;

	for (int i = 5; i != 0; i--)
	{
		var = myText.substr(0, myText.find(" "));

		myText = myText.erase(0, var.size() + 1);
		if (i == 5) { AT = stoi(var); }
		if (i == 4) { PID = stoi(var); }
		if (i == 3) { CT = stoi(var); }
		if (i == 2) { N = stoi(var); }
		if (i == 1) { DL = stoi(var); }
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

	Process *R = new Process(PID, AT, CT,DL, IO_R_D);		//Question Regarding using io_r_d as linked list (not dynamically allocated)

	allProcesses[process_counter] = R;

	NEW.InsertEnd(R);
	
}

void Scheduler::setRRTimeSlice(string &myText)
{
	RRTimeSlice = stoi(myText);

	for (int i = 0; i < pro_n; i++)
	{
		if (Processors[i]->getType() == "RR")
		{
			static_cast<RR_Processor*>(Processors[i])->setTimeSlice(RRTimeSlice);
		}
		
	}
}



bool Scheduler::Is_Finished()
{
	return DONE;
}

bool Scheduler::Done()
{
	
	if (TRM.GetSize() == this->processes_number) return true;

	// Check in ALL processes done  TT //

	return false;
}




void Scheduler::fork(Processor * & p)
{
	if (dynamic_cast<FCFS_Processor*>(p))
	{
		bool fork = static_cast<FCFS_Processor*>(p)->Fork(Fork_Probability);

		if (fork)
		{

			Process* P = nullptr; 
			
			if (p->getRunning(P))	// if a process is running
			{
				P =P->fork_process(time, processes_number);
			} 
			
			if (P != nullptr) // Check if it can fork
			{
				this->Process_Forked++;
				Add_To_FCFS(P);
			}
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










//    Output file    //


void Scheduler::write_statistics(string &name)
{
	ofstream outputFile("../Sample/Out_" + name + ".txt");



	outputFile << left << setw(5) << "TT";
	outputFile << left << setw(5) << "PID";
	outputFile << left << setw(5) << "AT";
	outputFile << left << setw(5) << "CT";
	outputFile << left << setw(5) << "IO_D";
	outputFile << left << setw(5) << "WT";
	outputFile << left << setw(5) << "RT";
	outputFile << left << setw(5) << "TRT" << endl;

	for (int i = 0; i < TRM.GetSize(); i++)
	{
		outputFile << left << setw(5) << TRM[i]->getTT();
		outputFile << left << setw(5) << TRM[i]->getID();
		outputFile << left << setw(5) << TRM[i]->getAT();
		outputFile << left << setw(5) << TRM[i]->getCT();
		outputFile << left << setw(5) << TRM[i]->getIODuration();
		outputFile << left << setw(5) << TRM[i]->getWT();
		outputFile << left << setw(5) << TRM[i]->getRT();
		outputFile << left << setw(5) << TRM[i]->getTRT() <<  endl;

	}

	outputFile << "Processes: " << processes_number << endl;

	double avgWT = 0;
	for (int i = 0; i < TRM.GetSize(); i++)
	{
		avgWT += TRM[i]->getWT();
	}
	avgWT = avgWT / (double)processes_number;

	outputFile << "Avg WT = " << avgWT << ", ";


	double avgRT = 0;
	for (int i = 0; i < TRM.GetSize(); i++)
	{
		avgRT += TRM[i]->getRT();
	}
	avgRT = avgRT / (double)processes_number;

	outputFile << "Avg RT = " << avgRT << ", ";


	double avgTRT = 0;
	for (int i = 0; i < TRM.GetSize(); i++)
	{
		avgTRT +=TRM[i]->getTRT();
	}
	avgTRT = avgTRT /(double) processes_number;

	outputFile << "Avg RT = " << avgTRT << endl;


	outputFile << "Forked Process: " << (Process_Forked / (double)processes_number) * 100 << "%" << endl;
	outputFile << "Killed Process: " << (Process_Killed / (double)processes_number) * 100 << "%" << endl;

	outputFile << "Processors: " << FCFS + SJF + RR + EDF << " [" << FCFS << " FCFS, " << SJF << " SJF, " << RR << " RR, " << EDF << " EDF]" << endl;
	outputFile << "Processors Load" << endl;

	double busy = 0;
	double totalTRT = 0;
	for (size_t i = 0; i < processes_number; i++)
	{
		totalTRT += TRM[i]->getTRT();
	}
	for (int i = 0; i < pro_n; i++)
	{

		busy = Processors[i]->getBusy();
		outputFile << "P" << i + 1 << "=" << (busy / (double)totalTRT)*100 << "%, ";
	}
	outputFile << endl;


	double avgUtiliz = 0;
	double util = 0;
	outputFile << "Processors Utiliz" << endl;
	for (int i = 0; i < pro_n; i++)
	{
		util = (Processors[i]->getBusy()) / (double)(Processors[i]->getBusy() + Processors[i]->getIDE()) ;
		
		util *= 100;
		avgUtiliz +=  util ;
		outputFile << "P" << i + 1 << "=" << util << "%, ";
	}
	outputFile << endl;


	outputFile << "Avg Utilization = " << avgUtiliz / (FCFS + SJF + RR + EDF) << "%";

}