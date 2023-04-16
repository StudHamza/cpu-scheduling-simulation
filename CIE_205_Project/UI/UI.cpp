#include "UI.h"



UI::UI()
{
    time = 0;
    cpu = new Scheduler;
}


void UI::GetFileName()
{
    string name;
    cout << "Enter Your Input File Name: ";
    cin >> name;
    while (true)
    {
        if (cpu->read_file(name))
        {
            return;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid File Name, Please Enter A Valid File Name: ";
        cin >> name;
    }
}


void UI::SetMode()
{
    int m;
    bool valid_input = false;
    cout << "Enter the number of mode you want the program to start with" << endl;
    cout << "1. INTERACTIVE\n" << "2.STEP BY STEP\n" << "3.SILENT\n";
    cout << "Enter your choice number: ";
    while (!valid_input)
    {
        try
        {
            cin >> m;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input");
            }
            switch (m)
            {
            case 1: {mode = INTERACTIVE; cout << "Interactive" << "....simulation starts"<<endl;
                valid_input = true; break; }
            case 2: {mode = STEP; cout << "Step" << "....simulation starts"<<endl;
                valid_input = true; break; }
            case 3: {mode = SILENT; cout << "Silent" << "....simulation starts"<<endl;
                valid_input = true; break; }
            default: throw invalid_argument("Invalid input");
            }
        }
        catch (const exception& e)
        {
            cout << e.what() << " Please Enter A Valid Value From (1 , 2 , 3): ";
        }
    }
}



int UI::GetCurrentTimeFromUser()
{
    int m;
    bool valid_input = false;
    cout << "Enter Current Time: ";
    while (!valid_input)
    {
        try
        {
            cin >> m;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw invalid_argument("Invalid input");
            }
            if (m <= time)
            {
                throw invalid_argument("Invalid time");
            }
            valid_input = true;
        }
        catch (const exception& e)
        {
            cout << e.what() << ". Please Enter A Valid Value (Integer): ";
        }
    }
    return m;
}


void UI::Print()
{
    if (mode == SILENT) return;
    cout << "####################################################################################\n";
    cout << "Current Time Step: " << time <<endl;
    cout << "//////////////////////////////  Processors  ////////////////////////////////"<<endl;
    cout << *cpu;
}


void UI::Start()
{
    SetMode();

    GetFileName();
    
    while (!(cpu->Is_Finished()))
    {

        
        if (mode == INTERACTIVE)
        {
            cout << "PRESS ANY KEY TO COUNTINUE";
            cin.get();
        }
        else if (mode == STEP)
        {
            chrono::seconds sec(1);
            this_thread::sleep_for(sec);
        }
        else if (mode == SILENT){}

        Print(); 

        cpu->update_();
        
        time++;
    }
    cout << "Simulation Ends, Output file created";

}