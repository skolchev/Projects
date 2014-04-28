#include "FileWriteStream.h"

FileWriteStream::FileWriteStream(const string& filename) {
	this->filename_ = filename;
	this->buffer_ = new char[STREAM_BUFFER_SIZE];
	this->file_stream_.open(filename.c_str(), std::ofstream::binary);
	this->bit_index_ = 0;
	this->total_bits_ = STREAM_BUFFER_SIZE * 8;
}

FileWriteStream::~FileWriteStream() {
	file_stream_.close();
	delete[] buffer_;
}

bool FileWriteStream::WriteBit(char bit) {
	if (bit_index_ >= total_bits_) {
		file_stream_.write(buffer_, STREAM_BUFFER_SIZE);
		bit_index_ = 0;
	}
	char& byte = buffer_[bit_index_ >> 3];
	int bit_pos = 7 - (bit_index_ & 7);
	if (((byte >> bit_pos) & 1) != bit) {
		byte ^= (1 << bit_pos);
	}
	bit_index_++;
	return true;
}

bool FileWriteStream::WriteByte(char byte) {
	for (int i = 7; i >= 0; i--) {
		char bit = ((byte >> i) & 1);
		WriteBit(bit);
	}
	return true;
}

bool FileWriteStream::WriteUnsignedInt32(unsigned int value) {
	for (int i = 3; i >= 0; i--) {
		char byte = ((value >> (8 * i)) & 255);
		WriteByte(byte);
	}
	return true;
}

bool FileWriteStream::Flush() {
	unsigned int bytes = (bit_index_ + 7) / 8;
	file_stream_.write(buffer_, bytes);
	file_stream_.flush();
	bit_index_ = 0;
	delete [] buffer_;
	buffer_ = new char[STREAM_BUFFER_SIZE];
	return true;
}
