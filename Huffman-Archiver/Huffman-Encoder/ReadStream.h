#ifndef READ_STREAM_H
#define READ_STREAM_H
/**
*  A binary stream of data that can be read bit by bit or byte by byte or
*  32 bit unsigned integer by 32 bit unsigned integer or by any combination
*  of the above. Concrete stream classes can read data from files, in-memory
*  representations, networks, databases or other sources. The "Read*" methods
*  return true if the read operation is successful or false otherwise.
 */
class ReadStream
{
public:
	virtual ~ReadStream() {};
	virtual bool ReadBit(char& bit) = 0;
	virtual bool ReadByte(char& byte) = 0;
	virtual bool ReadUnsignedInt32(unsigned int& value) = 0;
	virtual bool Reset() = 0;
	virtual unsigned int Bytes() = 0;
	virtual void RoundBitIndex() = 0;
};

#endif