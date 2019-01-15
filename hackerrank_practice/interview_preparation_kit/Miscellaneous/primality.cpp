#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

std::string primality(uint64_t n) {
  auto sq_root = static_cast<uint64_t>(sqrt(n));
  if (n <= 1) {
    return {"Not prime", std::allocator<char>()};
  }
  for (uint64_t i = 2; i <= sq_root; i++) {
    if (n % i == 0) {
      return {"Not prime", std::allocator<char>()};
    }
  }
  return {"Prime", std::allocator<char>()};
}

int main(int argc, const char **argv) {
  std::ifstream fin(getenv("INPUT_PATH"), std::ios_base::in);
  std::ofstream fout(getenv("OUTPUT_PATH"), std::ios_base::out);

  /* std::string str; */
  uint32_t q;
  fin >> q;
  /* std::cout << "q is: " << q << std::endl; */

  for (uint32_t q_itr = 0; q_itr < q; q_itr++) {
    uint32_t n;
    fin >> n;
    /* std::cout << "n is: " << n << std::endl; */
    std::string result = primality(n);
    /* std::cout << "result is: " << result << std::endl; */
    fout << result << "\n";
  }

  fout.close();

  (void)argc;
  (void)argv;
  return 0;
}
