#include "HuffmanCompressor.h"
#include "HuffmanEncoder.h"

HuffmanCompressor::HuffmanCompressor(ReadStream* input, WriteStream* output)
{
	this->input_ = input;
	this->output_ = output;
}

HuffmanCompressor::~HuffmanCompressor()
{

}

std::map<char, unsigned int> HuffmanCompressor::GetByteFrequencies()
{
	std::map<char, unsigned int> frequencies;

	while (true)
	{
		char byte;
		if (!input_->ReadByte(byte))
		{
			break;
		}
		frequencies[byte]++;
	}

	return frequencies;
}

void HuffmanCompressor::CompressFile()
{
	// TODO: Refactor
	std::map<char, unsigned int> frequencies = GetByteFrequencies();
	if (frequencies.size() == 0)
	{
		output_->WriteUnsignedInt32(0);
		output_->Flush();
		return;
	}
	HuffmanEncoder* huffmanEncoder = new HuffmanEncoder(frequencies);
	huffmanEncoder->BuildTree();
	HuffmanNode* huffmanTree = huffmanEncoder->GetTree();
	std::string code = "";
	huffmanEncoder->BuildTable(huffmanTree, code);
	std::map<char, std::string> encodedBytes = huffmanEncoder->GetTable();

	// Write the number of bytes that occur
	unsigned int numberOfBytes = frequencies.size();
	output_->WriteUnsignedInt32(numberOfBytes);

	// Write frequency table
	for (std::map<char, unsigned int>::iterator it = frequencies.begin();
		it != frequencies.end(); ++it)
	{
		output_->WriteByte(it->first);
		output_->WriteUnsignedInt32(it->second);
	}

	// Write the number of bytes that the file contains
	unsigned int bytes = input_->Bytes();
	input_->Reset();
	output_->WriteUnsignedInt32(bytes);

	// Read the file and write the encoded string for each byte
	while (true)
	{
		char byte;
		if (!input_->ReadByte(byte))
		{
			break;
		}
		std::string byteCode = encodedBytes[byte];
		for (int i = 0; i < byteCode.size(); i++)
		{
			output_->WriteBit(byteCode[i]);
		}
	}

	output_->Flush();
	delete huffmanEncoder;
}

void HuffmanCompressor::SetReadStream(ReadStream* input)
{
	delete input_;
	input_ = input;
}