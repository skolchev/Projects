#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include "ReadStream.h"
#include "WriteStream.h"
#include "FileDecompressor.h"
/**
* An instance of FileDecompressor. Uses huffman encoding to decode a file.
*/
class HuffmanDecompressor : public FileDecompressor
{
private:
	ReadStream* input_;
	WriteStream* output_;
public:
	HuffmanDecompressor(ReadStream*, WriteStream*);
	virtual ~HuffmanDecompressor() {};
	virtual void DecompressFile();
};

#endif