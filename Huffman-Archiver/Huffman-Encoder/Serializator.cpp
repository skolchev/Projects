#include "Serializator.h"
#include "FileReadStream.h"
#include "FileDispatcher.h"
#include <vector>
#include <string>

Serializator::Serializator(std::string input, WriteStream* output, FileCompressor* compressor)
{
	this->input_ = input;
	this->output_ = output;
	this->compressor_ = compressor;
}

Serializator::~Serializator()
{
	delete output_;
	delete compressor_;
}
void Serializator::Serialize()
{
	/*
		1. Get directories and folders recursively
		2. Serialize folders tree
			- Serialize each folder: N - number of characters for name; 1....N bytes
		3. Serialize files
			- Serialize each file: N - number of characters for name; 1.....N bytes; CompressFile method
	*/

	std::vector<std::string> filesAndFolders;
	std::vector<std::string> files;
	std::vector<std::string> folders;
	FileDispatcher::TraverseDirectoryRecursively(filesAndFolders, input_);
	for (int i = 0; i < filesAndFolders.size(); i++)
	{
		std::string result = FileDispatcher::StripBasePath(filesAndFolders[i], FileDispatcher::StripLastPathComponent(input_));
		if (FileDispatcher::IsFile(filesAndFolders[i]))
		{
			files.push_back(result);
		}
		else
		{
			folders.push_back(result);
		}
	}

	// Write folders tree
	unsigned int numberOfFolders = folders.size();
	output_->WriteUnsignedInt32(numberOfFolders);

	for (int i = 0; i < numberOfFolders; i++)
	{
		unsigned int folderNameLength = folders[i].size();
		std::string folderName = folders[i];

		output_->WriteUnsignedInt32(folderNameLength);
		for (int j = 0; j < folderNameLength; j++)
		{
			output_->WriteByte(folderName[j]);
		}
	}


	// Write files
	unsigned int numberOfFiles = files.size();
	output_->WriteUnsignedInt32(numberOfFiles);

	for (std::vector<std::string>::iterator it = files.begin();
		it != files.end(); ++it)
	{
		std::string fileName(*it);
		std::string fullPath = FileDispatcher::StripLastPathComponent(input_) + fileName;
		FileReadStream* input = new FileReadStream(fullPath);

		// Write file name length
		unsigned int fileNameLength = (*it).size();
		output_->WriteUnsignedInt32(fileNameLength);

		// Write file name
		for (int i = 0; i < fileName.size(); i++)
		{
			output_->WriteByte(fileName[i]);
		}

		compressor_->SetReadStream(input);
		compressor_->CompressFile();
	}
}