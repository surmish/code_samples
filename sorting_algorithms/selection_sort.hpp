#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_SELECTION_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_SELECTION_SORT_HPP

#include <vector>

template <typename value_type> void selection_sort(std::vector<value_type> &v) {
  for (auto j = v.begin(); j < v.end() - 1; j++) {
    auto smallest_key_location = j;
    for (auto i = j + 1; i < v.end(); i++) {
      if (*smallest_key_location > *i) {
        smallest_key_location = i;
      }
    }
    std::swap(*j, *smallest_key_location);
  }
}

#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_SELECTION_SORT_HPP
