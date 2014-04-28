#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H
#include <string>
#include <iostream>
/**
* A class that models a Huffman tree node. The same structure is used
* both for leaf nodes and inner nodes of the Huffman tree.
*/
class HuffmanNode
{
private:
	int frequency;
	char letter;
	std::string code;
	HuffmanNode* leftChild;
	HuffmanNode* rightChild;

public:
	HuffmanNode();

	///< Leaf node constructor.
	HuffmanNode(int frequency, char letter);

	///< Inner node constructor.
	HuffmanNode(HuffmanNode* left, HuffmanNode* right);
	~HuffmanNode();

	int GetFrequency();
	char GetLetter();
	std::string GetCode();
	HuffmanNode* GetLeftChild();
	HuffmanNode* GetRightChild();

	void SetCode(std::string code);

	void PrintNode();

	HuffmanNode& operator=(const HuffmanNode& node);
};

#endif