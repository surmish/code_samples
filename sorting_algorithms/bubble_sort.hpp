#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_BUBBLE_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_BUBBLE_SORT_HPP
#include <vector>

template <typename value_type> void bubble_sort(std::vector<value_type> &v) {
  for (auto i = v.begin(); i < v.end() - 1; i++) {
    for (auto j = v.end() - 1; j > i; j--) {
      if (*j < *(j - 1)) {
        std::swap(*j, *(j - 1));
      }
    }
  }
}

#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_BUBBLE_SORT_HPP
