#pragma once
#include <string>
#include "Process.h"
class Processor
{
	Process *p;
public:
	void update_() {};
	int getLenght() { return 0; }
	void addToRDY(Process*) {}

	std::string getType() { return ""; };

	Process* FindProcess(int) { return p ; }

	//sdeque<Process*> getRdylist() {};

	
};

