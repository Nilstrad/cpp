#include "lib5.h"

using namespace std;

int main(){

char logo[] =
"**********************************************\n"
"* Nizhniy Novgorod Technical University      *\n"
"* Study work number 2 Task number 1          *\n"
"* Performed student 22-IVT-3 Artamonov Nikita*\n"
"**********************************************\n";

cout << logo;

int mode;
	int How_many_event;


	Event* events[10];


	while (true)
	{
		cout  << "1 - A notification\n"
		      << "2 - Warning\n"
			  << "3 - Error\n"
			  << "Select mode event: ";


		cin >> mode;
		
		if ((mode > 3) && (mode < 1)) { cout << "No correct mode. Try again!\n"; }
		else break;
	}


	cout << "How many event you want write: ";
	cin >> How_many_event;
	cout << '\n';


	switch (mode)
	{
		case 1:
		{
			for (int i = 0; i < How_many_event; i++)
			{
				events[i] = new Notification;
				events[i]->EnterEvent();
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < How_many_event; i++)
			{
				events[i] = new Warning;
				events[i]->EnterEvent();
			}
			break;
		}
		case 3:
		{
			for (int i = 0; i < How_many_event; i++)
			{
				events[i] = new Error;
				events[i]->EnterEvent();
			}
			break;
		}
		
	}
	cout << endl << endl << endl << endl;


	for (int i = 0; i < How_many_event; i++) 
	{
		events[i]->PrintEvent(); 
		cout << endl << endl << endl << endl;
	}


	return 0;
}
