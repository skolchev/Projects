#ifndef WRITE_STREAM_H
#define WRITE_STREAM_H
/**
	* A binary stream of data that can be written bit by bit or byte by byte or
	* 32 bit unsigned integer by 32 bit unsigned integer or by any combination
	* of the above. Concrete stream classes can write data to files, in-memory
	* representations, networks, databases or other sources. The "Write*" methods
	* return true if the write operation is successful or false otherwise.
*/
class WriteStream {
public:
	virtual ~WriteStream() {}
	virtual bool WriteBit(char bit) = 0;
	virtual bool WriteByte(char byte) = 0;
	virtual bool WriteUnsignedInt32(unsigned int value) = 0;
	virtual bool Flush() = 0;
};

#endif