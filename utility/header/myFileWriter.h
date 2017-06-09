#ifndef MY_FILE_WRITER
#define MY_FILE_WRITER

#include <fstream>
#include <string>
#include "huffmanLibrary.h"

struct myFileWriter
{
public:
	explicit myFileWriter(std::string const& _fileName);
	myFileWriter() = delete;
	~myFileWriter();

	void put(unsigned char c);

	void open();
	void close();

	void flush();

	bool failed() const;

	void changeFileName(std::string const& _fileName);

	std::string const& getName() const;

private:
	std::ofstream stream;
	std::string fileName;
	char* buffer;

	size_t curIndex;
	bool opened;
};
#endif