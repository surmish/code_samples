/* Maximum XOR: https://www.hackerrank.com/challenges/maximum-xor/problem */

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <iostream>
#include <vector>

std::vector<std::string> split_string(std::string /*input_string*/);

class TrieNode {
private:
  std::shared_ptr<TrieNode> one_child;
  std::shared_ptr<TrieNode> zero_child;

public:
  TrieNode() {
    one_child = nullptr;
    zero_child = nullptr;
  }

  void set_one_child (std::shared_ptr<TrieNode>  child) {one_child  = child;}
  void set_zero_child (std::shared_ptr<TrieNode> child) {zero_child = child;}
  std::shared_ptr<TrieNode> get_one_child  () {return one_child; }
  std::shared_ptr<TrieNode> get_zero_child () {return zero_child;}

  ~TrieNode(){
  }
};

auto createTrieNode () {
  return std::shared_ptr<TrieNode>(new TrieNode);
}

class Trie {
private:
  std::shared_ptr<TrieNode> root;

public:
  void insert(uint32_t elem) {
    std::shared_ptr<TrieNode> current = root;
    int length = (sizeof(uint32_t) * CHAR_BIT);
    for (int current_bit = length; current_bit > 0; current_bit--) {
      uint32_t mask = static_cast<uint32_t>(1)
                      << (static_cast<uint32_t>(current_bit) - 1);
      bool bit = (elem & mask) != 0u;
      if (bit) {
        if (current->get_one_child() == nullptr) {
          std::shared_ptr<TrieNode> node = createTrieNode();
          current->set_one_child(node);
        }
        current = current->get_one_child();
      } else {
        if (current->get_zero_child() == nullptr) {
          std::shared_ptr<TrieNode> node = createTrieNode();
          current->set_zero_child(node);
        }
        current = current->get_zero_child();
      }
    }
  }
  Trie() { 
    root = createTrieNode();
    std::shared_ptr<TrieNode> temp = nullptr;
    root->set_zero_child(temp);
    root->set_one_child(temp);
  }
  std::shared_ptr<TrieNode> get_root () {return root;}
  ~Trie() {
  }
};

std::vector<uint32_t> maxXor(const std::vector<uint32_t> &arr,
                             const std::vector<uint32_t> &queries) {
  std::vector<uint32_t> result;

  Trie arr_trie{};
  for (auto &elem : arr) {
    arr_trie.insert(elem);
  }
  int length = (sizeof(uint32_t) * CHAR_BIT);

  for (auto &elem : queries) {
    std::shared_ptr<TrieNode> current = arr_trie.get_root();
    std::string maxXor_val = {"",std::allocator<char>()}; 
    for (int current_bit = length; current_bit > 0; current_bit--) {
      uint32_t mask = static_cast<uint32_t>(1)
        << (static_cast<uint32_t>(current_bit) - 1);
      /* std::cout << std::bitset<64>(mask) << std::endl ; */
      bool bit = (elem & mask) != 0u;
      if (bit) {
        if (current->get_zero_child() != nullptr) {
          current = current->get_zero_child();
          maxXor_val += "1";
        } else {
          current = current->get_one_child();
          maxXor_val += "0";
        }
      } else {
        if (current->get_one_child() != nullptr) {
          current = current->get_one_child();
          maxXor_val += "1";
        } else {
          current = current->get_zero_child();
          maxXor_val += "0";
        }
      }
    }
    result.push_back(std::stoi(maxXor_val, nullptr, 2));
    
  }
  (void) queries;
  return result;
}

int main(int argc, const char **argv) {
  std::ifstream fin(getenv("INPUT_PATH"), std::ios_base::in);
  std::ofstream fout(getenv("OUTPUT_PATH"), std::ios_base::out);

  uint32_t n;
  fin >> n;
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string arr_temp_temp;
  getline(fin, arr_temp_temp);

  std::vector<std::string> arr_temp = split_string(arr_temp_temp);

  std::vector<uint32_t> arr(n, std::allocator<uint32_t>());

  for (uint32_t i = 0; i < n; i++) {
    uint32_t arr_item = std::stoi(arr_temp[i], nullptr, 10);
    arr[i] = arr_item;
  }

  int m;
  fin >> m;
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<uint32_t> queries(m, std::allocator<uint32_t>());

  for (int i = 0; i < m; i++) {
    int queries_item;
    fin >> queries_item;
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    queries[i] = queries_item;
  }

  std::vector<uint32_t> result = maxXor(arr, queries);

  for (unsigned i = 0; i < result.size(); ++i) {
    fout << result[i];
    if (i != result.size() - 1) {
      fout << "\n";
    }
  }

  fout << "\n";
  fout.close();

  (void)argc;
  (void)argv;
  return 0;
}

std::vector<std::string> split_string(std::string input_string) {

  std::string::iterator new_end = std::unique(
      input_string.begin(), input_string.end(),
      [](const char &x, const char &y) { return x == y and x == ' '; });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  std::vector<std::string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter, 0);

  while (pos != std::string::npos) {
    splits.push_back(input_string.substr(i, pos - i));
    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(
      input_string.substr(i, std::min(pos, input_string.length()) - i + 1));

  return splits;
}
