#include "myFileReader.h"
#include <iostream>
#include "myFileWriter.h"
#include "workingWithFilesExceptions.h"
#include <vector>
#include "print.h"
#include "read.h"

#include "huffmanLibrary.h"
#include <ctime>
#include <cstring>
#include <string>
#include <cstdint>
#include <cstdlib>

using namespace std;

void sayHelp()
{
	cout << "Unknown command. Please, use this commands:\n";
	cout << "utility -compress fileFrom fileTo\n";
	cout << "utility compress fileFrom fileTo\n";
	cout << "utility -decompress fileFrom fileTo\n";
	cout << "utility decompress fileFrom fileTo\n";
}

int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		string command = argv[1];
		string fileFrom = argv[2];
		string fileTo = argv[3];
		if (command == "compress" || command == "-compress")
		{
			unsigned long long t1 = clock();
			std::cout << "Start compression\n";
			myFileReader reader(fileFrom);
			myFileWriter writer(fileTo);

			std::cout << "Start counting\n";
			try
			{
				reader.open();
			}
			catch (runtime_error e)
			{
				std::cerr << e.what() << "\n";
				return 1;
			}
			Counter counter;
			countFile(reader, counter);
			reader.close();
			std::cout << "Finished counting\n";

			huffmanEncryptor encryptor(counter);

			try
			{
				reader.open();
				writer.open();
			}
			catch (runtime_error e)
			{
				std::cerr << e.what() << "\n";
				return 1;
			}

			std::cout << "Printing tree\n";
			printTree(writer, encryptor);
			std::cout << "Printed tree\n";

			std::cerr << "Compressing...\n";
			while (!reader.eof())
			{
				//cerr << countBlocks << "\n";
				vector <unsigned char> block;
				while (readBlock(reader, block))
				{
					encryptAndWriteBlock(writer, encryptor, block);
					block.clear();
				}
				encryptAndWriteBlock(writer, encryptor, block);
			}
			reader.close();
			writer.close();
			std::cout << "Finish!\n";
			unsigned long long t2 = clock();
			std::cout << "Time is " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << "\n";
		}
		 else if (command == "decompress" || command == "-decompress")
		{
			unsigned long long t1 = clock();
			std::cout << "Start decompression\n";
			myFileReader reader(fileFrom);
			myFileWriter writer(fileTo);

			std::cout << "Start reading tree\n";
			vector<uint16_t> tree(TREE_SIZE);

			try
			{
				reader.open();
			}
			catch (runtime_error e)
			{
				std::cerr << e.what() << "\n";
				return 1;
			}
			readTree(reader, tree);

			huffmanDecryptor decryptor;

			try
			{
				decryptor.makeTree(tree);
			}
			catch (runtime_error e)
			{
				std::cerr << e.what() << "\n";
				return 1;
			}
			std::cout << "Finished reading tree\n";

			std::cout << "Decompressing...\n";
			try
			{
				writer.open();
			}
			catch (runtime_error e)
			{
				std::cerr << e.what() << "\n";
				return 1;
			}
			bool error = false;
			while (!reader.eof())
			{
				uint16_t blockSize, needSize;
				readInt16t(reader, blockSize);
				readInt16t(reader, needSize);
				vector <unsigned char> block(blockSize);
				try
				{
					readBlock(reader, block, blockSize);
				}
				catch (runtime_error e)
				{
					std::cerr << e.what() << "\n";
					error = true;
					break;
				}
				vector <unsigned char> decryptedBlock = decryptor.decrypt(block);

				try
				{
					printBlock(writer, decryptedBlock, needSize);
				}
				catch (runtime_error e)
				{
					std::cerr << e.what() << "\n";
					error = true;
					break;
				}
			}
			if (error)
			{
				return 1;
			}
			reader.close();
			writer.close();
			std::cout << "Finish!\n";
			unsigned long long t2 = clock();
			std::cout << "Time is " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << "\n";
		}
		else
		{
			sayHelp();
		}
	}
	else
	{
		sayHelp();
	}
	return 0;
}
/*
18
0
0
7
6
5
6
7
1
2
3
2
1
0
0
3
3
7
6
*/