#include "read.h"
#include "workingWithFilesExceptions.h"
#include <iostream>
#include <cassert>

using namespace  std;

void readTree(myFileReader& reader, vector<uint16_t>& tree)
{
	assert(tree.size() == TREE_SIZE);
	vector <unsigned char> treeChar(2 * TREE_SIZE);
	for (size_t i = 0; i < 2 * TREE_SIZE; i++)
	{
		reader.get(treeChar[i]);
	}
	for (size_t i = 0; i < TREE_SIZE; i++)
	{
		tree[i] = treeChar[2 * i] * 256 + treeChar[2 * i + 1];
	}
}

void countFile(myFileReader& reader, Counter& counter)
{
	vector <unsigned char> block;
	unsigned char c;
	while (reader.get(c))
	{
		if (block.size() == BLOCK_SIZE)
		{
			//cerr << "NEW BLOCK! \n";
			counter.addNewChars(block);
			block.clear();
		}
		block.push_back(c);
	}
	counter.addNewChars(block);
}

void readInt16t(myFileReader& reader, uint16_t& x)
{
	unsigned char old, young;
	reader.get(old);
	reader.get(young);
	x = (static_cast<uint16_t>(old) << 8) + young;
}

void readBlock(myFileReader& reader, vector<unsigned char>& block, size_t length)
{
	if (length > block.size())
	{
		throw smallBlockException(length);
	}
	for (size_t i = 0; i < length; i++)
	{
		if (reader.eof())
		{
			throw fileEndedException(reader.getName());
		}
		reader.get(block[i]);
	}
}

bool readBlock(myFileReader& reader, vector<unsigned char>& block)
{
	unsigned char c;
	while (reader.get(c))
	{
		block.push_back(c);
		if (block.size() == BLOCK_SIZE)
		{
			return true;
		}
	}
	return false;
}

