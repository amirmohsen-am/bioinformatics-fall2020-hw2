//
// Created by AmirMohsen Ahanchi on 12/1/20.
//

#include <iostream>
#include "bbhash.hpp"
#include "xxhash.h"
//#include <sdsl/rank_support_v.hpp>

using namespace std;

int main()
{


    /*
    bit_vector b = bit_vector(8000, 0);
    for (size_t i=0; i < b.size(); i+=100)
        b[i] = 1;
    rank_support_v<1> b_rank(&b); // <- pointer to b
    for (size_t i=0; i<=b.size(); i+= b.size()/4)
        cout << "(" << i << ", " << b_rank(i) << ") ";
        */


	vector <string> keys = {"a", "b", "c", "d", "WHY", "HA"};
	bbhash<string> bb(keys, 1);

	bb.print();

	for (auto key: keys)
	{
		cout << key << " " << bb.get(key) << endl;
	}
	cout << bb.get("hiii") << endl;

//	vector <int> keys = {1, 1, 2};
//	bbhash<int> bb(keys, 10);
//	int x = 1;
//	XXH64_hash_t hash = XXH64((char *)(&x), sizeof(x), 1);
//	cout << hash << endl;

    /*
    char s[] = "abc";
    XXH64_hash_t hash = XXH64((char *)(s), 3, 1);
    cout << hash << endl;
    */


}
