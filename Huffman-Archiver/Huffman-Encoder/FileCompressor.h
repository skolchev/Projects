// An abstract class for all data compressing algorithms
#ifndef FILE_COMPRESSOR_H
#define FILE_COMPRESSOR_H

#include "ReadStream.h"
#include "WriteStream.h"

class FileCompressor
{
public:
	/**
	* Empty virtual destructor. 
	*/
	virtual ~FileCompressor() {};
	/**
	* A base method that is used to compress the file with given algorithm.
	*/
	virtual void CompressFile() = 0;
	/**
	* A method that changes the current ReadStream*.
	*/
	virtual void SetReadStream(ReadStream*) = 0;
};

#endif