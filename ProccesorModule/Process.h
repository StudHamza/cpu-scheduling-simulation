#pragma once
#include "Pair.h"

class Process
{
	int AT;
	int RT;
public:
	int getAT();
	int getRT();
	Pairs<int,int> get_IOs();
};

