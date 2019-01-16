/* Friend circle queries: https://www.hackerrank.com/challenges/friend-circle-queries/problem */

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <vector>

std::shared_ptr<std::list<uint32_t>> createList() {
  return std::make_shared<std::list<uint32_t>>();
}

std::vector<uint32_t>
maxCircle(const std::vector<std::vector<uint32_t>> &queries) {
  std::map<uint32_t, std::shared_ptr<std::list<uint32_t>>> int_map;
  std::vector<uint32_t> result;
  uint32_t max = 0;
  for (auto &elem : queries) {
    if (int_map[elem[0]] == nullptr && int_map[elem[1]] == nullptr) {
      auto new_list = createList();
      new_list->push_back(elem[0]);
      int_map[elem[0]] = new_list;
      new_list->push_back(elem[1]);
      int_map[elem[1]] = new_list;
      if (max < new_list->size()) {
        max = new_list->size();
      }
    } else if (int_map[elem[0]] != nullptr && int_map[elem[1]] == nullptr) {
      auto list_ptr = int_map[elem[0]];
      list_ptr->push_back(elem[1]);
      int_map[elem[1]] = list_ptr;
      if (max < list_ptr->size()) {
        max = list_ptr->size();
      }
    } else if (int_map[elem[0]] == nullptr && int_map[elem[1]] != nullptr) {
      auto list_ptr = int_map[elem[1]];
      list_ptr->push_back(elem[0]);
      int_map[elem[0]] = list_ptr;
      if (max < list_ptr->size()) {
        max = list_ptr->size();
      }
    } else {
      if (int_map[elem[0]] != int_map[elem[1]]) {
        if (int_map[elem[0]]->size() > int_map[elem[1]]->size()) {
          auto list_ptr = int_map[elem[0]];
          auto temp_list_ptr = int_map[elem[1]];
          for (auto i = temp_list_ptr->begin(); i != temp_list_ptr->end();) {
            list_ptr->push_back(*i);
            int_map[*i] = list_ptr;
            i = temp_list_ptr->erase(i);
          }
          if (max < list_ptr->size()) {
            max = list_ptr->size();
          }
        } else {
          auto list_ptr = int_map[elem[1]];
          auto temp_list_ptr = int_map[elem[0]];
          for (auto i = temp_list_ptr->begin(); i != temp_list_ptr->end();) {
            list_ptr->push_back(*i);
            int_map[*i] = list_ptr;
            i = temp_list_ptr->erase(i);
          }
          if (max < list_ptr->size()) {
            max = list_ptr->size();
          }
        }
      } else {
        if (max < int_map[elem[0]]->size()) {
          max = int_map[elem[0]]->size();
        }
      }
    }
    result.push_back(max);
  }
  return result;
}

int main(int argc, const char **argv) {
  std::ifstream fin(getenv("INPUT_PATH"), std::ios_base::in);
  std::ofstream fout(getenv("OUTPUT_PATH"), std::ios_base::out);

  uint32_t q;
  fin >> q;
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<std::vector<uint32_t>> queries(q,std::allocator<std::vector<std::vector<uint32_t>>>());
  for (uint32_t i = 0; i < q; i++) {
    queries[i].resize(2);
    for (uint32_t j = 0; j < 2; j++) {
      fin >> queries[i][j];
    }
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::vector<uint32_t> ans = maxCircle(queries);

  for (uint32_t i = 0; i < ans.size(); ++i) {
    fout << ans[i];
    if (i != ans.size() - 1) {
      fout << "\n";
    }
  }

  fout << "\n";
  fout.close();

  (void)argc;
  (void)argv;
  return 0;
}
