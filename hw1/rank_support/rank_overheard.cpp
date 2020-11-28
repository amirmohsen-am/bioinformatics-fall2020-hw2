#include <iostream>
#include "rank_support.hpp"

using namespace std;

int main()
{
	uint64_t n = 1ull << 62;
//	for (uint64_t i = 100, cnt = 0; i < n, cnt < 100; i += 1000000, cnt++)
	for (uint64_t i = 10, cnt = 0; i < n, cnt < 15; i*= 4, cnt++)
	{	
		cout << i << " " << hypo_overhead(i) << endl;
	}
	return 0;
}
