#ifndef LIBRARY_EXCEPTIONS
#define LIBRARY_EXCEPTIONS
#include <stdexcept>
#include <cstdint>
#include <cstdlib>

struct incorrectFileException : std::runtime_error
{
	incorrectFileException() : runtime_error("Compressed file is damaged or was compressed not by this program") {}
};

struct noTreeException : std::runtime_error
{
	noTreeException() : runtime_error("Decryptor doesn't have a tree to decrypt") {}
};

#endif