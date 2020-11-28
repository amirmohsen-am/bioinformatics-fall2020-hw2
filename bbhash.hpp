#include <sdsl/rank_support_v.hpp>
#include <vector>
#include "xxhash.h"
#include <time.h>

using namespace std;
using namespace sdsl;

typedef uint64_t size_type;

template <class KeyType> 
class bb_level
{
	public:
	size_type size;
	size_type seed;
	bit_vector A;
	bit_vector C;
	
	rank_support_v<1> r;
	

	// DEBUG
	vector <KeyType> keys;

	vector<KeyType> init(vector<KeyType> keys, size_type gamma)
	{
		this->size = keys.size() * gamma;
		this->seed = rand(); // TODO
		A = bit_vector(size, 0);
		C = bit_vector(size, 0);

		this->keys = keys;

		vector<KeyType> collisions;


		for (auto key: keys)
		{
			size_type i = get_hash(key);
//			cerr << i << endl;
			if (A[i] == 0 && C[i] == 0)
				A[i] = 1;
			else if (A[i] == 1) 
			{
				assert (C[i] == 0);
				A[i] = 0;
				C[i] = 1;
			}
		}
		for (auto key: keys)
		{
			size_type i = get_hash(key) % size;
			if (C[i] == 1)
				collisions.push_back(key);
		}
		//util::init_support(r, &A);


		r = rank_support_v<1>(&A);

		return collisions;

	}


	size_type get_hash(KeyType key) // hash % size
	{
		ostringstream o;
		o << key;
		string s = o.str();

		XXH64_hash_t hash = XXH64(s.c_str(), s.size(), seed);	
		return hash % size;
	}

	size_type weight()
	{
		cerr << A << endl;
		cerr << r.size() << endl;
		cerr << r.rank(0) << endl;
		cerr << r.rank(1) << endl;
		cerr << r.rank(2) << endl;
		cerr << r.rank(3) << endl;
		cerr << r.rank(4) << endl;
		rank_support_v<1> tt(&A);

		cerr << tt.rank(0) << endl;
		cerr << tt.rank(1) << endl;
		cerr << tt.rank(2) << endl;
		cerr << tt.rank(3) << endl;
		cerr << tt.rank(4) << endl;
		return r.rank(size-1);
	}

	
};

//	
template <class KeyType>
class bbhash
{
	public:
	size_type gamma;
	size_type n;
	vector<KeyType> keys;

	vector<bb_level<KeyType> > level;
	

	bbhash(vector <KeyType> keys, size_type gamma)
	{
		//srand(time(NULL));
		n = keys.size();
//		this->keys = keys;
		this->gamma = gamma;

		assert (n > 0);

		vector <KeyType> collisions = keys;
		while (!collisions.empty())
		{
			//level.resize(level.size()+1);
			level.push_back(bb_level<KeyType>());
			collisions = level.back().init(collisions, gamma);
			cerr << "D" << level.back().r.size() << endl;
			//for (size_t k = 0; k < level.size(); k++)
			//	cerr << "X" << level[k].r.size() << endl;
		}

		cerr << level.size() << endl;
		for (auto l: level)
		{
			cerr << l.keys.size() << " ";
			for(auto key: l.keys) 
				cerr << key << " ";
			cerr << endl;
		}
		
	}

	size_type get(KeyType key)
	{
		size_type sum = 0;
		for (size_t i = 0; i < level.size(); i++)
		{
			size_type ind = level[i].get_hash(key);
			cerr << "ind: " << ind << endl;
			cerr << i << " " << ind << " " << level[i].A.size() << " " << level[i].r.size() << endl;
			if (level[i].A[ind] == 1)
			{
				return sum + level[i].r.rank(ind);
			}
			sum += level[i].weight();
		}
		cerr << "Key not found" << endl;
		return sum;
	}

};

