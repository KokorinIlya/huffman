#ifndef COUNTER
#define COUNTER
#include <vector>
#include <cstdint>
#include <cstdlib>

struct Counter
{
public:
	Counter();

	void addNewChars(std::vector<unsigned char> const& block);

	unsigned long long getCount(size_t i) const;

private:
	std::vector <unsigned long long> counter;
};
#endif