#include "Deserializator.h"
#include "FileWriteStream.h"
#include "FileReadStream.h"
#include "FileDispatcher.h"
#include "HuffmanEncoder.h"
#include "HuffmanCompressor.h"
#include "HuffmanDecompressor.h"
#include <vector>
#include <string>

Deserializator::Deserializator(std::string input, std::string output)
{
	this->input_ = input;
	this->output_ = output;
	this->inputStream_ = new FileReadStream(input_);
}

Deserializator::~Deserializator()
{
	delete inputStream_;
}

bool Deserializator::DeserializeDirectory()
{
	unsigned int length;
	//Read the length of directory name
	if (!inputStream_->ReadUnsignedInt32(length)) return false;
	string directory_name;
	//Read the directory name
	for (int i = 0; i < (int)length; i++) {
		char byte;
		if (!inputStream_->ReadByte(byte)) return false;
		directory_name += byte;
	}
	directory_name = output_ + "\\" + directory_name;
	string command = "mkdir \"" + directory_name + "\"";
	if (system(command.c_str())) return false;

	return true;
}

bool Deserializator::DeserializeFile() {
	unsigned int length;
	//Read file length
	if (!inputStream_->ReadUnsignedInt32(length)) return false;
	string filename;
	//Read file name
	for (int i = 0; i < (int)length; i++) {
		char byte;
		if (!inputStream_->ReadByte(byte)) return false;
		filename += byte;
	}
	filename = output_ + "\\" + filename;

	WriteStream* write_stream = new FileWriteStream (filename);

	FileDecompressor* decompress = new HuffmanDecompressor(inputStream_, write_stream);
	decompress->DecompressFile();

	write_stream->Flush();
	delete write_stream;
	delete decompress;
	return true;
}

bool Deserializator::DeserializeDirectories() {

	// Make sure that the target base directory is empty.

	// Delete the target base directory.
	string command = "rmdir /S /Q \"" + output_ + "\" 2>null";
	system(command.c_str());

	// Create an empty target base directory.
	command = "mkdir \"" + output_ + "\"";
	system(command.c_str());
	
	unsigned int n;
	//Read the number of directories
	if (!inputStream_->ReadUnsignedInt32(n)) return false;

	//Read each directory
	for (int i = 0; i < (int)n; i++) {
		if (!DeserializeDirectory()) return false;
	}
	return true;
}

bool Deserializator::DeserializeFiles() {
	unsigned int n;
	//Read the number of files
	if (!inputStream_->ReadUnsignedInt32(n)) return false;
	//Read each file name
	for (int i = 0; i < (int)n; i++) 
	{
		if (!DeserializeFile()) return false;		
	}
	return true;
}

bool Deserializator::Deserialize()
{
	if (!DeserializeDirectories()) return false;
	if (!DeserializeFiles()) return false;
	return true;

}