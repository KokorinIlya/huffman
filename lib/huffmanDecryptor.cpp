#include "huffmanDecryptor.h"
#include "libraryExceptions.h"
#include <iostream>
#include "constantsAndTypes.h"
#include <cstdint>
#include <cstdlib>

using namespace std;

void huffmanDecryptor::makeTree(vector<uint16_t> const& prev)
{
	if (ready)
	{
		throw runtime_error("Decryptor already has been initialyzed with a tree");
	}
	if (prev.size() != TREE_SIZE)
	{
		throw incorrectFileException();
	}

	size_t edges = 0;
	for (size_t i = 0; i < prev.size(); i++)
	{
		uint16_t pr = prev[i];
		if (pr >= TREE_SIZE && pr != TREE_INF)
		{
			throw incorrectFileException();
		}

		if (pr == TREE_INF)
		{
			treeRoot = i;
			continue;
		}
		edges++;
		if (tree[pr].first == TREE_INF)
		{
			tree[pr].first = i;
		}
		else
		{
			if (tree[pr].second == TREE_INF)
			{
				tree[pr].second = i;
			}
			else
			{
				throw incorrectFileException();
			}
		}
	}

	if (prev[TREE_SIZE - 1] != TREE_INF)
	{
		throw incorrectFileException();
	}

	if (edges != TREE_SIZE - 1)
	{
		throw incorrectFileException();
	}

	for (size_t i = 0; i < COUNTER_SIZE; i++)
	{
		if (tree[i].first != TREE_INF || tree[i].second != TREE_INF)
		{
			throw incorrectFileException();
		}
	}

	for (size_t i = COUNTER_SIZE; i < TREE_SIZE; i++)
	{
		if (tree[i].first == TREE_INF || tree[i].second == TREE_INF)
		{
			throw incorrectFileException();
		}
	}

	vector <bool> used(TREE_SIZE, false);
	dfs(treeRoot, used);
	for (size_t i = 0; i < TREE_SIZE; i++)
	{
		if (!used[i])
		{
			throw incorrectFileException();
		}
	}
	ready = true;
	/*for (size_t i = 0; i < TREE_SIZE; i++)
	{
		cout << i << " " << tree[i].first << " " << tree[i].second << endl;
	}*/
}

bool getBit(unsigned char c, size_t index)
{
	unsigned char temp = 1 << index;
	unsigned char res = c & temp;
	bool f = res != 0;
	return f;
}

vector <unsigned char> huffmanDecryptor::decrypt(vector<unsigned char> const& block) const
{
	if (!ready)
	{
		throw noTreeException();
	}

	/*for (size_t i = 0; i < block.size(); i++)
	{
		cout << static_cast<size_t>(block[i]) << " ";
	}
	cout << endl << endl;*/

	int16_t currentVertex = treeRoot;

	vector <unsigned char> res;
	for (size_t i = 0; i < block.size(); i++)
	{
		unsigned char currentChar = block[i];
		for (size_t j = 0; j < 8; j++)
		{
			if (!getBit(currentChar, 7 - j))
			{
				currentVertex = tree[currentVertex].first;
			}
			else
			{
				currentVertex = tree[currentVertex].second;
			}
			if (currentVertex < COUNTER_SIZE)
			{
				res.push_back(static_cast<unsigned char>(currentVertex));
				currentVertex = treeRoot;
			}
		}
	}
	/*for (size_t i = 0; i < res.size(); i++)
	{
		cout << static_cast<size_t>(res[i]) << " ";
	}*/
	return res;
}

void huffmanDecryptor::dfs(uint16_t v, std::vector<bool>& used)
{
	used[v] = true;
	if (v < COUNTER_SIZE)
	{
		return;
	}
	dfs(tree[v].first, used);
	dfs(tree[v].second, used);
}



huffmanDecryptor::huffmanDecryptor() : 
		treeRoot(TREE_INF), 
		tree(TREE_SIZE, {TREE_INF, TREE_INF}),
		ready(false) {}
