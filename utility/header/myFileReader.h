#ifndef MY_FILE_READER
#define MY_FILE_READER

#include <fstream>
#include <string>
#include "huffmanLibrary.h"

struct myFileReader
{
public:
	explicit myFileReader(std::string const& _fileName);
	myFileReader() = delete;
	~myFileReader();

	void open();
	void close();

	bool get(unsigned char& c);
	bool eof();

	bool failed() const;

	void changeFileName(std::string const& _fileName);

	std::string const& getName() const;

private:
	std::ifstream stream;
	std::string fileName;
	char* buffer;

	size_t curIndex;
	size_t endIndex;
	bool opened;

	bool isEOF();

};

#endif
