#include <string>
#include "Train.h"
#include "Schedule.h"
#include "City.h"
#include "FileDispatcher.h"
#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
	Engine(std::string fileCities, std::string fileTrains, std::string fileSchedule);

	void Run();

private:
	std::string fileCities;
	std::string fileTrains;
	std::string fileSchedule;

	Schedule EnterScheduleData();
	Train EnterTrainData();
};

#endif ENGINE_H