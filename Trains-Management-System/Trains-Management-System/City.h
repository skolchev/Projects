#include <string>
#ifndef CITY_H
#define CITY_H

class City
{
public:
	City();
	City(std::string name);
	City(const City& city);

	City& operator=(const City& city);

	void SetName(std::string name);

	std::string ToString();
	bool operator==(const City& otherCity);
	bool operator!=(const City& otherCity);
private:
	std::string name;
};

#endif