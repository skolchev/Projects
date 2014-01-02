#include "City.h"
#include <iostream>
#include <string>

using namespace std;

City::City()
{
	this->SetName("");
}

City::City(std::string name)
{
	this->SetName(name);
}

City::City(const City& city)
{
	this->SetName(city.name);
}

City& City::operator=(const City& city)
{
	this->SetName(city.name);

	return *this;
}

void City::SetName(std::string name)
{
	this->name = name;
}

std::string City::ToString()
{
	return this->name;
}

bool City::operator==(const City& otherCity)
{
	if (this->name == otherCity.name)
	{
		return true;
	}

	return false;
}

bool City::operator!=(const City& otherCity)
{
	if (this->name != otherCity.name)
	{
		return true;
	}

	return false;
}