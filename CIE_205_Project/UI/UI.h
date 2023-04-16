#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include "../Scheduler/scheduler.h"
using namespace std;

enum mode
{
	INTERACTIVE = 1,
	STEP_BY_STEP = 2,
	SILENT = 3
};

class UI
{
private:
	mode mode;
    int time;
    Scheduler scheduler;

    void GetFileName();
    void SetMode();
    int GetCurrentTimeFromUser();
    void Print();

public:

    UI();
    void Start();
};
