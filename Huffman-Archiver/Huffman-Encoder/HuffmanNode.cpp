#include "HuffmanNode.h"

using namespace std;

HuffmanNode::HuffmanNode()
{
	this->frequency = 0;
	this->letter = ' ';
	this->leftChild = NULL;
	this->rightChild = NULL;
}

HuffmanNode::HuffmanNode(int frequency, char letter)
{
	this->frequency = frequency;
	this->letter = letter;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

HuffmanNode::HuffmanNode(HuffmanNode* left, HuffmanNode* right)
{
	this->frequency = left->frequency + right->frequency;
	this->letter = NULL;
	this->leftChild = left;
	this->rightChild = right;
}

HuffmanNode::~HuffmanNode()
{
	delete this->leftChild;
	delete this->rightChild;
}

int HuffmanNode::GetFrequency() { return this->frequency; }

char HuffmanNode::GetLetter() { return this->letter; }

std::string HuffmanNode::GetCode() { return this->code; }

HuffmanNode* HuffmanNode::GetLeftChild() { return this->leftChild; }

HuffmanNode* HuffmanNode::GetRightChild() { return this->rightChild; }

void HuffmanNode::SetCode(std::string code) { this->code = code; }

void HuffmanNode::PrintNode()
{
	cout << "Frequency: " << this->GetFrequency() << endl
		<< "Code: " << this->GetCode() << endl
		<< "Letter: " << this->GetCode() << endl
		<< "Left child: " << (this->GetLeftChild() ? "Yes" : "NULL") << endl
		<< "Right child: " << (this->GetRightChild() ? "Yes" : "NULL") << endl;
}

HuffmanNode& HuffmanNode::operator=(const HuffmanNode& node)
{
	if (this != &node)
	{
		this->frequency = node.frequency;
		this->letter = node.letter;
		this->code = node.code;

		delete this->leftChild;
		delete this->rightChild;

		this->leftChild = node.leftChild;
		this->rightChild = node.rightChild;
	}

	return *this;
}