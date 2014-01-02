#include "Train.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// Constructors
Train::Train()
{
	this->SetID("");
	this->SetNumberOfSeats(0);
	this->SetDescription("");
}

Train::Train(std::string id, int numberOfSeats, std::string description)
{
	this->SetID(id);
	this->SetNumberOfSeats(numberOfSeats);
	this->SetDescription(description);
}

Train::Train(const Train& train)
{
	this->SetID(train.id);
	this->SetNumberOfSeats(train.numberOfSeats);
	this->SetDescription(train.description);
}

Train& Train::operator=(const Train& train)
{
	this->SetID(train.id);
	this->SetNumberOfSeats(train.numberOfSeats);
	this->SetDescription(train.description);

	return *this;
}

// Methods
std::string Train::ToString()
{
	std::string result = "";
	result += this->GetID();
	result += ", ";

	char number[5];
	itoa(this->GetNumberOfSeats(), number, 10);
	result += number;
	result += ", ";

	result += this->GetDescription();

	return result;
}

bool Train::operator==(const Train& otherTrain)
{
	if (this->id == otherTrain.id)
	{
		return true;
	}

	return false;
}

bool Train::operator!=(const Train& otherTrain)
{
	if (this->id != otherTrain.id)
	{
		return true;
	}

	return false;
}

// Setters
void Train::SetID(std::string id)
{
	this->id = id;
}

void Train::SetDescription(std::string description)
{
	this->description = description;
}

void Train::SetNumberOfSeats(int numberOfSeats)
{
	this->numberOfSeats = numberOfSeats;
}

// Getters
std::string Train::GetID()
{
	return this->id;
}

std::string Train::GetDescription()
{
	return this->description;
}

int Train::GetNumberOfSeats()
{
	return this->numberOfSeats;
}