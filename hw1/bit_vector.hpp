#include <iostream>
#include <sdsl/bit_vectors.hpp>


using namespace std;



void save_ull(uint64_t x, ofstream& fout)
{
	fout.write((char*)&x, sizeof(x));
}
void load_ull(uint64_t& x, ifstream& fin)
{
	fin.read((char*)&x, sizeof(x));
}

class bit_vector : public sdsl::bit_vector
{
	// include the constructors
	using sdsl::bit_vector::bit_vector;
	public:

	bit_vector(uint64_t size, uint64_t value) : sdsl::bit_vector(size)
	{
		set_int(0, value);
	}

	uint64_t to_int()
	{
		// TODO check if it fits
		return get_int(0);
	}

	void save(ofstream& fout)
	{
	
	//	uint64_t output_size = ((this->size() + 7) / 8)*8;
	//	cerr << output_size << endl;
	//	save_ull(output_size, fout);
		save_ull(this->size(), fout);
		uint64_t cnt = 0;
		for (auto i = 0; i < this->size(); i += 8) {
			uint8_t byte = get_int(i, 8); 
			fout.write((char*)(&byte), 1);
			cnt += 8;
		}
//		cerr << cnt << " " << output_size << endl;
//		cerr << this->size() << endl;
//		assert(cnt == output_size);
	}
	void load(ifstream& fin)
	{
		this->resize(0);
		uint64_t sz;
		load_ull(sz, fin);
	//	cerr << sz << endl;
	//	cerr << sizeof(sz) << endl;
		this->resize(sz);
		for (auto i = 0; i < this->size(); i += 8) 
		{
			char byte;
			fin.read(&byte, 1);
			set_int(i, byte, 8);
		}
	}


};

bit_vector rand_bitvector(uint64_t sz) 
{
	bit_vector res(sz);
	for (auto i = 0; i < sz; i++)
		res[i] = rand()%2;
	return res;
}

