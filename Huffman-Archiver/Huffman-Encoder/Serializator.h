// A class for a file deserialization
#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include "ReadStream.h"
#include "WriteStream.h"
#include "FileCompressor.h"
#include <string>

class Serializator
{
public:
	/**
	* 	Requires an input string for directory you want to archive.
	* A pointer to WriteStream for the ofstream where you want to write data.
	* A pointer to file compressor.
	*/
	Serializator(std::string input, WriteStream* output, FileCompressor* compressor);
	~Serializator();
	void Serialize();

private:
	std::string input_;
	WriteStream* output_;
	FileCompressor* compressor_;
};

#endif