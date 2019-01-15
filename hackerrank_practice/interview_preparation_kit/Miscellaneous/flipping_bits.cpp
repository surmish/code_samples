#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

uint32_t flippingBits (uint32_t n) {
  return (static_cast<uint32_t>(-1) - n);
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
    uint32_t result = flippingBits(n);
    /* std::cout << "result is: " << result << std::endl; */
    fout << result << "\n";
  }

  fout.close();

  (void)argc;
  (void)argv;
  return 0;
}
