#ifndef LIB2
#define LIB2


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>


using namespace std;

class Event
{
protected:
	std::string about_event = "";
	std::string type_event = "event";
	std::string time = "";
	std::string date = "";
	std::string priority = "";


public:
	void SetAbout(std::string val);
	std::string GetAbout();


	void SetTimet(std::string val);
	std::string GetTime();


	void SetTypeEvent(std::string val);
	std::string GetTypeEvent();


	void SetDate(std::string val);
	std::string GetDate();


	void SetPriority(std::string val);
	std::string GetPriority();


	virtual void EnterEvent()
	{
		cout << "Enter type event: ";
		cin >> type_event;


		cout << "Enter about event: ";
		cin >> about_event;


		cout << "Enter time event: ";
		cin >> time;


		cout << "Enter date event: ";
		cin >> date;


		cout << "Enter priority event: ";
		cin >> priority;


		cout << endl;
	}


	virtual void PrintEvent()
	{
		if (type_event != "") cout << "Type: " << type_event <<"\n\n";
		if (about_event != "") cout << "About: "<< about_event << "\n\n";
		if (time != "") cout << "Time: " << time << "\n";
		if (date != "") cout << "Date: " << date << "\n";
		if (priority != "") cout << "Priority: " << priority << "\n";


	}
};


class Notification : public Event
{
public:


	Notification() { type_event = "Notification"; }


	void EnterEvent();
};


class Warning : public Event
{
public:


	Warning() { type_event = "Warning"; }


	void EnterEvent();

};


class Error : public Event
{
public:


	Error() { type_event = "Error"; }


	void EnterEvent();
};


#endif