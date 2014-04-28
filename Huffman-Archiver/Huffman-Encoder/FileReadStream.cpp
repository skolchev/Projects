#include "FileReadStream.h"

FileReadStream::FileReadStream(const string& filename) {
	this->filename = filename;
	this->buffer_ = new char[STREAM_BUFFER_SIZE];
	this->file_stream_.clear();
	this->file_stream_.open(filename.c_str(), std::ifstream::binary);
	this->bit_index_ = 0;
	this->total_bits_ = 0;
}

FileReadStream::~FileReadStream() {
	file_stream_.close();
	delete[] buffer_;
}

bool FileReadStream::ReadBit(char& bit) {
	if (bit_index_ >= total_bits_) {
		file_stream_.read(buffer_, STREAM_BUFFER_SIZE);
		total_bits_ = (unsigned int)file_stream_.gcount() * 8;
		bit_index_ = 0;
		if (total_bits_ == 0) {
			return false;
		}
	}
	char byte = buffer_[bit_index_ >> 3];
	bit = ((byte >> (7 - (bit_index_ & 7))) & 1);
	bit_index_++;
	return true;
}

bool FileReadStream::ReadByte(char& byte) {
	byte = 0;
	for (int i = 7; i >= 0; i--) {
		char bit;
		if (!ReadBit(bit)) {
			return false;
		}
		if (bit) {
			byte |= (1 << i);
		}
	}
	return true;
}

bool FileReadStream::ReadUnsignedInt32(unsigned int& value) {
	value = 0;
	for (int i = 0; i < 4; i++) {
		char byte;
		if (!ReadByte(byte)) {
			return false;
		}
		value = (value << 8) | ((unsigned char)byte);
	}
	return true;
}

bool FileReadStream::Reset() {
	file_stream_.close();
	file_stream_.clear();
	file_stream_.open(filename.c_str(), std::ifstream::binary);
	bit_index_ = 0;
	total_bits_ = 0;
	return true;
}

unsigned int FileReadStream::Bytes() {
	Reset();
	unsigned int bytes = 0;
	while (true) {
		char byte;
		if (!ReadByte(byte)) {
			break;
		}
		bytes++;
	}
	return bytes;
}

void FileReadStream::RoundBitIndex()
{
	while (bit_index_ % 8 != 0)
	{
		bit_index_++;
	}
}