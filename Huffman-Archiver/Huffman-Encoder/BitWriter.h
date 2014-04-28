#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include <fstream>
#include <string>

using std::ofstream;
using std::string;

class BitWriter
{
public:
	/** Constructor, initializes output ofstream with given file name
	*/
	BitWriter(const string fileName);
	/** Empty Destuctor
	*/
	~BitWriter();
	/** 
	*/
	void WriteBit(unsigned char bit);
	void Flush();

private:
	const int MAX_SIZE = 8;
	int size;
	unsigned char buffer;
	string fileName;
	ofstream output;
};

#endif