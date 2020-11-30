#include <iostream>
#include "bbhash.hpp"
#include "xxhash.h"
//#include <sdsl/rank_support_v.hpp>

using namespace std;
//using namespace sdsl;

string rand_str(int len = 30)
{
    string res;
    for (int i = 0; i < len; i++)
        res += rand()%26 + 'a';
    return res;
}

vector <string> gen_strings(int n)
{
    vector <string> res;
    for (int i = 0; i < n; i++)
        res.push_back(rand_str());
    return res;
}

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

/*
	vector <string> keys = {"a", "b", "c", "d", "WHY", "HA"};
	bbhash<string> bb(keys, 1);

	
	for (auto key: keys)
	{
		cerr << key << " " << bb.get(key) << endl;
	}
	cerr << bb.get("hiii");
 */
    vector <string> keys = gen_strings(1000);
    bbhash<string> bb(keys, 1);
    bb.print();

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
