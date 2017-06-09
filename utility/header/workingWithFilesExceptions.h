#ifndef WORKING_WITH_FILES_EXCEPTIONS
#define WORKING_WITH_FILES_EXCEPTIONS
#include <stdexcept>
#include <string>
#include <cstdint>
#include <cstdlib>

struct openFileException : std::runtime_error
{
	openFileException(std::string const& fileName) : runtime_error("Cannot open file " + fileName + ", try to open another file") {}
};

struct fileNotOpenedException : std::runtime_error
{
	fileNotOpenedException(std::string const& fileName, std::string const& action) : 
		runtime_error("File " + fileName + " is not opened, cannot perform " + action) {}
};

struct fileEndedException : std::runtime_error
{
	fileEndedException(std::string const& fileName) : runtime_error("File " + fileName + " is ended, cannot perform reading") {}
};

struct smallBlockException : std::runtime_error
{
	smallBlockException(uint16_t length) : runtime_error("Block is too small, it's size is less than " + length) {}
};
#endif
