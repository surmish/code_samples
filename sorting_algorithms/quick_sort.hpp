#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_QUICK_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_QUICK_SORT_HPP

#include <vector>

template <typename value_type>
typename std::vector<value_type>::size_type
partition(std::vector<value_type> &v,
          typename std::vector<value_type>::size_type p,
          typename std::vector<value_type>::size_type r) {

  auto pivot = v[r];
  auto i = p;
  for (auto j = p; j <= r - 1; j++) {
    if (v[j] < pivot) {
      auto temp = v[i];
      v[i] = v[j];
      v[j] = temp;
      i++;
    }
  }
  if (i != r) {
    auto temp = v[i];
    v[i] = v[r];
    v[r] = temp;
  }
  return i;
};

template <typename value_type>
void tail_recursive_quick_sort(std::vector<value_type> &v,
                typename std::vector<value_type>::size_type p,
                typename std::vector<value_type>::size_type r) {
  while (p < r) {
    auto q = partition(v, p, r);
    if (p < q)
      tail_recursive_quick_sort(v, p, q - 1);
    p = q + 1;
  }
}

template <typename value_type>
void quick_sort(std::vector<value_type> &v,
                typename std::vector<value_type>::size_type p,
                typename std::vector<value_type>::size_type r) {
  if (p < r) {
    auto q = partition(v, p, r);
    if (p < q)
      quick_sort(v, p, q - 1);
    if (q < r)
      quick_sort(v, q + 1, r);
  }
}
#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_QUICK_SORT_HPP
