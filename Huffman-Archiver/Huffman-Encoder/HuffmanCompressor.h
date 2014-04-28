#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include "FileCompressor.h"
#include <map>
/**
* An instance of FileCompressor. Uses huffman encoding to encode a file.
*/
class HuffmanCompressor : public FileCompressor
{
private:
	ReadStream* input_;
	WriteStream* output_;

public:
	HuffmanCompressor(ReadStream*, WriteStream*);
	virtual ~HuffmanCompressor();
	virtual void CompressFile();
	virtual void SetReadStream(ReadStream*);

private:
	std::map<char, unsigned int> GetByteFrequencies();
};

#endif