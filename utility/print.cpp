#include  "print.h"
#include <vector>
#include <iostream>
#include "workingWithFilesExceptions.h"

using namespace std;

vector <unsigned char> int16ToUnsignedChar(uint16_t x)
{
	vector <unsigned char> res(2);
	for (size_t i = 0; i <= 1; i++)
	{
		res[i] = static_cast<unsigned char> ((x >> ((1 - i) * 8)) & 255);
	}
	return res;
}

vector <unsigned char> treeToVector(huffmanEncryptor const& encryptor)
{
	vector <uint16_t> const& tree = encryptor.getTree();
	vector <unsigned char> temp(TREE_SIZE * 2);
	size_t curIndex = 0;
	for (size_t i = 0; i < tree.size(); i++)
	{
		//cout << i << ", " << tree[i] << ": ";
		vector <unsigned char> res = int16ToUnsignedChar(tree[i]);
		for (size_t j = 0; j < res.size(); j++)
		{
			temp[curIndex++] = res[j];
		}
		/*for (size_t j = 0; j < res.size(); j++)
		{
		cout << static_cast<size_t>(res[j]) << " ";
		}
		cout << endl << endl;*/
	}
	return temp;
}

void printTree(myFileWriter& writer, huffmanEncryptor const& encryptor)
{
	vector <unsigned char> treetoWrite = treeToVector(encryptor);
	for (size_t i = 0; i < treetoWrite.size(); i++)
	{
		writer.put(treetoWrite[i]);
	}
}

void printInt16t(myFileWriter& writer, uint16_t x)
{
	vector <unsigned char> toWrite = int16ToUnsignedChar(x);
	writer.put(toWrite[0]);
	writer.put(toWrite[1]);
}

void printBlock(myFileWriter& writer, vector<unsigned char> const& block)
{
	for (size_t i = 0; i < block.size(); i++)
	{
		writer.put(block[i]);
	}
}

void printBlock(myFileWriter& writer, vector<unsigned char> const& block, size_t length)
{
	if (length > block.size())
	{
		throw smallBlockException(length);
	}
	for (size_t i = 0; i < length; i++)
	{
		writer.put(block[i]);
	}
}

void encryptAndWriteBlock(myFileWriter& writer, huffmanEncryptor const& encryptor, vector<unsigned char> const& block)
{
	uint16_t needSize = block.size();
	vector <unsigned char> encryptedBlock = encryptor.encrypt(block);
	uint16_t blockSize = encryptedBlock.size();
	printInt16t(writer, blockSize);
	printInt16t(writer, needSize);
	printBlock(writer, encryptedBlock);
}
