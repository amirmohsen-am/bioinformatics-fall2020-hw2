Course: Algorithms, Data Structures and Inference for High-Throughput Genomics  
Fall 2020 - UMD

CMSC858D Homework 2 : Implementing a minimum perfect hash function

https://rob-p.github.io/CMSC858D_F20/assignments/03_homework_02

# References
<a href="https://arxiv.org/abs/1702.03154">[1]</a> 
Limasset, Antoine, et al. "Fast and scalable minimal perfect hashing for massive key sets." arXiv preprint arXiv:1702.03154 (2017).
<a href=>[2]</a> xxHash: Extremely fast non-cryptographic hash algorithm 

# libraries


*sdsl* `bit_vector` and `rank_support` has been used in this project 
In order to install `sdsl` library:
```
git clone https://github.com/simongog/sdsl-lite.git
cd sdsl-lite
sudo ./install.sh /usr/local/
```
`rank_support` from hw1 is used. (hw1 folder)  
`xxhash.h` and `xxhash.c` is used for fast hashing with arbitary seed

## data
data is generated using data/gen_data.cpp
## bbhash
bbhash is implemented in header `bbhash.hpp`  
`run_bbhash.cpp` is used for running an instance of bbhash.  
`run_bbhash.cpp` takes GAMMA as an argument.  
Number of keys are given in the first line of input.
Keys are given in the second line.  
Number of queries are given on the third line.
Query strings are given on the second line. 

The output consists of information about the bbhash table and the queries.

## compiling

```
g++ -std=c++11 -Wall -DNDEBUG -O3 -I/usr/local/include -L/usr/local/lib run_bbhash.cpp xxhash.c -lsdsl  
```
## running
```
./a.out GAMMA
```
## sample run
```
./a.out 1
```
input:
```
5
COVID
19
bushfire
trump
2020

2
COVID
vaccine2020
```
output:
```
1
Key not found: vaccine2020
5

n:5 , gamma:2
levels:2
level-0 : 3
level-1 : 2
terminal hash table size: 0
bitvector overhead: 1
all overhead: 1
Alien keys: 1
```