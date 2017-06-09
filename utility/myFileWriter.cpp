#include "myFileWriter.h"
#include "workingWithFilesExceptions.h"
#include <iostream>
#include <cstdint>
#include <cstdlib>

myFileWriter::myFileWriter(std::string const& _fileName) : stream(),
fileName(_fileName),
buffer(static_cast<char *>(malloc(BUFFER_SIZE))),
curIndex(0),
opened(false) {}

void myFileWriter::flush()
{
	stream.write(buffer, curIndex);
}

void myFileWriter::put(unsigned char c)
{
	if (!opened)
	{
		throw fileNotOpenedException(fileName, "putting char in file");
	}
	if (curIndex == BUFFER_SIZE)
	{
		flush();
		curIndex = 0;
	}
	buffer[curIndex++] = static_cast<char>(c);
}

myFileWriter::~myFileWriter()
{
	close();
	free(buffer);
}

bool myFileWriter::failed() const
{
	return stream.fail();
}

void myFileWriter::open()
{
	if (opened)
	{
		close();
	}
	stream.open(fileName, std::ofstream::binary);
	if (stream.fail())
	{
		throw openFileException(fileName);
	}
	curIndex = 0;
	opened = true;
}

void myFileWriter::close()
{
	if (!opened)
	{
		return;
	}
	flush();
	opened = false;
	stream.close();
}

void myFileWriter::changeFileName(std::string const& _fileName)
{
	close();
	fileName = _fileName;
	curIndex = 0;
}

std::string const& myFileWriter::getName() const
{
	return fileName;
}




