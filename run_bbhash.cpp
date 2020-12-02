#include <iostream>
#include "bbhash.hpp"
#include "xxhash.h"
//#include <sdsl/rank_support_v.hpp>

using namespace std;
//using namespace sdsl;



int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Provide gamma" << endl;
        return -1;
    }
    double gamma = atof(argv[1]);
    int n; cin >> n;
    vector <string> keys(n);

    for(int i = 0; i < n; i++)
        cin >> keys[i];

    bbhash<string> bb(keys, gamma);

    int q; cin >> q;
    int sum = 0;
    int alien = 0;
    while (q--)
    {
        string key; cin >> key;
        size_type res = bb.get(key);
        cout << res << "\n";
        if (res == keys.size())
            alien++;
    }

    bb.print();
    cout << "Alien keys: " << alien << endl;
//    cout << "Sum of hashes: " << sum << endl;


}
