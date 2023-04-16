#include "UI.h"




UI::UI()
{
	cpu = new Scheduler;
}

void UI::Start()
{
	std::cout << "Current Time: " << clock << endl;

	setMode();

	std::ifstream myFile;
	myFile.open("myFile.txt");
	
	cout << "Loading file: " << endl;

	if (myFile.is_open())cpu->read_file(myFile);

	myFile.close();

	/* Depending on the mode we will update the clock*/
	while (!cpu->End())
	{
		cout << "Clock : " << clock++ << endl;
		if (MODE = INTERACTIVE)
		{
			cin.get();
		}
		if (MODE = STEP) Sleep(1);
		if (MODE = SILENT);
		
		cpu->update_();
	}
}

void UI::End()
{
}

void UI::setMode()
{
	int mode = 0;

	std::cout << "Please choose a mode:" << endl
		<< "Interactive -> 1" << endl
		<< " Step by Step -> 2" << endl
		<< " Silent -> 3" << endl;

	std::cin >> mode;

	switch (mode) {
	case INTERACTIVE:
		cout << "Interactive mode"<<endl;
		MODE = INTERACTIVE;
		break;
	case STEP:
		std::cout << "STEP mode"<<endl;
		MODE = STEP;
		break;
	case SILENT:
		std::cout << "Silent mode"<<endl;
		MODE = SILENT;
		break;
	};
}

void UI::Output()
{
	//Logs info into cmd
}