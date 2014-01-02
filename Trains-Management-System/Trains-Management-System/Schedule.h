#include "City.h"
#include "Train.h"
#include <time.h>
#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule
{
public:
	Schedule();
	Schedule(const City& departure, const City& arrival, const Train& train, time_t date, double price);
	Schedule(const Schedule& schedule);

	Schedule& operator=(const Schedule& schedule);
	bool operator==(Schedule& schedule);
	bool operator!=(Schedule& schedule);

	std::string ToString();

	void SetDeparture(const City& departure);
	void SetArrival(const City& arrival);
	void SetTrain(const Train& train);
	void SetDate(time_t time);
	void SetPrice(double price);

	City GetDeparture();
	City GetArrival();
	Train GetTrain();
	time_t GetDate();
	double GetPrice();

private:
	City departure;
	City arrival;
	Train train;
	time_t date;
	double price;
};

#endif