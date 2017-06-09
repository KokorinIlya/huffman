#include <set>
#include <iostream>
#include <cassert>
#include "huffmanEncryptor.h"
#include "constantsAndTypes.h"

using namespace std;

struct Node
{
	unsigned long long count;
	uint16_t index;

	Node(unsigned long long _count, size_t _index) : count(_count), index(_index) {}

	bool operator <(const Node& other) const
	{
		if (count == other.count)
		{
			return index < other.index;
		}
		return count < other.count;
	}
};

Node getAndDeleteMin(set <Node>& from)
{
	Node res = *(from.begin());
	from.erase(from.begin());
	return res;
}

void huffmanEncryptor::makeCodesByDfs(uint16_t v, std::vector<std::pair<uint16_t, uint16_t>>& tree, CodeWord curCode)
{
	if (v < COUNTER_SIZE)
	{
		codes[v] = curCode;
		return;
	}

	CodeWord newCode(curCode);

	newCode.addBit(false);
	makeCodesByDfs(tree[v].first, tree, newCode);
	newCode.removeBit();

	newCode.addBit(true);
	makeCodesByDfs(tree[v].second, tree, newCode);
	newCode.removeBit();
}


huffmanEncryptor::huffmanEncryptor(const Counter& counter) : treeRoot(TREE_INF), tree(TREE_SIZE, TREE_INF), codes(COUNTER_SIZE)
{
	vector <pair <uint16_t, uint16_t> > treeBySons(TREE_SIZE, {TREE_INF, TREE_INF});

	set <Node> encryptor;
	for (uint16_t i = 0; i < COUNTER_SIZE; i++)
	{
		//cout << counter.getCount(i) << " ";
		encryptor.insert(Node(counter.getCount(i), i));
	}
	uint16_t index = COUNTER_SIZE;
	while (encryptor.size() > 1)
	{
		Node nodeFirst = getAndDeleteMin(encryptor);
		Node nodeSecond = getAndDeleteMin(encryptor);
		size_t leftIndex = nodeFirst.index;
		size_t rightIndex = nodeSecond.index;
		if (leftIndex > rightIndex)
		{
			swap(leftIndex, rightIndex);
		}
		tree[leftIndex] = index;
		tree[rightIndex] = index;
		treeBySons[index] = { leftIndex, rightIndex };
		encryptor.insert(Node(nodeFirst.count + nodeSecond.count, index++));
	}
	treeRoot = encryptor.begin()->index;
	CodeWord start;
	makeCodesByDfs(treeRoot, treeBySons, start);
	/*cout << endl;
	for (size_t i = 0; i < codes.size(); i++)
	{
		cout << codes[i].getCode() << " " << codes[i].getLength() << endl;
	}*/
	/*cout << endl << endl;
	cout << treeRoot << endl;
	for (size_t i = 0; i < tree.size(); i++)
	{
		cout << i << " - " << tree[i] << endl;
	}*/
}

vector <uint16_t> const& huffmanEncryptor::getTree() const
{
	return tree;
}

void addBit(unsigned char& c, bool f, size_t index)
{
	c |= static_cast<unsigned char>(f) << index;
}

vector <unsigned char> huffmanEncryptor::encrypt(vector<unsigned char> const& symbols) const
{
	vector <unsigned char> temp;
	unsigned char curChar = 0;
	size_t curIndex = 0;
	for (size_t i = 0; i < symbols.size(); i++)
	{
		CodeWord curCode = codes[symbols[i]];
		for (size_t j = 0; j < curCode.getLength(); j++)
		{
			if (curIndex == 8)
			{
				temp.push_back(curChar);
				curChar = 0;
				curIndex = 0;
			}
			addBit(curChar, curCode.getBit(j), 7 - curIndex);
			curIndex++;
		}
	}
	temp.push_back(curChar);
	/*for (size_t i = 0; i < temp.size(); i++)
	{
		cout << static_cast<size_t>(temp[i]) << " ";
	}
	cout << endl << 8 - curIndex << endl;*/
	return temp;
}
