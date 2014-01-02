#include "City.h"
#include "Train.h"
#include "Schedule.h"
#include "FileDispatcher.h"
#include "Ticket.h"
#include "Engine.h"
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

int main()
{
	Engine engine("Cities.txt", "Trains.txt", "Schedule.txt");
	engine.Run();

	return 0;
}