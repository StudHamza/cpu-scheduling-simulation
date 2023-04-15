

#include <iostream>
using namespace std;

#include "Data_Structures/LinkedList.h"
#include "Data_Structures/Array.h"
#include "Data_Structures/LinkedQueue.h"
#include "Data_Structures/Priority_Queue.h"

int main()
{
	cout << "Hello world"<<endl;

	Priority_Queue<string> try1;

    Pair<string, int> num1("Hamza", 6);
    Pair<string, int> num2("Omar", 7);
    Pair<string, int> num3("Doctor", 22);

    Pair<string, int> num4("staff", 2);
    Pair<string, int> num5("father of doctor", 34);

    try1.enqueue(num1);
    try1.enqueue(num2);
    try1.enqueue(num3);
    try1.enqueue(num4);
    try1.enqueue(num5);

    string spare;

    try1.dequeue(spare);

    

    try1.print();

    std::cout << "Removed : " << spare << endl;;


    try1.enqueue(Pair<string, int>("wow", 222));

    try1.print();

    try1.peek(spare);

    cout << "spare is :" << spare;
}



