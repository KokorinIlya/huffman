#ifndef MY_PRINTERS
#define MY_PRINTERS
#include <vector>
#include "myFileWriter.h"
#include "huffmanLibrary.h"

void printTree(myFileWriter& writer, huffmanEncryptor const& encryptor);

void printInt16t(myFileWriter& writer, uint16_t x);

void printBlock(myFileWriter& writer, std::vector<unsigned char> const& block);

void printBlock(myFileWriter& writer, std::vector<unsigned char> const& block, size_t length);

void encryptAndWriteBlock(myFileWriter& writer, huffmanEncryptor const& encryptor, std::vector<unsigned char> const& block);

#endif
