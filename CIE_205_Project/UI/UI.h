#pragma once

#include "Mode.h"
#include "../Scheduler/scheduler.h"
#include <iostream>

#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif



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


//              mode mode;
// int time;
// Scheduler scheduler;

// // void GetFileName();
// // void SetMode();
// // int GetCurrentTimeFromUser();
// // void Print();

// public:
// UI();
// void Start();
// }
// ;
