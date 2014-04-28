// An abstract class for all data decompressing algorithms
#ifndef FILE_DECOMPRESSOR_H
#define FILE_DECOMPRESSOR_H

#include "ReadStream.h"
#include "WriteStream.h"

class FileDecompressor
{
public:
	/**
	* Empty virtual destructor.
	*/
	virtual ~FileDecompressor() {};
	/**
	* A base method that is used to compress the file with given algorithm.
	*/
	virtual void DecompressFile() = 0;
};

#endif