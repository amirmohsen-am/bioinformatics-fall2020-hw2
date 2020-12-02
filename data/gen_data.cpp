#include <iostream>
#include <string>
#include <vector>
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

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Please provide n and q (number of queries)" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int q = atoi(argv[2]);
    vector <string> keys = gen_strings(n);

    cout << n << endl;
    for (auto key: keys)
        cout << key << " ";
    cout << endl;
    cout << q << endl;
    while (q--)
        // for normal queries
        cout << keys[rand()%n] << " ";
        // for alien keys queries
//        cout << rand_str(20) << " ";
    cout << endl;
}
