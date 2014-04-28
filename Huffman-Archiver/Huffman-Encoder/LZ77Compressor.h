// Derived class for LZ77 encoding
#ifndef LZ77_COMPRESSOR_H
#define LZ77_COMPRESSOR_H

#include "FileCompressor.h"

class LZ77Compressor : public FileCompressor
{
public:
	virtual void CompressFile();
};

#endif