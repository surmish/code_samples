#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_BUCKET_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_BUCKET_SORT_HPP

#include <cstdint>
#include <limits>
#include <list>
#include <vector>

template <typename value_type>
void bucket_sort_subroutine(std::vector<value_type> &v) {

  typename std::vector<typename std::list<value_type>> B;
  B.resize(v.size());
  B.reserve(v.size());

  std::fill(B.begin(), B.end(), std::list<value_type>(0));

  auto bucket_size = static_cast<uint32_t>(
      (std::numeric_limits<value_type>::max() / v.size()) + 1);

  for (auto elem : v) {
    auto bucket_no = static_cast<uint32_t>(elem / bucket_size);
    // Do not exceed vector size
    if (bucket_no >= v.size()) {
      bucket_no = v.size() - 1;
    }
    if (B[bucket_no].empty()) {
      B[bucket_no].push_front(elem);
    } else {
      auto it = B[bucket_no].begin();
      while (*it < elem && it != B[bucket_no].end()) {
        it++;
      }
      B[bucket_no].insert(it, elem);
    }
  }

  v.clear();
  for (auto elem : B) {
    if (!elem.empty()) {
      for (auto list_elem : elem) {
        v.push_back(list_elem);
      }
    }
  }
}

template <typename value_type> void bucket_sort(std::vector<value_type> &v) {
  std::vector<value_type> pos_v;
  std::vector<value_type> neg_v;

  for (auto elem : v) {
    if (elem < 0) {
      neg_v.push_back((elem + 1) * -1);
    } else {
      pos_v.push_back(elem);
    }
  }

  if (!neg_v.empty()) {
    bucket_sort_subroutine(neg_v);
  }
  if (!pos_v.empty()) {
    bucket_sort_subroutine(pos_v);
  }

  v.clear();
  for (auto it = neg_v.rbegin(); it != neg_v.rend(); it++) {
    v.push_back(((*it) * -1) - 1);
  }
  for (auto elem : pos_v) {
    v.push_back(elem);
  }
}

#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_BUCKET_SORT_HPP
