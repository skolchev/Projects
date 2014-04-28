#include "BitWriter.h"

BitWriter::BitWriter(const string fileName)
{
	this->fileName = fileName;
	this->output.open(fileName.c_str(), std::ofstream::binary);
	this->buffer = 0;
	this->size = 0;
}

BitWriter::~BitWriter()
{
	this->output.close();
}

void BitWriter::Flush()
{
	this->output.write((char*)&buffer, sizeof(buffer));
	this->size = 0;
	this->buffer = 0;
}

void BitWriter::WriteBit(unsigned char bit)
{
	if (this->size == MAX_SIZE)
	{
		// Flush buffer into file
		Flush();
	}

	buffer <<= 1;
	if (bit == 1)
	{
		// Change bit at last position to 1
		buffer = buffer | 1;
	}
	else if (bit == 0)
	{
		// Change bit at last position to 0
		buffer = buffer & (~1);
	}
}