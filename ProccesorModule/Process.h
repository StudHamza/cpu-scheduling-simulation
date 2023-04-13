#pragma once
#include "../Pair.h"


class Process
{
	int AT;
	int RT;
	Pairs<int,int> O;

public:
	int getAT() { return 0; }
	int getRT() { return 0; }
	int getWT() { return 0; }
	Pairs<int, int> get_IOs() { return O; };
};

