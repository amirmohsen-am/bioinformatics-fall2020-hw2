#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int n; cin >> n;
    vector <string> keys(n);

    for(int i = 0; i < n; i++)
        cin >> keys[i];

    unordered_map<string, uint64_t> hash;

    for (auto key: keys)
    {
        if (hash.find(key) == hash.end())
        {
            int sz = hash.size();
            hash[key] = sz;
        }
    }

    int q; cin >> q;
    int sum = 0;
    while(q--)
    {
        string key; cin >> key;
        sum += hash[key];
    }
    long long oh = 0;

    for (auto it: hash)
        oh += it.first.size() + sizeof(uint64_t);
    cout << "overhead: " << oh << endl;
    cout << "sum of hashes: " << sum << endl;


}
