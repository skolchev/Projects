#include <time.h>
#include <string>
#ifndef TICKET_H
#define TICKET_H

struct Ticket
{
public:
	Ticket();
	Ticket(bool isReserved, time_t soldOn, double price);

	std::string ToString();

	void SetReserved(bool isReserved);
	void SetSold(time_t soldOn);
	void SetPrice(double price);

	bool IsReserved();
	time_t SoldOn();
	double Price();

private:
	bool isReserved;
	time_t soldOn;
	double price;
};

#endif