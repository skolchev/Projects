#ifndef FILE_WRITE_STREAM_H
#define FILE_WRITE_STREAM_H

#define STREAM_BUFFER_SIZE 4096

#include "WriteStream.h"
#include <string>
#include <fstream>

using std::string;
using std::ofstream;
/**
* 	A concrete WriteStream that writes binary data into a file.
* 	Writing data to the file is optimized by buffering.
*/
class FileWriteStream : public WriteStream {
public:
	FileWriteStream(const string& filename);
	virtual ~FileWriteStream();
	virtual bool WriteBit(char bit);
	virtual bool WriteByte(char byte);
	virtual bool WriteUnsignedInt32(unsigned int value);
	virtual bool Flush();
private:
	string filename_;
	char* buffer_;
	ofstream file_stream_;
	unsigned int bit_index_;
	unsigned int total_bits_;
};

#endif