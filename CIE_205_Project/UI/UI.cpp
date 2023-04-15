#include "UI.h"

UI::UI()
{

}

void UI::Start()
{
	std::cout << "Current Time: " << clock;

	std::ifstream myFile;
	cpu.read_file(myFile);

	/* Depending on the mode we will update the clock*/

	cpu.update_();

}

void UI::End()
{}