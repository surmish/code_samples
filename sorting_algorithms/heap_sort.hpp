#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_HEAP_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_HEAP_SORT_HPP

#include <vector>

template <typename value_type>
void max_heapify(std::vector<value_type> &v,
                 typename std::vector<value_type>::size_type &heap_size,
                 typename std::vector<value_type>::size_type i) {
  typename std::vector<value_type>::size_type L = (2 * i + 1);
  typename std::vector<value_type>::size_type R = (2 * i + 2);
  typename std::vector<value_type>::size_type largest;
  if ((L < heap_size) && (v[L] > v[i])) {
    largest = L;
  } else {
    largest = i;
  }
  if ((R < heap_size) && (v[R] > v[largest])) {
    largest = R;
  }
  if (largest != i) {
    std::swap(v[i], v[largest]);
    max_heapify(v, heap_size, largest);
  }
}

template <typename value_type>
void build_max_heap(std::vector<value_type> &v,
                    typename std::vector<value_type>::size_type &heap_size) {
  // Safe 'for' loop for unsigned integers, use i-1 instead of i in the body
  for (typename std::vector<value_type>::size_type i =
           ((heap_size - 1) / 2) + 1;
       i > 0; --i) {
    max_heapify(v, heap_size, i - 1);
  }
}

template <typename value_type>
void swap_max_and_decrement(
    std::vector<value_type> &v,
    typename std::vector<value_type>::size_type &heap_size,
    typename std::vector<value_type>::size_type i) {
  std::swap(v[0], v[i]);
  heap_size--;
  max_heapify(v, heap_size, 0);
}

template <typename value_type> void heap_sort(std::vector<value_type> &v) {
  typename std::vector<value_type>::size_type heap_size = v.size();
  build_max_heap(v, heap_size);
  for (auto i = v.size(); i >= 1; i--) {
    swap_max_and_decrement(v, heap_size, i - 1);
  }
}

#endif // HOME_ARCHLINUX_SORTING_ALGORITHMS_HEAP_SORT_HPP
