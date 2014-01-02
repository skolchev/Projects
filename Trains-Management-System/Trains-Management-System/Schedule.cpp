#include "Schedule.h"
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;

// Constructors
Schedule::Schedule()
{
}

Schedule::Schedule(const City& departure, const City& arrival, const Train& train, time_t date, double price)
{
	this->SetDeparture(departure);
	this->SetArrival(arrival);
	this->SetTrain(train);
	this->SetDate(date);
	this->SetPrice(price);
}

Schedule::Schedule(const Schedule& schedule)
{
	this->SetDeparture(schedule.departure);
	this->SetArrival(schedule.arrival);
	this->SetTrain(schedule.train);
	this->SetDate(schedule.date);
	this->SetPrice(schedule.price);
}

Schedule& Schedule::operator=(const Schedule& schedule)
{	
	this->SetDeparture(schedule.departure);
	this->SetArrival(schedule.arrival);
	this->SetTrain(schedule.train);
	this->SetDate(schedule.date);
	this->SetPrice(schedule.price);

	return *this;
}

// Methods
std::string Schedule::ToString()
{
	std::string result;

	result = this->GetDeparture().ToString();
	result += " -> ";
	result += this->GetArrival().ToString();
	result += ", ";
	
	tm* date = gmtime(&this->date);
	char day[3];
	char month[3];
	char year[5];
	int currentMonth = date->tm_mon + 1;
	int currentYear = date->tm_year + 1900;
	itoa(date->tm_mday, day, 10);
	itoa(currentMonth, month, 10);
	itoa(currentYear, year, 10);
	result += day;
	result += ".";
	result += month;
	result += ".";
	result += year;
	result += ", ";

	char hour[3];
	char minutes[3];
	int currentHour = date->tm_hour + 2;
	itoa(currentHour, hour, 10);
	itoa(date->tm_min, minutes, 10);
	result += hour;
	result += ":";
	result += minutes;
	result += ", ";

	result += this->GetTrain().GetID();
	result += ", ";

	std::ostringstream oss;
	oss << this->GetPrice();
	result += oss.str();

	return result;
}

bool Schedule::operator==(Schedule& schedule)
{
	if (this->GetDeparture().ToString() == schedule.GetDeparture().ToString() &&
		this->GetArrival().ToString() == schedule.GetArrival().ToString() &&
		this->GetTrain().GetID() == schedule.GetTrain().GetID() &&
		this->GetDate() == schedule.GetDate())
	{
		return true;
	}

	return false;
}

bool Schedule::operator!=(Schedule& schedule)
{
	if (this->GetDeparture().ToString() == schedule.GetDeparture().ToString() &&
		this->GetArrival().ToString() == schedule.GetArrival().ToString() &&
		this->GetTrain().GetID() == schedule.GetTrain().GetID() &&
		this->GetDate() == schedule.GetDate())
	{
		return false;
	}

	return true;
}

// Setters
void Schedule::SetDeparture(const City& departure)
{
	this->departure = departure;
}

void Schedule::SetArrival(const City& arrival)
{
	this->arrival = arrival;
}

void Schedule::SetTrain(const Train& train)
{
	this->train = train;
}

void Schedule::SetDate(time_t date)
{
	this->date = date;
}

void Schedule::SetPrice(double price)
{
	this->price = price;
}

// Getters
City Schedule::GetDeparture()
{
	return this->departure;
}

City Schedule::GetArrival()
{
	return this->arrival;
}

Train Schedule::GetTrain()
{
	return this->train;
}

time_t Schedule::GetDate()
{
	return this->date;
}

double Schedule::GetPrice()
{
	return this->price;
}