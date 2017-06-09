#ifndef HUFFMAN_DECRYPTOR
#define HUFFMAN_DECRYPTOR
#include <vector>
#include <cstdint>
#include <cstdlib>

struct huffmanDecryptor
{
public:
	huffmanDecryptor();
	void makeTree(std::vector <uint16_t> const& prev);
	std::vector <unsigned char> decrypt(std::vector<unsigned char> const&) const;

private:
	size_t treeRoot;
	std::vector <std::pair <uint16_t, uint16_t> > tree;
	bool ready;

	void dfs(uint16_t v, std::vector <bool> &used);
};

#endif
