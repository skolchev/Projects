#include "HuffmanBinaryHeap.h"

using namespace std;

HuffmanBinaryHeap::HuffmanBinaryHeap(int capacity)
{
	this->data = new HuffmanNode*[capacity];
	for (int i = 0; i < capacity; i++)
	{
		this->data[i] = NULL;
	}
	this->capacity = capacity;
	this->size = 0;
}

HuffmanBinaryHeap::~HuffmanBinaryHeap()
{
	for (int i = 0; i < this->capacity; i++)
	{
		if (this->data[i] != NULL)
		{
			delete this->data[i];
			this->size--;
		}
	}

	delete [] this->data;
}

bool HuffmanBinaryHeap::IsEmpty() { return this->size == 0; }

int HuffmanBinaryHeap::GetSize() { return this->size; }

int HuffmanBinaryHeap::GetCapacity() { return this->capacity; }

HuffmanNode* HuffmanBinaryHeap::GetMin() 
{ 
	if (!IsEmpty())
	{
		return this->data[0];
	}
 }

int HuffmanBinaryHeap::NumberOfChildren(int currentIndex)
{
	int numberOfChildren = 0;
	int left = currentIndex * 2 + 1;
	int right = currentIndex * 2 + 2;

	if (left >= this->size) return 0;
	if (this->data[left] != NULL) numberOfChildren++;
	if (this->data[right] != NULL) numberOfChildren++;

	return numberOfChildren;	
}

void HuffmanBinaryHeap::SiftDown(int currentIndex)
{
	int children = 0;
	children = NumberOfChildren(currentIndex);
	int left = 2 * currentIndex + 1;
	int right = 2 * currentIndex + 2;
	HuffmanNode* temp;

	if (children == 1)
	{
		if (this->data[currentIndex]->GetFrequency() > this->data[left]->GetFrequency())
		{
			temp = this->data[currentIndex];
			this->data[currentIndex] = this->data[left];
			this->data[left] = temp;
			SiftDown(left);
		}
	}
	else if (children == 2)
	{
		if (this->data[currentIndex]->GetFrequency() > this->data[left]->GetFrequency() ||
			this->data[currentIndex]->GetFrequency() > this->data[right]->GetFrequency())
		{
			if (this->data[left]->GetFrequency() <= this->data[right]->GetFrequency())
			{
				temp = this->data[currentIndex];
				this->data[currentIndex] = this->data[left];
				this->data[left] = temp;
				SiftDown(left);
			}
			else
			{
				temp = this->data[currentIndex];
				this->data[currentIndex] = this->data[right];
				this->data[right] = temp;
				SiftDown(right);
			}
		}
	}
	return;
}

void HuffmanBinaryHeap::SiftUp(int currentIndex)
{
	// Return if we are on top
	if (currentIndex < 1)
	{
		return;
	}

	int parent = floor((currentIndex - 1) / 2);
	if (this->data[currentIndex]->GetFrequency() < this->data[parent]->GetFrequency())
	{
		HuffmanNode* temp = this->data[parent];
		this->data[parent] = this->data[currentIndex];
		this->data[currentIndex] = temp;
		SiftUp(parent);
	}
}

HuffmanNode* HuffmanBinaryHeap::RemoveMin()
{
	if (this->IsEmpty())
	{
		return NULL;
	}

	HuffmanNode* minNode = this->data[0];
	this->data[0] = this->data[this->size - 1];
	this->data[this->size - 1] = NULL;
	this->size--;
	SiftDown(0);

	return minNode;
}

void HuffmanBinaryHeap::Add(HuffmanNode* node)
{
	if (this->capacity == this->size)
	{
		return;
	}

	this->size++;
	this->data[size - 1] = node;
	SiftUp(size - 1);
}

void HuffmanBinaryHeap::Print()
{
	int parent = 0;
	int left = parent * 2 + 1, right = parent * 2 + 2;
	while (parent < size)
	{
		cout << this->data[parent]->GetFrequency() << " ";
			// << this->data[left]->GetFrequency() << " "
			// << this->data[right]->GetFrequency() << " ";
		
		parent++;
	}
	cout << endl;
}