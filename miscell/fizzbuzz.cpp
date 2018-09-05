#include <gsl/gsl_util>
#include <iostream>
#include <string>

int main() {

  std::string buf(10,' ',std::allocator<char>());

  const char *arr[] = {
    buf.c_str(),
    "Buzz",
    "Fizz",
    "FizzBuzz"
  };

  for (uint32_t i= 1; i < 1000; i++) {
    buf = std::to_string(i);
    std::cout << gsl::at(arr,((static_cast<uint32_t>((i % 3) == 0u) << 1u) | static_cast<uint32_t>((i % 5) == 0u))) << std::endl;
  }
  
  return 0;
}
