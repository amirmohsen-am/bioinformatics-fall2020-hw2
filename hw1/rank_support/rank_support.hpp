#include <iostream>
#include "../bit_vector.hpp"

using namespace std;


// get ceil(log2(x))
uint64_t get_log(uint64_t x)
{
	x--;
	uint64_t res = 0;
	while(x >>= 1) 
		res++;
	return res+1;
}

class rank_support
{
	public:
	bit_vector* b;
	vector <bit_vector> R1, R2;
	uint64_t sz1, sz2;
	uint64_t R1_bits, R2_bits;
	uint64_t R3_bits;

	bit_vector **R3; 

	rank_support()
	{
		b = new bit_vector(0);
	}
	rank_support(bit_vector *b)
	{
		init(b);
	}


	void init(bit_vector *b) 
	{
		assert(b->size() >= 4);
		this->b = b;
		uint64_t log = get_log(b->size());
		sz1 = log*log/2;
		sz2 = log/2;
		assert(sz1%sz2 == 0);
		// could be better
		R1_bits = log+1;
		R2_bits = get_log(sz1)+1;

	
		uint64_t cnt1 = 0, cnt2 = 0;
		for (auto i = 0; i < b->size(); i++)
		{
			if (i%sz1 == 0)
			{
				R1.push_back(bit_vector(R1_bits, cnt1));	
				cnt2 = 0;
			}
			if (i%sz2 == 0)
				R2.push_back(bit_vector(R2_bits, cnt2));	
			if ((*b)[i])
			{
				cnt1++;
				cnt2++;
			}
		}

		R3_bits = get_log(sz2)+1;

		R3 = new bit_vector*[1<<sz2];
		for (uint64_t i = 0; i < (1<<sz2); i++)
		{
			R3[i] = new bit_vector[sz2];
			uint64_t x = i;
			uint64_t cnt = 0;
			for (int j = 0; j < sz2; j++)
			{
				cnt += x%2;
				R3[i][j] = bit_vector(R3_bits, cnt);
				x >>= 1;
			}
		}

	}

	uint64_t rank1(uint64_t i)
	{
		if (i >= b->size()) i = b->size()-1;


		uint64_t s = (i/sz2)*sz2;
		uint64_t ind = 0;

		/*
		uint64_t mask = 1;
		for (uint64_t i = s; i < s+sz2; i++)
		{
			if ((*b)[i])
				ind += mask;
			mask <<= 1;
		}
		*/

		ind = b->get_int(s,sz2);
			
		/*
		cerr << "R1: " << R1[i/sz1].to_int() << endl;
		cerr << "R2: " << R2[i/sz2].to_int() << endl;
		cerr << "R3 " << ind << ": "<< R3[ind][i%sz2].to_int() << endl;
		*/
		return R1[i/sz1].to_int() + R2[i/sz2].to_int() + R3[ind][i%sz2].to_int();
	}
	uint64_t rank0(uint64_t i)
	{
		return i+1 - rank1(i);
	}
	uint64_t rank(uint64_t i, bool bit)
	{
		if (bit == 0)
			return rank0(i);
		else
			return rank1(i);
	}

	uint64_t overhead()
	{
		uint64_t sum = 0;
		sum += R1.size()*(R1_bits-1);
		sum += R2.size()*(R2_bits-1);
		sum += (1<<sz2)*sz2*(R3_bits-1);
		return sum;
	}


	void print()
	{
		cerr << "bit_vector:\n" << (*b) << endl;
		cerr << "R1, sz1= " << sz1 << endl;
		for (auto x : R1)
			cerr << x.to_int() << " ";
		cerr << endl;
		cerr << "R2, sz2= " << sz2 << endl;
		for (auto x : R2)
			cerr << x.to_int() << " "; 
		cerr << endl;

	}
	void print_sizes()
	{
		cerr << "R1: " << sz1 << ", " << R1_bits << " R1 size: " << R1.size() << endl;
		cerr << "R2: " << sz2 << ", " << R2_bits << " R2 size: " << R2.size() << endl;
		cerr << "R3: " << (1<<sz2)<< " " << sz2  << ", " << R3_bits << endl;
	}



	bool test()
	{
		cerr << "testing rank_support on bitvector size: " << b->size() << endl;
		uint64_t cnt = 0;
		for (auto i = 0; i < b->size(); i++)
		{
			cnt += (*b)[i];
			if (cnt != rank1(i))
			{
				cerr << "test fail on index: " << i << endl;
				return false;
			}

		}
		cerr << "test passed" << endl;
		return true;
	}
/*

	uint64_t sz1, sz2;
	bit_vector* b;
	vector <bit_vector> R1, R2;
	bit_vector **R3; 
	uint64_t R1_bits, R2_bits;
	uint64_t R3_bits;

	*/
	void save(ofstream& fout)
	{
		save_ull(sz1, fout);
		save_ull(sz2, fout);
		b->save(fout);
		save_ull(R1.size(), fout);
		for (auto bv: R1)
			bv.save(fout);

		save_ull(R2.size(), fout);
		for (auto bv: R2)
			bv.save(fout);

		for (int i = 0; i < (1<<sz2); i++)
			for (int j = 0; j < sz2; j++)
				R3[i][j].save(fout);
	}
	void load(ifstream& fin)
	{
		R1.clear(); R2.clear();

		load_ull(sz1, fin);
		load_ull(sz2, fin);
		b->load(fin);
		uint64_t R1sz;
		load_ull(R1sz, fin);
		R1.resize(R1sz);
		for (int i = 0; i < R1sz; i++)
			R1[i].load(fin);


		uint64_t R2sz;
		load_ull(R2sz, fin);
		R2.resize(R2sz);
		for (int i = 0; i < R2sz; i++)
			R2[i].load(fin);

		R3 = new bit_vector*[1<<sz2];
		for (uint64_t i = 0; i < (1<<sz2); i++)
		{
			R3[i] = new bit_vector[sz2];
			for (int j = 0; j < sz2; j++)
				R3[i][j].load(fin);
		}

//		cerr << R1.size() << " " <<  R2.size()  << " " <<  sz1 << " " << sz2 << endl;
		assert(R1.size() * R2.size() * sz1 * sz2 > 0);

		R1_bits = R1[0].size();
		R2_bits = R2[0].size();
		R3_bits = R3[0][0].size();
	}

	

};






uint64_t hypo_overhead(uint64_t n)
{
	uint64_t log, sz1, sz2, R1_bits, R2_bits, R3_bits;
	log = get_log(n);
	sz1 = log*log/2;
	sz2 = log/2;
	R1_bits = log+1;
	R2_bits = get_log(sz1)+1;
	R3_bits = get_log(sz2)+1;

	uint64_t res = 0;
	res += ((n+sz1-1)/sz1)*(R1_bits-1);
	res += ((n+sz2-1)/sz2)*(R2_bits-1);
	res += (1<<sz2)*sz2*(R3_bits-1);
	return res;

}
