#ifndef HUFFMAN_ENCRYPTER
#define HUFFMAN_ENCRYPTER

#include "counter.h"
#include "codeWord.h"
#include <cstdint>
#include <cstdlib>

struct huffmanEncryptor
{
public:
	huffmanEncryptor(Counter const& counter);
	huffmanEncryptor() = delete;

	std::vector <uint16_t> const& getTree() const;

	std::vector <unsigned char> encrypt(std::vector <unsigned char> const& symbols) const;

private:
	size_t treeRoot;
	std::vector <uint16_t> tree;
	std::vector <CodeWord> codes;

	void makeCodesByDfs(uint16_t v, std::vector <std::pair <uint16_t, uint16_t > > &tree, CodeWord curCode);

};

#endif
