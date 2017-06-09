#ifndef CODE_WORD
#define CODE_WORD

struct CodeWord
{
public:
	CodeWord();
	CodeWord(CodeWord const& other);
	void operator=(CodeWord const& other);

	void addBit(bool bit);
	void removeBit();

	size_t getLength() const;

	bool getBit(size_t index) const;
	unsigned char get8Bit(size_t index) const;
	unsigned long long getCode() const;

private:
	unsigned long long data;
	size_t length;
};

#endif

