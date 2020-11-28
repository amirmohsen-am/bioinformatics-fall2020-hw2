# rank_support
select_support class is implemented in header `rank_support.hpp`  
compiling and running:
```
g++ -std=c++11 -DNDEBUG -O3 -I/usr/local/include -L/usr/local/lib \
run_rank.cpp -lsdsl -ldivsufsort -ldivsufsort64 && ./a.out
```
`run_rank.cpp` takes one string consisting of '0' and '1's as input. And then constructs the tables needed. Then it will test all the possible queries to see if select is working properly.  
Then in each line it will get a query x and print `rank1(x)` (0 based index)

sample input:
```
1001011101001010
1
0
3   

```
sample output:
```
bit_vector:
1001011101001010
R1, sz1= 8
0 5 
R2, sz2= 2
0 1 2 3 0 1 1 2 
testing rank_support on bitvector size: 16
test passed
overhead: 40
rank1(1) = 1
rank1(0) = 1
rank1(3) = 2
```


some changes to function parameter format:
```
rank_support.save(ofstream& fout);
rank_support.load(ofstream& fout);
```
