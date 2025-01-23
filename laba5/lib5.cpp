#include "lib5.h"

void Event::SetAbout(std::string val) { about_event = val; }
std::string Event::GetAbout() { return about_event; }

void Event::SetTimet(std::string val) { time = val; }
std::string Event::GetTime() { return time; }

void Event::SetTypeEvent(std::string val) { type_event = val; }
std::string Event::GetTypeEvent() { return type_event; }

void Event::SetDate(std::string val) { date = val; }
std::string Event::GetDate() { return date; }


void Event::SetPriority(std::string val) { priority = val; }
std::string Event::GetPriority() { return priority; }

	

    void Notification::EnterEvent()
	{
		std::cin.ignore(32767, '\n');


		cout << "Enter about event: ";
		std::getline(std::cin, about_event);
		
		cout << "Enter time event: ";
		std::getline(std::cin, time);
		
		cout << "Enter date event: ";
		std::getline(std::cin, date);
		
		cout << "Enter priority event: ";
		std::getline(std::cin, priority);
		
		cout << endl;

	}

void Warning::EnterEvent()
	{
		std::cin.ignore(32767, '\n');


		cout << "Enter about event: ";
		std::getline(std::cin, about_event);
		
		cout << "Enter time event: ";
		std::getline(std::cin, time);
		
		cout << "Enter date event: ";
		std::getline(std::cin, date);
		
		cout << "Enter priority event: ";
		std::getline(std::cin, priority);
		
		cout << endl;


	}

void Error::EnterEvent()
	{
		std::cin.ignore(32767, '\n');


		cout << "Enter about event: ";
		std::getline(std::cin, about_event);
		
		cout << "Enter time event: ";
		std::getline(std::cin, time);
		
		cout << "Enter date event: ";
		std::getline(std::cin, date);
		
		cout << "Enter priority event: ";
		std::getline(std::cin, priority);
		
		cout << endl;
	


	}





