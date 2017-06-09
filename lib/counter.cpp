#include <cassert>
#include <iostream>
#include "counter.h"
#include "constantsAndTypes.h"

Counter::Counter() : counter(COUNTER_SIZE) {}

void Counter::addNewChars(std::vector<unsigned char> const& block)
{
	for (size_t i = 0; i < block.size(); i++)
	{
		++counter[block[i]];
	}
}

unsigned long long Counter::getCount(size_t i) const
{
	assert(0 <= i && i < COUNTER_SIZE);
	return counter[i];
}

