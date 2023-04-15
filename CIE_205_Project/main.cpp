

#include <iostream>


#include "Scheduler/scheduler.h"
#include "UI/UI.h"

int main()
{
	std::cout << "Hello world" << endl;

	UI interface;

	// START PROGRAM //
	interface.Start();

	// END PROGRAM	//

	interface.End();	/*Genrates Output files and deallocates objects*/

}

/*
	// Creating program objects //
	Scheduler cpu;


	// LOADING DATA //

	std::ifstream load;

	cpu.read_file(load);

*/

