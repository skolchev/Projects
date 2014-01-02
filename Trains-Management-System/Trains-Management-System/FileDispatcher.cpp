#include "FileDispatcher.h"
#include "Ticket.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <fstream>
#include <time.h>

using namespace std;

// Print methods
void FileDispatcher::PrintCities(std::string fileName)
{
	ifstream reader(fileName);
	std::string line;
	City city;
	int counter = 1;

	while (std::getline(reader, line))
	{
		if (line != "")
		{
			 city = ParseCity(line);
			 cout << counter << ". " << city.ToString() << endl;
			 counter++;
		}
	}
}

void FileDispatcher::PrintTrains(std::string fileName)
{
	ifstream reader(fileName);
	std::string line;
	Train train;
	int counter = 1;
	
	while (std::getline(reader, line))
	{
		train = ParseTrain(line);
		std::cout << counter << ". " << train.ToString() << endl;
		counter++;
	}

	reader.close();
}

void FileDispatcher::PrintSchedule(std::string fileName)
{
	ifstream reader(fileName);
	std::string line;
	Schedule schedule;
	int counter = 1;
	
	while (std::getline(reader, line))
	{
		schedule = ParseSchedule(line);		
		cout << counter << ". " << schedule.ToString() << endl;
		counter++;
	}

	reader.close();
}

// Add methods
// TODO: Fix adding empty lines
void FileDispatcher::AddCity(std::string fileName, City& city)
{
	int cityIndex = FindCity(fileName, city);

	if (cityIndex == 0)
	{
		ofstream writer(fileName, std::ios_base::app);
		
		writer << endl << city.ToString();
		writer.close();

		cout << city.ToString() << " added to file " << fileName << endl;
	}
	else
	{
		cout << city.ToString() << " already exists in " << fileName << endl;
	}
}

void FileDispatcher::AddTrain(std::string fileName, Train& train)
{
	int trainIndex = FindTrain(fileName, train);

	if (trainIndex == 0)
	{
		ofstream writer(fileName, std::ios_base::app);

		writer << endl << train.ToString();
		writer.close();

		cout << train.GetID() << " added to file " << fileName << endl;
	}
	else
	{
		cout << train.GetID() << " already exists in " << fileName << endl;
	}
}

void FileDispatcher::AddSchedule(std::string fileName, Schedule& schedule)
{
	int trainIndex = FindTrain("Trains.txt", schedule.GetTrain());
	if (trainIndex == 0)
	{
		cout << schedule.GetTrain().GetID() << "Train does not exist" << endl;
		return;
	}

	int cityIndex = FindCity("Cities.txt", schedule.GetDeparture());
	if (cityIndex == 0)
	{
		cout << schedule.GetDeparture().ToString() << " does not exist" << endl;
		return;
	}
	cityIndex = FindCity("Cities.txt", schedule.GetArrival());
	if (cityIndex == 0)
	{
		cout << schedule.GetArrival().ToString() << " does no exist" << endl;
		return;
	}

	int scheduleIndex = FindSchedule(fileName, schedule);
	if (scheduleIndex == 0)
	{
		ofstream writer(fileName, std::ios_base::app);

		writer << endl << schedule.ToString();
		writer.close();
		
		cout << "Schedule added to file " << fileName << endl;
	}
	else
	{
		cout << "This schedule already exists in " << fileName << endl;
	}
}

// Delete methods
void FileDispatcher::DeleteCity(std::string fileName, City& city)
{
	int indexOfCity = FindCity(fileName, city);
	int counter = 1;
	if (indexOfCity == 0)
	{
		std::cout << "Cannot find " << city.ToString() << " in " << fileName << endl;
		return;
	}

	ifstream scheduleReader("Schedule.txt");
	Schedule schedule;
	std::string scheduleLine;
	
	while (std::getline(scheduleReader, scheduleLine))
	{
		schedule = ParseSchedule(scheduleLine);
		if (schedule.GetDeparture() == city || schedule.GetArrival() == city)
		{
			std::cout << "City cannot be deleted, because it exists in schedule." << endl;
			return;
		}
	}

	scheduleReader.close();
	
	bool isFirstLine = true;

	std::string newFile = "OutputCities.txt";
	std::string line;

	ifstream reader(fileName);
	ofstream writer(newFile);

	while (std::getline(reader, line))
	{
		if (counter != indexOfCity)
		{
			if (isFirstLine)
			{
				writer << line;
				isFirstLine = false;
			}
			else
			{
				writer << endl << line;
			}
		}
		counter++;
	}

	writer.close();
	reader.close();

	std::remove(fileName.c_str());
	std::rename(newFile.c_str(), fileName.c_str());

	std::cout << city.ToString() << " removed from " << fileName << endl;
}

void FileDispatcher::DeleteTrain(std::string fileName, Train& train)
{
	int indexOfTrain = FindTrain(fileName, train);
	int counter = 1;
	if (indexOfTrain == 0)
	{
		std::cout << "Cannot find " << train.GetID() << " in " << fileName << endl;
		return;
	}

	ifstream scheduleReader("Schedule.txt");
	Schedule schedule;
	std::string scheduleLine;
	
	while (std::getline(scheduleReader, scheduleLine))
	{
		schedule = ParseSchedule(scheduleLine);
		if (schedule.GetTrain() == train)
		{
			std::cout << "Train cannot be deleted, because it exists in schedule." << endl;
			return;
		}
	}

	scheduleReader.close();

	bool isFirstLine = true;

	std::string newFile = "OutputTrains.txt";
	std::string line;

	ifstream reader(fileName);
	ofstream writer(newFile);

	while (std::getline(reader, line))
	{
		if (counter != indexOfTrain)
		{
			if (isFirstLine)
			{
				writer << line;
				isFirstLine = false;
			}
			else
			{
				writer << endl << line;
			}
		}
		counter++;
	}

	writer.close();
	reader.close();

	std::remove(fileName.c_str());
	std::rename(newFile.c_str(), fileName.c_str());

	std::cout << train.GetID() << " removed from " << fileName << endl;
}

void FileDispatcher::DeleteSchedule(std::string fileName, Schedule& schedule)
{
	int indexOfSchedule = FindSchedule(fileName , schedule);
	int counter = 1;
	if (indexOfSchedule == 0)
	{
		std::cout << "Cannot find schedule in " << fileName << endl;
		return;
	}

	std::string scheduleStr = GetItem(fileName, indexOfSchedule);
	Schedule scheduleToDelete = ParseSchedule(scheduleStr);
	std::string ticketFile = GetFileName(scheduleToDelete);
	fstream ticketReader(ticketFile, ios::binary | ios::in);
	Ticket ticket;
	int numberOfSeats = scheduleToDelete.GetTrain().GetNumberOfSeats();
	for (int i = 0; i < numberOfSeats; i++)
	{
		ticketReader.seekg(i * sizeof(Ticket));
		ticketReader.read((char*)&ticket, sizeof(Ticket));
		if (ticket.IsReserved())
		{
			cout << "Cannot delete schedule. Tickets have already been bought." << endl;
			return;
		}
	}
	ticketReader.close();

	bool isFirstLine = true;

	std::string newFile = "OutputSchedule.txt";
	std::string line;

	ifstream reader(fileName);
	ofstream writer(newFile);

	while (std::getline(reader, line))
	{
		if (counter != indexOfSchedule)
		{
			if (isFirstLine)
			{
				writer << line;
				isFirstLine = false;
			}
			else
			{
				writer << endl << line;
			}			
		}
		counter++;
	}

	writer.close();
	reader.close();

	std::remove(fileName.c_str());
	std::rename(newFile.c_str(), fileName.c_str());

	std::cout << "Schedule deleted from " << fileName << endl;
}

// Edit methods
void FileDispatcher::EditTrain(std::string fileName, Train& oldTrain, Train& newTrain)
{
	int indexOfTrain = FindTrain(fileName, oldTrain);
	int counter = 1;
	if (indexOfTrain == 0)
	{
		std::cout << "Cannot find " << oldTrain.GetID() << " in " << fileName << endl;
		return;
	}

	if (FindTrain(fileName, newTrain) != 0)
	{
		std::cout << newTrain.GetID() << " already exists in " << fileName << endl;
		return;
	}

	std::string newFile = "OutputTrains.txt";
	std::string line;

	ifstream reader(fileName);
	ofstream writer(newFile);

	while (std::getline(reader, line))
	{
		if (counter != indexOfTrain)
		{
			writer << line << endl;
		}
		else
		{
			writer << newTrain.ToString() << endl;
		}
		counter++;
	}

	writer.close();
	reader.close();

	std::remove(fileName.c_str());
	std::rename(newFile.c_str(), fileName.c_str());

	ifstream scheduleReader("Schedule.txt");
	Schedule schedule;
	std::string scheduleLine;
	
	while (std::getline(scheduleReader, scheduleLine))
	{
		schedule = ParseSchedule(scheduleLine);
		if (schedule.GetTrain() == oldTrain)
		{
			Schedule newSchedule = schedule;
			newSchedule.SetTrain(newTrain);
			EditSchedule("Schedule.txt", schedule, newSchedule);
		}
	}

	scheduleReader.close();

	std::cout << oldTrain.GetID() << " edited" << endl;
}

void FileDispatcher::EditSchedule(std::string fileName, Schedule& oldSchedule, Schedule& newSchedule)
{
	int indexOfSchedule = FindSchedule(fileName, oldSchedule);
	int counter = 1;
	if (indexOfSchedule == 0)
	{
		cout << "Schedule does not exist in " << fileName << endl;
		return;
	}

	int indexOfNewSchedule = FindSchedule(fileName, newSchedule);
	if (indexOfNewSchedule != 0)
	{
		cout << "Schedule already exists in " << fileName << endl;
		return;
	}

	std::string newFile = "OutputSchedule.txt";
	std::string line;

	ifstream reader(fileName);
	ofstream writer(newFile);

	while (std::getline(reader, line))
	{
		if (counter != indexOfSchedule)
		{
			writer << line << endl;
		}
		else
		{
			writer << newSchedule.ToString() << endl;
		}
		counter++;
	}

	writer.close();
	reader.close();

	remove(fileName.c_str());
	rename(newFile.c_str(), fileName.c_str());

	cout << "Schedule edited" << endl;
}

void FileDispatcher::DisplayScheduleBetweenCities(std::string fileName, City& first, City& second)
{
	ifstream reader(fileName);

	Schedule schedule;
	std::string line;
	int counter = 1;
	while (std::getline(reader, line))
	{
		schedule = ParseSchedule(line);
		if ((schedule.GetDeparture() == first && schedule.GetArrival() == second) ||
			(schedule.GetArrival() == first && schedule.GetDeparture() == second))
		{
			cout << counter << ". " << schedule.ToString() << endl;
			counter++;
		}
	}

	reader.close();
}


// Ticket methods

void FileDispatcher::DisplayFreeSeats(Schedule& schedule)
{
	std::string fileName = GetFileName(schedule);

	fstream reader(fileName, ios::binary | ios::in);
	Ticket ticket;
	int numberOfSeats = schedule.GetTrain().GetNumberOfSeats();
	int counter = 1;

	for (int i = 0; i < numberOfSeats; i++)
	{
		reader.seekg(i * sizeof(Ticket));
		reader.read((char*)&ticket, sizeof(Ticket));
		if (!ticket.IsReserved())
		{
			cout << counter << ". " << ticket.ToString() << endl;
		}
		counter++;
	}

	reader.close();
}

void FileDispatcher::DisplayAllSeats(Schedule& schedule)
{
	std::string fileName = GetFileName(schedule);

	fstream reader(fileName, ios::binary | ios::in);
	Ticket ticket;
	int numberOfSeats = schedule.GetTrain().GetNumberOfSeats();
	int counter = 1;

	for (int i = 0; i < numberOfSeats; i++)
	{
		reader.seekg(i * sizeof(Ticket));
		reader.read((char*)&ticket, sizeof(Ticket));
		cout << counter << ". " << ticket.ToString() << endl;
		counter++;
	}	

	reader.close();
}

bool FileDispatcher::ReserveSeats(int numberOfSeats, int* seats, Schedule& schedule)
{
	std::string fileName = GetFileName(schedule);

	fstream reader(fileName, ios::binary | ios::in | ios::out);
	Ticket ticket;
	time_t date;
	tm* timeinfo;
	time(&date);
	timeinfo = gmtime(&date);
	timeinfo->tm_hour += 2;
	date = mktime(timeinfo);
	int seatsInTrain = schedule.GetTrain().GetNumberOfSeats();

	for (int i = 0; i < numberOfSeats; i++)
	{
		if (seats[i] < 1 || seats[i] > seatsInTrain)
		{
			cout << "Seat number must be between 1 and " << seatsInTrain << endl;
		}
		reader.seekg((seats[i] - 1) * sizeof(Ticket));
		reader.read((char*)&ticket, sizeof(Ticket));
		if (ticket.IsReserved() == true)
		{
			cout << seats[i] << "is already reserved" << endl;
			return false;
		}
	}

	for (int i = 0; i < numberOfSeats; i++)
	{
		reader.seekp((seats[i] - 1) * sizeof(Ticket));
		ticket.SetReserved(true);
		ticket.SetPrice(schedule.GetPrice());
		ticket.SetSold(date);
		reader.write((char*)&ticket, sizeof(Ticket));
	}

	reader.close();

	return true;
}

void FileDispatcher::DisplayScheduleInformation(Schedule& schedule)
{
	std::string fileName = GetFileName(schedule);

	fstream reader(fileName, ios::binary | ios::in);
	Ticket ticket;
	int numberOfSeats = schedule.GetTrain().GetNumberOfSeats();
	double incomes = 0;
	time_t startTime = 0;
	time_t endTime = 0;
	tm* ptr;

	for (int i = 0; i < numberOfSeats; i++)
	{
		reader.read((char*)&ticket, sizeof(Ticket));
		if (ticket.IsReserved())
		{
			incomes += ticket.Price();
			if (startTime > ticket.SoldOn())
			{
				startTime = ticket.SoldOn();
			}
			if (endTime < ticket.SoldOn())
			{
				endTime = ticket.SoldOn();
			}
		}
	}

	cout << "Total incomes from sales: " << incomes << endl;
	if (incomes == 0)
	{
		cout << "No tickets have been sold yet." << endl;
	}
	else
	{
		time(&startTime);
		time(&endTime);
		cout << "Tickets sold between: " << endl
			<< ctime(&startTime)
			<< "and: " << endl
			<< ctime(&endTime);
	}
	reader.close();
}

void FileDispatcher::LoadTicketsFiles(std::string fileName)
{
	ifstream reader(fileName);
	std::string line;
	std::string newFile;
	Schedule schedule;
	while (std::getline(reader, line))
	{
		schedule = ParseSchedule(line);
		SaveTickets(schedule);
	}

	reader.close();
}

// Private methods
City FileDispatcher::ParseCity(std::string line)
{
	City city;
	line = TrimBoth(line);
	city.SetName(line);

	return city;
}

Train FileDispatcher::ParseTrain(std::string line)
{
	Train train;
	std::string delimeters = ",";
	size_t current = 0;
	size_t next = -1;

	line = TrimBoth(line);
		
	next = line.find_first_of(delimeters, current);
	std:: string id = line.substr(current, next - current);
	id = TrimRight(id);
	train.SetID(id);
	line = line.substr(next + 1, line.length());
	line = TrimLeft(line);

	next = line.find_first_of(delimeters, current);
	int numberOfSeats = atoi(line.substr(current, next - current).c_str());
	train.SetNumberOfSeats(numberOfSeats);
	line = line.substr(next + 1, line.length());
	line = TrimLeft(line);

	train.SetDescription(line);

	return train;
}
// TODO: Fix adding train seats
Schedule FileDispatcher::ParseSchedule(std::string line)
{
	City departure;
	City arrival;
	Train train;
	time_t date;
	tm pDate;
	double price;

	std::string delimeters = " ,\t->.:";
	size_t current = 0;
	size_t next = -1;

	line = TrimBoth(line);

	next = line.find_first_of(delimeters, current);
	departure.SetName(line.substr(current, next - current));
	line = line.substr(next + 4, line.length());

	next = line.find_first_of(delimeters, current);
	arrival.SetName(line.substr(current, next - current));
	line = line.substr(next + 1, line.length());
	line = TrimLeft(line);

	next = line.find_first_of(delimeters, current);
	int number = atoi(line.substr(current, next - current).c_str());
	pDate.tm_mday = number;
	line = line.substr(next + 1, line.length());
	next = line.find_first_of(delimeters, current);
	number = atoi(line.substr(current, next - current).c_str());
	pDate.tm_mon = number - 1;
	line = line.substr(next + 1, line.length());
	next = line.find_first_of(delimeters, current);
	number = atoi(line.substr(current, next - current).c_str());
	pDate.tm_year = number - 1900;
	line = line.substr(next + 1, line.length());
	line = TrimLeft(line);

	next = line.find_first_of(delimeters, current);
	number = atoi(line.substr(current, next - current).c_str());
	pDate.tm_hour = number;
	line = line.substr(next + 1, line.length());
	next = line.find_first_of(delimeters, current);
	number = atoi(line.substr(current, next - current).c_str());
	pDate.tm_min = number;
	line = line.substr(next + 1, line.length());
	pDate.tm_sec = 1;
	pDate.tm_isdst = 0;
	date = mktime(&pDate);
	line = TrimLeft(line);

	next = line.find_first_of(delimeters, current);
	train.SetID(line.substr(current, next - current));
	line = line.substr(next + 1, line.length());
	line = TrimLeft(line);	

	price = atof(line.c_str());

	int indexOfTrain = FindTrain("Trains.txt", train);
	if (indexOfTrain == 0)
	{
		std::cout << "Train with given id does not exist" << endl;
	}
	else
	{
		std::string trainData = GetItem("Trains.txt", indexOfTrain);
		train = ParseTrain(trainData);
	}
	Schedule schedule(departure, arrival, train, date, price);

	return schedule;	
}


int FileDispatcher::FindCity(std::string fileName, City& city)
{
	ifstream reader(fileName);
	std::string line;
	City currentCity;
	int counter = 1;

	while (std::getline(reader, line))
	{
		line = TrimBoth(line);
		currentCity = ParseCity(line);
		
		if (currentCity.ToString() == city.ToString())
		{
			return counter;
		}
		counter++;
	}

	reader.close();

	return 0;
}

int FileDispatcher::FindTrain(std::string fileName, Train& train)
{
	ifstream reader(fileName);
	std::string line;
	Train currentTrain;
	int counter = 1;

	while (std::getline(reader, line))
	{
		currentTrain = ParseTrain(line);
		if (currentTrain.GetID() == train.GetID())
		{
			return counter;
		}
		counter++;
	}

	reader.close();

	return 0;
}

int FileDispatcher::FindSchedule(std::string fileName, Schedule& schedule)
{
	ifstream reader(fileName);
	std::string line;
	Schedule currentSchedule;
	int indexOfSchedule = 1;
	
	while (std::getline(reader, line))
	{
		currentSchedule = ParseSchedule(line);
		if (currentSchedule == schedule)
		{
			return indexOfSchedule;
		}
		indexOfSchedule++;
	}

	reader.close();

	return 0;
}


void FileDispatcher::SaveTickets(Schedule& schedule)
{
	std::string fileName = GetFileName(schedule);

	fstream writer(fileName, ios::out | ios::binary);

	Ticket ticket;
	ticket.SetPrice(schedule.GetPrice());
	int numberOfSeats = schedule.GetTrain().GetNumberOfSeats();
	for (int i = 0; i < numberOfSeats; i++)
	{
		writer.seekp(i * sizeof(Ticket));
		writer.write((char*)&ticket, sizeof(Ticket));
	}

	writer.close();
}


std::string FileDispatcher::GetFileName(Schedule& schedule)
{
	std::string result = "";
	result += schedule.GetDeparture().ToString();
	result += "-";
	result += schedule.GetArrival().ToString();
	result += "-";
	
	time_t timeinfo = schedule.GetDate();
	tm* date = gmtime(&timeinfo);
	char day[3];
	char month[3];
	char year[5];
	int currentMonth = date->tm_mon + 1;
	int currentYear = date->tm_year + 1900;
	itoa(date->tm_mday, day, 10);
	itoa(currentMonth, month, 10);
	itoa(currentYear, year, 10);
	result += day;
	result += "-";
	result += month;
	result += "-";
	result += year;
	result += "-";

	char hour[3];
	char minutes[3];
	int currentHour = date->tm_hour + 2;
	itoa(currentHour, hour, 10);
	itoa(date->tm_min, minutes, 10);
	result += hour;
	result += "-";
	result += minutes;
	result += "-";

	result += schedule.GetTrain().GetID();
	result += ".bin";

	return result;
}

std::string FileDispatcher::GetItem(std::string fileName, int indexOfLine)
{
	ifstream reader(fileName);
	std::string line;
	int counter = 1;

	while (std::getline(reader, line))
	{
		if (counter == indexOfLine)
		{
			return line;
		}
		counter++;
	}

	reader.close();
}


inline std::string& FileDispatcher::TrimLeft(std::string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return str;
}

inline std::string& FileDispatcher::TrimRight(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
	return str;
}

inline std::string& FileDispatcher::TrimBoth(std::string& str)
{
	return TrimLeft(TrimRight(str));
}