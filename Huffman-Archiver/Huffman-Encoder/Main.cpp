// A small driver program that demonstrates the Huffman encoding API.#include <iostream>

#include <fstream>
#include <string>
#include "FileDispatcher.h"
#include "HuffmanEncoder.h"
#include "HuffmanCompressor.h"
#include "FileReadStream.h"
#include "FileWriteStream.h"
#include "Serializator.h"
#include "Deserializator.h"
#include "HuffmanDecompressor.h"
#include <map>

int main(int argc, char* argv[]) {
	std::string inputPath = "C:\\Users\\Milen\\Desktop\\Sample";
	std::string outputPath = "C:\\Users\\Milen\\Desktop\\Archive\\testArchive_arch";
	ReadStream* read = new FileReadStream(inputPath);
	WriteStream* write = new FileWriteStream(outputPath);
	HuffmanCompressor* compressor = new HuffmanCompressor(read, write);
	Serializator serialization(inputPath, write, compressor);
	serialization.Serialize();

	std::string sampleOutput = "C:\\Users\\Milen\\Desktop\\SampleOutput";
	Deserializator deserialization(outputPath, sampleOutput);
	deserialization.Deserialize();
	// Verification for correct given absolute or relative directory to the program
	std::string err_message = "Please enter a valid directory!";

	//if (argc != 4)
	//{
	//	std::cerr << err_message << std::endl;
	//	return 1;
	//}

	//if (!FileDispatcher::IsValid(argv[2]) && !FileDispatcher::IsValid(argv[3]))
	//{
	//	std::cerr << err_message << std::endl;
	//	return 1;
	//}

	//std::string firstParam = argv[1];
	//if (firstParam == "compress")
	//{
	//	ReadStream* read = new FileReadStream(argv[2]);
	//	std::string archiveName = argv[3];
	//	archiveName += "_arch";
	//	WriteStream* write = new FileWriteStream(archiveName);
	//	HuffmanCompressor* compressor = new HuffmanCompressor(read, write);
	//	Serializator serialization(argv[2], write, compressor);
	//	serialization.Serialize();
	//}
	//else if (firstParam == "decompress")
	//{
	//	Deserializator deserialization(argv[2], argv[3]);
	//	deserialization.Deserialize();
	//}

}