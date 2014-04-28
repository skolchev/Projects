#ifndef HUFFMANBINARYHEAP_H
#define HUFFMANBINARYHEAP_H
#include "HuffmanNode.h"
/**
* 	Implementation of basic binary heap
*/
class HuffmanBinaryHeap
{
private:
	HuffmanNode** data;
	int size;
	int capacity;

	void SiftUp(int currentIndex);
	void SiftDown(int currentIndex);
	int NumberOfChildren(int currentIndex);

public:
	HuffmanBinaryHeap(int size);
	~HuffmanBinaryHeap();

	int GetSize();
	int GetCapacity();
	HuffmanNode* GetMin();

	void Add(HuffmanNode* node);
	HuffmanNode* RemoveMin();
	bool IsEmpty();

	void Print();
};

#endif