#include "Engine.h"
#include "City.h"
#include "Train.h"
#include "Schedule.h"
#include "FileDispatcher.h"
#include "Ticket.h"
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

Engine::Engine(std::string fileCities, std::string fileTrains, std::string fileSchedule)
{
	this->fileCities = fileCities;
	this->fileTrains = fileTrains;
	this->fileSchedule = fileSchedule;
}

void Engine::Run()
{
	FileDispatcher::LoadTicketsFiles(fileSchedule);

	cout << "========================================" << endl;
	cout << "		MAIN MENU" << endl;
	cout << "========================================" << endl;
	cout << endl;
	cout << "1. Manage cities" << endl;
	cout << "2. Manage trains" << endl;
	cout << "3. Manage schedule" << endl;
	cout << "4. Sale tickets" << endl;

	std::string choice;
	int option = 0;
	int innerOption = 0;

	
	do
	{
		cout << "Please choose a option from the main menu or type 'exit' to escape: ";
		cin >> choice;	
		
		if (choice != "exit")
		{
			option = atoi(choice.c_str());
			if (option < 1 && option > 4)
			{
				cout << "Invalid option!" << endl;
				cout << "Try again: ";
				cin >> choice;
			}
			else
			{
				switch (option)
				{
				case 1:
					cout << "1. Display cities" << endl;
					cout << "2. Add city" << endl;
					cout << "3. Delete city" << endl;
					cout << endl << "Choose a option from sub menu: ";
					cin >> innerOption;

					if (innerOption == 1)
					{
						FileDispatcher::PrintCities(fileCities);
					}
					else if (innerOption == 2)
					{
						cin.get();
						std::string cityToAdd;
						cout << "Enter city to add: ";
						std::getline(std::cin, cityToAdd);
						City city(cityToAdd);
						FileDispatcher::AddCity(fileCities, city);
					}
					else if (innerOption == 3)
					{
						cin.get();
						std::string cityToDelete;
						cout << "Enter city to delete: ";
						std::getline(cin, cityToDelete);
						City city(cityToDelete);
						FileDispatcher::DeleteCity(fileCities, city);
					}
					else
					{
						cout << "Invalid command" << endl;
					}

					break;

				case 2:
					cout << "1. Display trains" << endl;
					cout << "2. Add train" << endl;
					cout << "3. Delete train" << endl;
					cout << "4. Edit train" << endl;
					cout << endl << "Choose a option from sub menu: ";
					cin >> innerOption;

					if (innerOption == 1)
					{
						FileDispatcher::PrintTrains(fileTrains);
					}
					else if (innerOption == 2)
					{
						cin.get();
						std::string trainToAdd;
						Train train = EnterTrainData();

						FileDispatcher::AddTrain(fileTrains, train);
					}
					else if (innerOption == 3)
					{
						cin.get();
						std::string trainToDelete;
						Train train;

						cout << "Enter train id: ";
						cin >> trainToDelete;
						train.SetID(trainToDelete);

						FileDispatcher::DeleteTrain(fileTrains, train);
					}
					else if (innerOption == 4)
					{
						cin.get();
						Train oldTrain;
						std::string train;						
						cout << "Enter train to edit id: ";
						cin >> train;
						oldTrain.SetID(train);

						cin.get();
						Train newTrain = EnterTrainData();					

						FileDispatcher::EditTrain(fileTrains, oldTrain, newTrain);
					}
					else
					{
						cout << "Invalid command" << endl;
					}
					break;

				case 3:
					cout << "1. Display schedule" << endl;
					cout << "2. Add schedule" << endl;
					cout << "3. Delete schedule" << endl;
					cout << "4. Edit schedule" << endl;
					cout << "5. Display schedule between two cities" << endl;
					cout << endl << "Choose a option from sub menu: ";
					cin >> innerOption;

					if (innerOption == 1)
					{
						FileDispatcher::PrintSchedule(fileSchedule);
					}
					else if (innerOption == 2)
					{
						cin.get();
						Schedule schedule = EnterScheduleData();
						FileDispatcher::AddSchedule(fileSchedule, schedule);
					}
					else if (innerOption == 3)
					{
						cin.get();
						Schedule schedule = EnterScheduleData();
						FileDispatcher::DeleteSchedule(fileSchedule, schedule);
					}
					else if (innerOption == 4)
					{
						cin.get();
						Schedule oldSchedule = EnterScheduleData();
						cin.get();
						Schedule newSchedule = EnterScheduleData();
						FileDispatcher::EditSchedule(fileSchedule, oldSchedule, newSchedule);
					}
					else if (innerOption == 5)
					{
						cin.get();
						std::string firstCity;
						std::cout << "First city: ";
						std::getline(cin, firstCity);
						std::string secondCity;
						std::cout << "Second city: ";
						std::getline(cin, secondCity);
						City first(firstCity);
						City second(secondCity);
						FileDispatcher::DisplayScheduleBetweenCities(fileSchedule, first, second);
						cout << endl;
					}
					else
					{
						cout << "Invalid command" << endl;
					}
					break;

				case 4:
					cout << "1. Sale tickets" << endl;
					cout << "2. Display information about a route" << endl;
					cout << endl << "Choose a option from sub menu: ";
					cin >> innerOption;
					
					if (innerOption == 1)
					{
						int route = 1;
						FileDispatcher::PrintSchedule(fileSchedule);

						do
						{
							cout << "Enter the number of route: ";
							cin >> route;
						}
						while (route < 1);

						std::string line = FileDispatcher::GetItem(fileSchedule, route);
						Schedule schedule = FileDispatcher::ParseSchedule(line);
						FileDispatcher::DisplayFreeSeats(schedule);

						cout << "How many seats would you like to reserve: ";
						int numberOfSeats;
						cin >> numberOfSeats;

						int* seats = new int[numberOfSeats];
						for (int i = 0; i < numberOfSeats; i++)
						{
							cout << "Enter seat: ";
							cin >> seats[i];
						}
						
						if (FileDispatcher::ReserveSeats(numberOfSeats, seats, schedule))
						{
							cout << "Seats reserved!" << endl;
						}
						else
						{
							cout << "Incorrect seats!" << endl;
						}
					}
					else if(innerOption == 2)
					{
						int route = 1;
						FileDispatcher::PrintSchedule(fileSchedule);
						do
						{
							cout << "Enter the number of route: ";
							cin >> route;
						}
						while (route < 1);

						std::string line = FileDispatcher::GetItem(fileSchedule, route);
						Schedule schedule = FileDispatcher::ParseSchedule(line);
						FileDispatcher::DisplayAllSeats(schedule);
						FileDispatcher::DisplayScheduleInformation(schedule);
					}
					else
					{
						cout << "Invalid input";
					}
					break;
				}				
			}
		}
		else
		{
			cout << "Goodbye! :]" << endl;
			break;
		}
	}
	while (true);
}

Schedule Engine::EnterScheduleData()
{
	std::string scheduleToAdd;
	City departure;
	City arrival;
	Train train;
	time_t date;
	tm timeinfo;						

	cout << "Enter city to depart: ";
	std::getline(cin, scheduleToAdd);
	departure.SetName(scheduleToAdd);
						
	cout << "Enter city to arrive: ";
	std::getline(cin, scheduleToAdd);
	arrival.SetName(scheduleToAdd);

	cout << "Enter train id: ";
	std::getline(cin, scheduleToAdd);
	train.SetID(scheduleToAdd);

	cout << "Enter day: ";
	int day = 1;
	cin >> day;
	timeinfo.tm_mday = day;

	cout << "Enter month: ";
	int month = 0;
	cin >> month;
	timeinfo.tm_mon = month - 1;

	cout << "Enter year: ";
	int year = 0;
	cin >> year;						
	timeinfo.tm_year = year - 1900;

	cout << "Enter hour: ";
	int hour = 0;
	cin >> hour;						
	timeinfo.tm_hour = hour;

	cout << "Enter minutes: ";
	int minutes = 0;
	cin >> minutes;
	timeinfo.tm_min = minutes;
	timeinfo.tm_sec = 1;
	timeinfo.tm_isdst = 0;

	cout << "Enter price: ";
	double price = 0;
	cin >> price;

	date = mktime(&timeinfo);
	Schedule schedule(departure, arrival, train, date, price);

	return schedule;
}

Train Engine::EnterTrainData()
{
	std::string trainToAdd;
	Train train;

	cout << "Enter train id: ";
	cin >> trainToAdd;
	train.SetID(trainToAdd);
	cout << "Enter train's number of seats: ";
	int seats = 0;
	cin >> seats;
	train.SetNumberOfSeats(seats);
	cin.get();
	cout << "Enter train description: ";
	std::getline(cin, trainToAdd);
	train.SetDescription(trainToAdd);

	return train;
}