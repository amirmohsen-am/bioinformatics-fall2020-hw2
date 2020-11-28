//#include <sdsl/rank_support_v.hpp>
#include <vector>
#include "xxhash.h"
#include <time.h>
#include "hw1/rank_support/rank_support.hpp"

using namespace std;
//using namespace sdsl;

typedef uint64_t size_type;

template <class KeyType> 
class bbhash;

template <class KeyType> 
class bb_level
{
	public:
	size_type size;
	size_type seed;
	bit_vector A;
	bit_vector C;
	
	rank_support *r;
	

	// DEBUG
	vector <KeyType> keys;
	
//	bbhash *bb;

	bb_level()
	{
	    size = seed = 0;
	    r = NULL;
		return;
	}

	vector<KeyType> init(vector<KeyType> keys, size_type gamma)
	{
		this->size = keys.size() * gamma;
		this->seed = rand(); // TODO

		size_type sz = size;
		if (size < 4)
			sz = 4;
		A = bit_vector(sz, 0);
		C = bit_vector(sz, 0);

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
			size_type i = get_hash(key)% size;
			if (C[i] == 1)
				collisions.push_back(key);
		}
		//util::init_support(r, &A);

		cerr << "T" << A << endl;
		r = new rank_support(&A);
		cerr << "T" << (*r->b) << endl;
//		cerr << "T" << (*r.b) << endl;

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
		/*
		cerr << A << endl;
		cerr << r.size() << endl;
		cerr << r.rank(0) << endl;
		cerr << r.rank(1) << endl;
		cerr << r.rank(2) << endl;
		cerr << r.rank(3) << endl;
		cerr << r.rank(4) << endl;
		rank_support_v<1> tt(&A);

		*/
		/*
		cerr << tt.rank(0) << endl;
		cerr << tt.rank(1) << endl;
		cerr << tt.rank(2) << endl;
		cerr << tt.rank(3) << endl;
		cerr << tt.rank(4) << endl;
		*/
	//	cerr << r.b->size() << " " << size-1 << endl;
		return r->rank1(size-1);
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
			for (size_t k = 0; k < level.size(); k++)
			{
				printf("%02x\n", ((char*)level[k].r->b)[0]);
				cerr << "XX1" << *(level[k].r->b) << endl;
				cerr << "DX1" << level[k].A << endl;
			}
			cerr << collisions.size() << endl;
			level.push_back(bb_level<KeyType>());
			for (size_t k = 0; k < level.size()-1; k++)
			{
				cerr << "DX2" << level[k].A << endl;
				printf("%02x\n", ((char*)level[k].r->b)[0]);
				cerr << "XX2" << *(level[k].r->b) << endl;
			}
			collisions = level.back().init(collisions, gamma);
//			cerr << "XXX" << endl;
//			cerr << "DDD" << (*level.back().r.b) << endl;
			//for (size_t k = 0; k < level.size(); k++)
			//	cerr << "X" << level[k].r.size() << endl;
			for (size_t k = 0; k < level.size(); k++)
			{
				cerr << "XX" << *(level[k].r->b) << endl;
				cerr << "DX" << level[k].A << endl;
			}
		}

		cerr << level.size() << endl;
		for (auto l: level)
		{
			cerr << l.keys.size() << " ";
			for(auto key: l.keys) 
				cerr << key << " ";
			cerr << endl;
		}
		/*
		for (size_t k = 0; k < level.size(); k++)
		{
			cerr << "X" << level[k].r.b->size() << endl;
			cerr << "D" << level[k].A.size() << endl;
		}
		*/
		
	}

	size_type get(KeyType key)
	{

		size_type sum = 0;
		for (size_t i = 0; i < level.size(); i++)
		{
			cerr << "WW " << i << endl;
//			cerr << (*level[i].r.b) << endl;
			size_type ind = level[i].get_hash(key);
			cerr << "ind: " << ind << endl;
			
//			cerr << i << " " << ind << " " << level[i].A.size() << " " << level[i].r.b->size() << endl;
			if (level[i].A[ind] == 1)
			{
				return sum + level[i].r->rank1(ind);
			}
			cerr << "YY" << endl;
			cerr << level[i].A << endl;
//			cerr << (*level[i].r.b) << endl;
			sum += level[i].weight();
			cerr << "YY" << endl;
		}
		cerr << "Key not found" << endl;
		return sum;
	}

};

