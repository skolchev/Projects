#include <string>
#ifndef TRAIN_H
#define TRAIN_H

class Train
{
public:
	Train();
	Train(std::string id, int numberOfSeats, std::string description);
	Train(const Train& train);

	Train& operator=(const Train& train);

	void SetID(std::string id);
	void SetDescription(std::string description);
	void SetNumberOfSeats(int numberOfSeats);

	std::string GetID();
	std::string GetDescription();
	int GetNumberOfSeats();

	std::string ToString();
	bool operator==(const Train& otherTrain);
	bool operator!=(const Train& otherTrain);

private:
	std::string id;
	std::string description;
	int numberOfSeats;
};

#endif