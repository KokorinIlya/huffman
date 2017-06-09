#include <cassert>
#include "codeWord.h"

CodeWord::CodeWord() : data(0), length(0) {}

CodeWord::CodeWord(CodeWord const& other) : data(other.data), length(other.length) {}

void CodeWord::operator=(CodeWord const& other)
{
	data = other.data;
	length = other.length;
}

void CodeWord::addBit(bool bit)
{
	data |= static_cast<unsigned long long>(bit) << (length++);
}

void CodeWord::removeBit()
{
	length--;
}

size_t CodeWord::getLength() const
{
	return length;
}

bool CodeWord::getBit(size_t index) const
{
	unsigned long long temp = 1ULL << index;
	unsigned long long res = data & temp;
	bool f = res != 0;
	return f;
}

unsigned char CodeWord::get8Bit(size_t index) const
{
	size_t ind8 = index << 3;
	return static_cast<unsigned char>((data >> ind8) & 255);
}

unsigned long long CodeWord::getCode() const
{
	return data;
}






