# sorting

c++ implementation of common sorting techniques

```
[archlinux@thinkpad sorting_algorithms]$ ./sort 
This program sorts a vector made up of uniformly generated random numbers
ranging from -2147483648 to 2147483647:
  -h [ --help ]                    produce help message
  -v [ --vector_size ] arg (=1024) Vector size between 0 and 
                                   18446744073709551615
  -a [ --all ]                     Run all sorting algorithms
  --bst_sort                       Run binary search tree sort algorithm
  --bubble_sort                    Run bubble sort algorithm
  --bucket_sort                    Run bucket sort algorithm
  --heap_sort                      Run heap sort algorithm
  --insertion_sort                 Run insertion sort algorithm
  --merge_sort                     Run merge sort algorithm
  --quick_sort                     Run quick sort algorithm
  --radix_sort                     Run radix sort algorithm
  --selection_sort                 Run selection sort algorithm
  --shell_sort                     Run selection sort algorithm
  --print_vectors                  Print the unsorted vector and the sorted one
                                   after each. Make sure vector_size is a small
                                   number
```


The following script compiles and runs the programs for multiple vector sizes.

`./run.sh`

You can either compile using make as follows (uses g++ as default)

`make`

or compile all the files explicity using

`g++ -lboost_program_options main.cpp -o sort`

You can execute the compiled binary as follows

E.g:
```bash
./sort --help
./sort --all
./sort --quick_sort
./sort --merge_sort --vector_size 20000
./sort --quick_sort --vector_size 50 --printvectors
```
Executing `run.sh` gives the following:
```
g++ -c bst_sort.hpp
g++ -c bucket_sort.hpp
g++ -c bubble_sort.hpp
g++ -c heap_sort.hpp
g++ -c insertion_sort.hpp
g++ -c merge_sort.hpp
g++ -c quick_sort.hpp
g++ -c radix_sort.hpp
g++ -c shell_sort.hpp
g++ -c selection_sort.hpp
g++ -c main.cpp -o main.o
g++ -lboost_program_options main.o -o sort
bst_sort for vector size 10 completed in: 0.007166 ms
bubble_sort for vector size 10 completed in: 0.003832 ms
bucket_sort for vector size 10 completed in: 0.020144 ms
heap_sort for vector size 10 completed in: 0.002469 ms
insertion_sort for vector size 10 completed in: 0.002501 ms
merge_sort for vector size 10 completed in: 0.006832 ms
quick_sort for vector size 10 completed in: 0.001266 ms
radix_sort for vector size 10 completed in: 0.040933 ms
selection_sort for vector size 10 completed in: 0.003421 ms
shell_sort for vector size 10 completed in: 0.0013 ms

bst_sort for vector size 100 completed in: 0.074157 ms
bubble_sort for vector size 100 completed in: 0.437958 ms
bucket_sort for vector size 100 completed in: 0.140748 ms
heap_sort for vector size 100 completed in: 0.058129 ms
insertion_sort for vector size 100 completed in: 0.215422 ms
merge_sort for vector size 100 completed in: 0.124541 ms
quick_sort for vector size 100 completed in: 0.028533 ms
radix_sort for vector size 100 completed in: 0.196274 ms
selection_sort for vector size 100 completed in: 0.321415 ms
shell_sort for vector size 100 completed in: 0.034317 ms

bst_sort for vector size 1000 completed in: 0.818849 ms
bubble_sort for vector size 1000 completed in: 30.9703 ms
bucket_sort for vector size 1000 completed in: 0.984855 ms
heap_sort for vector size 1000 completed in: 0.459873 ms
insertion_sort for vector size 1000 completed in: 11.6707 ms
merge_sort for vector size 1000 completed in: 0.720243 ms
quick_sort for vector size 1000 completed in: 0.227936 ms
radix_sort for vector size 1000 completed in: 0.478835 ms
selection_sort for vector size 1000 completed in: 16.0763 ms
shell_sort for vector size 1000 completed in: 0.308117 ms

bst_sort for vector size 10000 completed in: 5.22068 ms
bubble_sort for vector size 10000 completed in: 2555.45 ms
bucket_sort for vector size 10000 completed in: 9.73568 ms
heap_sort for vector size 10000 completed in: 6.18875 ms
insertion_sort for vector size 10000 completed in: 1151.39 ms
merge_sort for vector size 10000 completed in: 8.13556 ms
quick_sort for vector size 10000 completed in: 3.16483 ms
radix_sort for vector size 10000 completed in: 4.49981 ms
selection_sort for vector size 10000 completed in: 1610.92 ms
shell_sort for vector size 10000 completed in: 4.64846 ms
```
