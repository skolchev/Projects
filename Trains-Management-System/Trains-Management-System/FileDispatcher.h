#include <string>
#include "City.h"
#include "Train.h"
#include "Schedule.h"
#ifndef FILEDISPATCHER_H
#define FILEDISPATCHER_H

class FileDispatcher
{
public:
	static void PrintCities(std::string fileName);
	static void PrintTrains(std::string fileName);
	static void PrintSchedule(std::string fileName);

	static void AddCity(std::string fileName, City& city);
	static void AddTrain(std::string fileName, Train& train);
	static void AddSchedule(std::string fileName, Schedule& schedule);

	static void DeleteCity(std::string fileName, City& city);
	static void DeleteTrain(std::string fileName, Train& train);
	static void DeleteSchedule(std::string fileName, Schedule& schedule);

	static void EditTrain(std::string fileName, Train& oldTrain, Train& newTrain);
	static void EditSchedule(std::string fileName, Schedule& oldSchedule, Schedule& newSchedule);

	static void DisplayFreeSeats(Schedule& schedule);
	static void DisplayAllSeats(Schedule& schedule);

	static bool ReserveSeats(int numberOfSeats, int* seats, Schedule& schedule);
	static void DisplayScheduleInformation(Schedule& schedule);
	static void DisplayScheduleBetweenCities(std::string fileName, City& departure, City& arrival);

	static void LoadTicketsFiles(std::string fileName);
	static std::string GetItem(std::string fileName, int indexOfLine);
	static Schedule ParseSchedule(std::string line);
	
private:
	static City ParseCity(std::string line);
	static Train ParseTrain(std::string line);


	static int FindCity(std::string fileName, City& city);
	static int FindTrain(std::string fileName, Train& train);
	static int FindSchedule(std::string fileName, Schedule& schedule);

	static void SaveTickets(Schedule& schedule);

	static std::string GetFileName(Schedule& schedule);


	static inline std::string& TrimLeft(std::string& str);
	static inline std::string& TrimRight(std::string& str);
	static inline std::string& TrimBoth(std::string& str);
};

#endif