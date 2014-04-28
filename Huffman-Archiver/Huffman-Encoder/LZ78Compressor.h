// Derived class for LZ78 encoding
#ifndef LZ78_COMPRESSOR_H
#define LZ78_COMPRESSOR_H

#include "FileCompressor.h"

class LZ78Compressor : public FileCompressor
{
public:
	virtual void CompressFile();
};
#endif