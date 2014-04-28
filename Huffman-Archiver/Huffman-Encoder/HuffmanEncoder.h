#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H
#include <map>
#include <string>
#include "HuffmanBinaryHeap.h"
/** A class that uses the binary heap to build a Huffman tree and Huffman table.
* It stores the frequency table.
*/
class HuffmanEncoder
{
private:
	HuffmanBinaryHeap* huffmanHeap;
	std::map<char, std::string> huffmanTable;
	std::map<char, unsigned int> frequencyTable;

public:
	HuffmanEncoder(const std::map<char, unsigned int>& frequencies);
	~HuffmanEncoder();
	
	void BuildTree();
	void BuildTable(HuffmanNode* root, std::string code);
	HuffmanNode* GetTree();
	std::map<char, std::string> GetTable();
};

#endif