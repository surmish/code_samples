#include "bst_sort.hpp"
#include "bubble_sort.hpp"
#include "bucket_sort.hpp"
#include "heap_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "radix_sort.hpp"
#include "selection_sort.hpp"
#include "shell_sort.hpp"
#include <algorithm>
#include <boost/program_options.hpp> // use -lboost_program_options for compile
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#define DEFAULTSIZE 1024

namespace po = boost::program_options;

using value_type = int32_t;
using std::chrono::high_resolution_clock;

void sort(const std::vector<value_type> &random_vector,
          const std::vector<value_type> &random_vector_sorted,
          const std::string &sorting_algorithm,
          const bool &print_vectors) {

  std::vector<value_type> v_sort(random_vector);
  v_sort.resize(random_vector.size());
  v_sort.reserve(random_vector.size());
  v_sort.shrink_to_fit();

  std::string cstr;
  auto t1 = std::chrono::system_clock::now();
  if (sorting_algorithm         == "bst_sort") {
    bst_sort(v_sort);
  } else if (sorting_algorithm  == "bubble_sort") {
    bubble_sort(v_sort);
  } else if (sorting_algorithm  == "bucket_sort") {
    bucket_sort(v_sort);
  } else if (sorting_algorithm  == "heap_sort") {
    heap_sort(v_sort);
  } else if (sorting_algorithm  == "insertion_sort") {
    insertion_sort(v_sort);
  } else if (sorting_algorithm  == "merge_sort") {
    merge_sort(v_sort, 0, v_sort.size() - 1);
  } else if (sorting_algorithm  == "quick_sort") {
    // Use tail recursion to reduce stack frame size
    /* tail_recursive_quick_sort(v_sort,0,v_sort.size()-1); */
    quick_sort(v_sort, 0, v_sort.size() - 1);
  } else if (sorting_algorithm  == "radix_sort") {
    radix_sort(v_sort);
  } else if (sorting_algorithm  == "selection_sort") {
    selection_sort(v_sort);
  } else if (sorting_algorithm  == "shell_sort") {
    shell_sort(v_sort);
  } else {
    std::cerr << "Unknown sorting algorithm!" << std::endl;
    return;
  }
  auto t2 = std::chrono::system_clock::now();

  if (!(v_sort == random_vector_sorted)) {
    std::cerr << sorting_algorithm << "ed vector and original random vector sorted with std::sort are different! Check algorithm!!!" << std::endl;
    if (print_vectors) {
      std::cout << " The " << sorting_algorithm
                << "ed array is: " << std::endl;
      std::copy(v_sort.begin(), v_sort.end(),
                std::ostream_iterator<value_type>(std::cout, " "));
      std::cout << std::endl;
    }
    return;
  }

  if (std::is_sorted(v_sort.begin(), v_sort.end())) {
    cstr = sorting_algorithm + " for vector size " + std::to_string(v_sort.size()) +  " completed in: " ;
    std::cout << cstr << std::setw(6)
              << std::setprecision(6)
              << std::chrono::duration<double>(t2 - t1).count() * 1000
              << " ms"
              << std::endl;
    if (print_vectors) {
      std::cout << " The " << sorting_algorithm
                << "ed array is: " << std::endl;
      std::copy(v_sort.begin(), v_sort.end(),
                std::ostream_iterator<value_type>(std::cout, " "));
      std::cout << std::endl;
    }
  } else {
    std::cerr << sorting_algorithm << " failed. Check the algorithm!!!" << std::endl;
    return;
  }
}

int main(int argc, const char **argv) {

  std::string program_desc = "This program sorts a vector made up of uniformly generated random numbers\nranging from " +
    std::to_string(std::numeric_limits<value_type>::min()) +
    " to " +
    std::to_string(std::numeric_limits<value_type>::max());

  po::options_description desc(program_desc, 80, 40);

  std::string vectorsize_desc =
      "Vector size between " +
      std::to_string(
          std::numeric_limits<std::vector<value_type>::size_type>::min()) +
      " and " +
      std::to_string(
          std::numeric_limits<std::vector<value_type>::size_type>::max());

  bool all            = false;
  bool bst_sort       = false;
  bool bubble_sort    = false;
  bool bucket_sort    = false;
  bool heap_sort      = false;
  bool insertion_sort = false;
  bool merge_sort     = false;
  bool quick_sort     = false;
  bool radix_sort     = false;
  bool selection_sort = false;
  bool shell_sort     = false;
  bool print_vectors  = false;

  desc.add_options()("help,h", "produce help message")
    ("vector_size,v",
      po::value<std::vector<value_type>::size_type>()->default_value(DEFAULTSIZE),
      vectorsize_desc.c_str())
    ("all,a",           po::bool_switch(&all),            "Run all sorting algorithms")
    ("bst_sort",        po::bool_switch(&bst_sort),       "Run binary search tree sort algorithm")
    ("bubble_sort",     po::bool_switch(&bubble_sort),    "Run bubble sort algorithm")
    ("bucket_sort",     po::bool_switch(&bucket_sort),    "Run bucket sort algorithm")
    ("heap_sort",       po::bool_switch(&heap_sort),      "Run heap sort algorithm")
    ("insertion_sort",  po::bool_switch(&insertion_sort), "Run insertion sort algorithm")
    ("merge_sort",      po::bool_switch(&merge_sort),     "Run merge sort algorithm")
    ("quick_sort",      po::bool_switch(&quick_sort),     "Run quick sort algorithm")
    ("radix_sort",      po::bool_switch(&radix_sort),     "Run radix sort algorithm")
    ("selection_sort",  po::bool_switch(&selection_sort), "Run selection sort algorithm")
    ("shell_sort",      po::bool_switch(&shell_sort),     "Run selection sort algorithm")
    ("print_vectors",   po::bool_switch(&print_vectors),  "Print the unsorted vector and the sorted one after each. Make sure vector_size is a small number");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc, 0, po::ext_parser()), vm,
            false);
  po::notify(vm);

  if ((vm.count({"help", std::allocator<char>()}) != 0) || (argc == 1)) {
    std::cout << desc << std::endl;
    return 0;
  }

  // Get the size of the vector to be sorted from program options
  std::vector<value_type>::size_type vector_size =
      vm[{"vector_size", std::allocator<char>()}]
          .as<std::vector<value_type>::size_type>();

  std::random_device rnd_device({"/dev/urandom", std::allocator<char>()});
  std::mt19937 mersenne_engine{rnd_device()};

  // Initializing a huge vector with a small range of numbers makes
  // quick sort slower than average.
  /* std::uniform_int_distribution<value_type> distribution(-100,100); */
  std::uniform_int_distribution<value_type> distribution(
      std::numeric_limits<value_type>::min(),
      std::numeric_limits<value_type>::max());

  // Lambda function for random number generation to use with std::generator
  auto gen = [&distribution, &mersenne_engine]() {
    return distribution(mersenne_engine);
  };

  std::vector<value_type> random_vector;
  random_vector.reserve(vector_size);
  random_vector.resize(vector_size);
  std::generate(random_vector.begin(), random_vector.end(), gen);
  random_vector.shrink_to_fit();

  std::vector<value_type> random_vector_sorted(random_vector);
  random_vector_sorted.resize(random_vector.size());
  random_vector_sorted.reserve(random_vector.size());
  random_vector_sorted.shrink_to_fit();
  std::sort(random_vector_sorted.begin(), random_vector_sorted.end());

  if (print_vectors) {
    std::cout << "Unsorted randomized vector is: " << std::endl;
    std::copy(random_vector.begin(), random_vector.end(),
              std::ostream_iterator<value_type>(std::cout, " "));
    std::cout << std::endl;
  }

  if (all) {
    sort(random_vector, random_vector_sorted, {"bst_sort",        std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"bubble_sort",     std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"bucket_sort",     std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"heap_sort",       std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"insertion_sort",  std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"merge_sort",      std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"quick_sort",      std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"radix_sort",      std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"selection_sort",  std::allocator<char>()}, print_vectors);
    sort(random_vector, random_vector_sorted, {"shell_sort",      std::allocator<char>()}, print_vectors);
  } else {
    if (bst_sort) {
      sort(random_vector, random_vector_sorted, {"bst_sort",        std::allocator<char>()}, print_vectors);
    }
    if (bubble_sort) {
      sort(random_vector, random_vector_sorted, {"bubble_sort",     std::allocator<char>()}, print_vectors);
    }
    if (bucket_sort) {
      sort(random_vector, random_vector_sorted, {"bucket_sort",     std::allocator<char>()}, print_vectors);
    }
    if (heap_sort) {
      sort(random_vector, random_vector_sorted, {"heap_sort",       std::allocator<char>()}, print_vectors);
    }
    if (insertion_sort) {
      sort(random_vector, random_vector_sorted, {"insertion_sort",  std::allocator<char>()}, print_vectors);
    }
    if (merge_sort) {
      sort(random_vector, random_vector_sorted, {"merge_sort",      std::allocator<char>()}, print_vectors);
    }
    if (quick_sort) {
      sort(random_vector, random_vector_sorted, {"quick_sort",      std::allocator<char>()}, print_vectors);
    }
    if (radix_sort) {
      sort(random_vector, random_vector_sorted, {"radix_sort",      std::allocator<char>()}, print_vectors);
    }
    if (selection_sort) {
      sort(random_vector, random_vector_sorted, {"selection_sort",  std::allocator<char>()}, print_vectors);
    }
    if (shell_sort) {
      sort(random_vector, random_vector_sorted, {"shell_sort",      std::allocator<char>()}, print_vectors);
    }
  }
  return 0;
}
