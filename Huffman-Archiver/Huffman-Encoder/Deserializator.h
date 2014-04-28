// A class for a file deserialization
#ifndef DESERIALIZATOR_H 
#define DESERIALIZATOR_H

#include "FileReadStream.h"
#include "FileWriteStream.h"
#include "FileDecompressor.h"
#include <string>

class Deserializator
{
public:
	/**
	* The constructor takes two strings. First for input path (the path to the archived file)
	* and second for output path (the path where you want to unzip the file).
	*/
	Deserializator(std::string, std::string);
	/**
	* Destructor to clean up dynamiclly allocated memory for inputStream_.
	*/
	~Deserializator();
	/**
	* The base function of the class. Deserializes the archive into folders and files.
	* @sa bool DeserializeFile();
	* @sa	bool DeserializeFiles();
	* @sa	bool DeserializeDirectories();
	* @sa	bool DeserializeDirectory();
	*/
	bool Deserialize();
private:
	std::string input_; ///< The path to the archived file.
	std::string output_; ///< The path wheer you want to unzip the file.
	ReadStream* inputStream_; ///< iostream to read through the file.
	bool DeserializeFile(); ///< The function returns true if the file has been deserialized correctly.
	bool DeserializeFiles(); ///< The function returns true if all the files have been deserialized correctly.
	bool DeserializeDirectories(); ///< The function returns true if the directories have been deserialized correctly.
	bool DeserializeDirectory(); ///< The function returns true if the directory has been deserialized correctly.
};
#endif