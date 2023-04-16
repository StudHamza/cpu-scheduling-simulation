#pragma once
#include "Mode.h"
#include "../Scheduler/scheduler.h"

class UI
{
private:
	Mode MODE;
	Scheduler *cpu;
	int clock = 0;

	void setMode();
public:
	UI();

	void Start();

	void End();

	void Output();

};