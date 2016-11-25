s-rlbwt: Sparse Run-Length Compressed Burrows-Wheeler transform with sparse suffix array sampling
===============
Author: Nicola Prezza (nicolapr@gmail.com)

### Brief description

The s-rlbwt data structure is a fast index that takes advantage of text repetitions in order to reduce its memory footprint. Highly repetitive inputs produce fewer BWT runs, and therefore a smaller structure. The s-rlbwt index applies sparsification to the main bitvector encoding run lengths: this results in a space occupancy close to 

r(log sigma + log(n/r)) + (n/k)log n

where: r is the number of BWT runs, n is the text length, sigma is the alphabet size, and k is the suffix array sampling

Compared to previous RLBWT-based indexes (e.g. RLCSA), the s-rlbwt saves therefore r*log(n/r) bits of space. 

### Download

To clone the repository, use the --recursive option:

> git clone --recursive http://github.com/nicolaprezza/s-rlbwt

### Compile

The library has been tested under linux using gcc 4.9.2. You need the SDSL library installed on your system (https://github.com/simongog/sdsl-lite).

s-rlbwt uses cmake to generate the Makefile. Create a build folder in the main s-rlbwt folder:

> mkdir build

execute cmake:

> cd build; cmake ..

and compile:

> make

### Run

After compiling, run 

>  s-rlbwt-build input.txt

This command will create the s-rlbwt index of the text file "input.txt" and will store it using as prefix "input.txt". Use option -o to specify a different basename for the index files. 

Run

> s-rlbwt-count index_basename patterns_file

or

> s-rlbwt-locate index_basename patterns_file

to count/locate a set of patterns in pizza&chilli format (http://pizzachili.dcc.uchile.cl/experiments.html) using the s-rlbwt index. At the moment, these executables do not store the output anywhere (we use it only for benchmarking purposes)
