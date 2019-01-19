/* Given an array,find the maximum j – i such that arr[j] > arr[i] */

#include <algorithm>
/* #include <bitset> */
#include <climits>
/* #include <cmath> */
#include <cstdlib>
#include <fstream>
#include <iostream>
/* #include <memory> */
#include <vector>

int32_t arr_max_diff (const std::vector<int32_t> &v) {
  int32_t pos_i  = 0;
  int32_t pos_j  = 0;
  std::vector<int32_t> min_vals, max_vals;
  auto v_size = static_cast<int32_t>(v.size());
  min_vals.reserve(v_size);
  max_vals.reserve(v_size);
  for (pos_i = 0, pos_j = v_size - 1; pos_i < v_size ; pos_i++, pos_j--) {
    if (pos_i == 0) {
      min_vals.push_back(pos_i);
    } else {
      if (v[min_vals.back()] > v[pos_i]) {
        min_vals.push_back(pos_i);
      } else {
        min_vals.push_back(min_vals.back());
      }
    }
    if (pos_j == (v_size - 1)) {
      max_vals.push_back(pos_j);
    } else {
      if (v[max_vals.back()] < v[pos_j]) {
        max_vals.push_back(pos_j);
      } else {
        max_vals.push_back(max_vals.back());
      }
    }
  }
  std::reverse (max_vals.begin(), max_vals.end());
  /* for (auto elem : min_vals) { */
  /*   std::cout << elem << ":" ; */
  /* } */
  /* std::cout << std::endl; */
  /* for (auto elem : max_vals) { */
  /*   std::cout << elem << ":" ; */
  /* } */
  /* std::cout << std::endl; */

  int32_t max_pos_diff = -1;
  pos_i = pos_j = 0;
  while (pos_j < v_size && pos_i < v_size) {
    if (v[min_vals[pos_i]] < v[max_vals[pos_j]]) {
      std::cout << "Current max_pos_diff is: " << max_pos_diff << std::endl;
      std::cout << "j:i is: " << pos_j << ":" << pos_i << std::endl;
      std::cout << "v[min_vals[pos_i]]:v[max_vals[pos_j]] is: " << v[min_vals[pos_i]] << ":" <<  v[max_vals[pos_j]] << std::endl;
      max_pos_diff = (max_pos_diff < (pos_j - pos_i)) ? (pos_j - pos_i) : max_pos_diff;
      pos_j++;
    } else {
      pos_i++;
    }
    /* std::cout << "Current max_pos_diff is: " << max_pos_diff << std::endl; */
  }
  /* for (pos_i = 0; pos_i < v_size - 1; pos_i++) { */
  /*   for (pos_j = pos_i + 1; pos_j < v_size; pos_j++) { */
  /*     if (v[pos_j] > v[pos_i]) { */
  /*       if (max_pos_diff < (pos_j - pos_i)) { */
  /*         std::cout << "pos_j:pos_i are: " << pos_j << ":" << pos_i << std::endl; */
  /*         max_pos_diff = pos_j - pos_i; */
  /*       } */
  /*     } */
  /*   } */
  /* } */
  return max_pos_diff;
};

int main(int argc, const char **argv) {
  std::ifstream fin(getenv("INPUT_PATH"), std::ios_base::in);
  std::ofstream fout(getenv("OUTPUT_PATH"), std::ios_base::out);

  uint32_t q;
  fin >> q;
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<int32_t> input_vector;
  input_vector.reserve(q);
  for (uint32_t q_itr = 0; q_itr < q; q_itr++) {
    uint32_t n;
    fin >> n;
    input_vector.push_back(n);
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  
  fout << arr_max_diff(input_vector) << "\n";
  /* fout << "\n"; */
  fout.close();

  (void)argc;
  (void)argv;
  return 0;
}
