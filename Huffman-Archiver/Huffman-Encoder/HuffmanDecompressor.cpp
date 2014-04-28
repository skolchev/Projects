#include "HuffmanDecompressor.h"
#include "HuffmanEncoder.h"

using std::map;

HuffmanDecompressor::HuffmanDecompressor(ReadStream* read, WriteStream* write)
{ 
	this->input_ = read;
	this->output_ = write;
}
void HuffmanDecompressor::DecompressFile()
{
	//Decode frequency table
	std::map<char, unsigned int> frequencies;
	unsigned int elements;
	//Read the number of unique bytes in the file
	this->input_->ReadUnsignedInt32(elements);

	if (elements == 0)
	{
		return;
	}

	//Read each byte and how many times it occur
	for (int i = 0; i < elements; i++) {
		char byte;
		this->input_->ReadByte(byte);
		unsigned int freq;
		this->input_->ReadUnsignedInt32(freq);
		frequencies[byte] = freq;
	}
	
	HuffmanEncoder huffmanEncoder(frequencies);
	huffmanEncoder.BuildTree();
	std::string code = "";
	HuffmanNode* huffmanTree = huffmanEncoder.GetTree();

	//Writes file size in bytes
	unsigned int bytes;
	this->input_->ReadUnsignedInt32(bytes);

	//Decode data
	while (bytes > 0) 
	{
		HuffmanNode* node = huffmanTree;

		if (!node->GetLeftChild() && !node->GetRightChild())
		{
			char bit;
			this->input_->ReadBit(bit);
		}
		while (node->GetLeftChild() != NULL &&
			node->GetRightChild() != NULL)
		{
			char bit;
			this->input_->ReadBit(bit);
			node = (bit == 0) ? node->GetLeftChild() : node->GetRightChild();
		}
		this->output_->WriteByte(node->GetLetter());
		bytes--;
	}
	input_->RoundBitIndex();
}