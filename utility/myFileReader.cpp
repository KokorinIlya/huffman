#include "myFileReader.h"
#include "workingWithFilesExceptions.h"
#include <iostream>

myFileReader::myFileReader(std::string const& _fileName) : stream(),
fileName(_fileName),
buffer(static_cast<char*>(malloc(BUFFER_SIZE))),
curIndex(0),
endIndex(0),
opened(false)
{}

myFileReader::~myFileReader()
{
	free(buffer);
	close();
}

void myFileReader::open()
{
	if (opened)
	{
		stream.close();
	}
	stream.open(fileName, std::ifstream::binary);
	if (stream.fail())
	{
		throw openFileException(fileName);
	}
	curIndex = 0;
	endIndex = 0;
	opened = true;
}

void myFileReader::close()
{
	if (!opened)
	{
		return;
	}
	opened = false;
	stream.close();
}


bool myFileReader::failed() const
{
	return stream.fail();
}

bool myFileReader::isEOF()
{
	return stream.peek() == EOF;
}


bool myFileReader::eof()
{
	if (!opened)
	{
		throw fileNotOpenedException(fileName, "checking end of file");
	}
	return	curIndex == endIndex && isEOF();
}


bool myFileReader::get(unsigned char& c)
{
	if (!opened)
	{
		throw fileNotOpenedException(fileName, "reading chars from file");
	}
	if (curIndex == endIndex)
	{
		if (isEOF())
		{
			return false;
		}
		curIndex = 0;
		stream.read(buffer, BUFFER_SIZE);
		endIndex = static_cast<size_t>(stream.gcount());
	}
	c = static_cast<unsigned char>(buffer[curIndex++]);
	return true;
}

void myFileReader::changeFileName(std::string const& _fileName)
{
	close();
	fileName = _fileName;
	curIndex = 0;
	endIndex = 0;
}

std::string const& myFileReader::getName() const
{
	return fileName;
}
