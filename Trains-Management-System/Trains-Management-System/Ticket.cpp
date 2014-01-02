#include "Ticket.h"
#include <time.h>
#include <sstream>

Ticket::Ticket()
{
	this->SetReserved(false);
	this->SetSold(0);
	this->SetPrice(0);
}

Ticket::Ticket(bool isReserved, time_t soldOn, double price)
{
	this->SetReserved(isReserved);
	this->SetSold(soldOn);
	this->SetPrice(price);
}

std::string Ticket::ToString()
{
	std::string result;

	std::ostringstream oss;
	oss << this->Price();

	if (this->IsReserved() == true)
	{
		result += "Reserved ";
		tm* ptr = gmtime(&soldOn);
		 ptr->tm_hour += 3;
		result += asctime(ptr);
		int length = result.length();
		result[length - 1] = ' ';
	}
	else
	{
		result += "Not reserved ";
	}

	result += oss.str();

	return result;
}

void Ticket::SetReserved(bool isReserved)
{
	this->isReserved = isReserved;
}

void Ticket::SetSold(time_t soldOn)
{
	this->soldOn = soldOn;
}

void Ticket::SetPrice(double price)
{
	this->price = price;
}

bool Ticket::IsReserved()
{
	return this->isReserved;
}

time_t Ticket::SoldOn()
{
	return this->soldOn;
}

double Ticket::Price()
{
	return this->price;
}