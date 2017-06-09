#ifndef MY_READER
#define MY_READER
#include <cstdint>
#include <vector>
#include "myFileReader.h"
#include "huffmanLibrary.h"
#include <cstdint>
#include <cstdlib>

void readTree(myFileReader& reader, std::vector<uint16_t>& tree);

void countFile(myFileReader& reader, Counter& counter);

void readInt16t(myFileReader& reader, uint16_t& x);

void readBlock(myFileReader& reader, std::vector<unsigned char>& block, size_t length);

bool readBlock(myFileReader& reader, std::vector<unsigned char>& block);

#endif

