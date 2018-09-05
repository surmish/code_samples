#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_INSERTION_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_INSERTION_SORT_HPP
#include <vector>

template <typename value_type> void insertion_sort(std::vector<value_type> &v) {
  for (auto j = v.begin() + 1; j < v.end(); j++) {
    auto key = *j;
    auto i = j - 1;
    while ((i >= v.begin()) && (*i > key)) {
      *(i + 1) = *i;
      i--;
    }
    *(i + 1) = key;
  }
}
#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_INSERTION_SORT_HPP
