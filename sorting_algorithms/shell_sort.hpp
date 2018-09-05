#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_SHELL_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_SHELL_SORT_HPP

#include <cstdint>
#include <vector>

template <typename value_type> void shell_sort(std::vector<value_type> &v) {

  if (v.size() == 0) {
    return;
  }

  typename std::vector<value_type>::size_type gap = 1;
  while (gap < (v.size()) / 3) {
    gap = 3 * gap + 1;
  }

  while (gap >= 1) {
    for (int64_t j = gap; j < static_cast<int64_t>(v.size()); j++) {
      auto key = v[j];
      int64_t i = j - gap;
      while (i >= 0 && (v[i] > key)) {
        v[i + gap] = v[i];
        i = i - gap;
      }
      v[i + gap] = key;
    }
    gap = (gap / 3);
  }
}
#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_SHELL_SORT_HPP
