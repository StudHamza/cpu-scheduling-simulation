#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include "../Scheduler/scheduler.h"
#include "Mode.h"
using namespace std;


class UI
{
private:
    Mode mode;
    int time;
    Scheduler *cpu;

    void GetFileName();
    void SetMode();
    int GetCurrentTimeFromUser();
    void Print();

public:

    UI();
    void Start();
};