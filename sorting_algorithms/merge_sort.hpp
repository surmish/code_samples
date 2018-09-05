#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_MERGE_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_MERGE_SORT_HPP

#include <vector>

template <typename value_type>
void merge(std::vector<value_type> &v,
           typename std::vector<value_type>::size_type p,
           typename std::vector<value_type>::size_type q,
           typename std::vector<value_type>::size_type r) {

  auto n1 = q - p + 1;
  auto n2 = r - q;

  typename std::vector<value_type>::size_type l_ptr = 0, r_ptr = 0;

  std::vector<value_type> L(&v[p], &v[p + n1]);
  std::vector<value_type> R(&v[p + n1], &v[p + n1 + n2]);

  L.shrink_to_fit();
  R.shrink_to_fit();

  for (auto i = p; i <= r; i++) {
    if ((l_ptr == n1) || (r_ptr == n2)) {
      if (l_ptr == n1) {
        v[i] = R[r_ptr];
        r_ptr++;
      } else {
        v[i] = L[l_ptr];
        l_ptr++;
      }
    } else {
      if (L[l_ptr] <= R[r_ptr]) {
        v[i] = L[l_ptr];
        l_ptr++;
      } else {
        v[i] = R[r_ptr];
        r_ptr++;
      }
    }
  }
};

template <typename value_type>
void merge_sort(std::vector<value_type> &v,
                typename std::vector<value_type>::size_type p,
                typename std::vector<value_type>::size_type r) {
  if (p < r) {
    // Calculating average of unsigned int in a safe way
    int q = (p / 2) + (r / 2) + (p & r & 1);
    merge_sort(v, p, q);
    merge_sort(v, q + 1, r);
    merge(v, p, q, r);
  }
}
#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_MERGE_SORT_HPP
