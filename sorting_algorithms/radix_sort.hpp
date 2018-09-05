#ifndef _HOME_ARCHLINUX_SORTING_ALGORITHMS_RADIX_SORT_HPP
#define _HOME_ARCHLINUX_SORTING_ALGORITHMS_RADIX_SORT_HPP

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

template <typename value_type> void radix_sort(std::vector<value_type> &v) {
  auto no_of_bytes = static_cast<uint32_t>(sizeof(value_type));
  auto no_of_bits = static_cast<uint32_t>(no_of_bytes * 8);
  auto bits_grouped_together = static_cast<uint32_t>(8);
  auto number_of_chunks =
      static_cast<uint32_t>(no_of_bits / bits_grouped_together);
  auto counter_length = static_cast<uint32_t>(pow(2.0, bits_grouped_together));

  std::vector<value_type> temp;
  temp.resize(v.size());
  temp.reserve(v.size());

  std::vector<uint32_t> counter_vector;
  counter_vector.resize(counter_length);
  counter_vector.reserve(counter_length);

  std::fill(temp.begin(), temp.end(), 0);
  std::fill(counter_vector.begin(), counter_vector.end(), 0);

  for (uint32_t chunk = 0; chunk < number_of_chunks; chunk++) {
    for (auto elem : v) {
      uint32_t mask = ((counter_length - 1)
                       << static_cast<uint32_t>(chunk * bits_grouped_together));
      uint32_t chunk_value = (elem & mask) >> (chunk * bits_grouped_together);
      counter_vector[chunk_value]++;
    }
    for (uint32_t counter_index = 1; counter_index < counter_length;
         counter_index++) {
      counter_vector[counter_index] =
          counter_vector[counter_index] + counter_vector[counter_index - 1];
    }
    for (auto r_iterator = v.rbegin(); r_iterator != v.rend(); ++r_iterator) {
      uint32_t mask = ((counter_length - 1)
                       << static_cast<uint32_t>(chunk * bits_grouped_together));
      uint32_t chunk_value =
          ((*r_iterator & mask) >> (chunk * bits_grouped_together));
      temp[counter_vector[chunk_value] - 1] = *r_iterator;
      counter_vector[chunk_value]--;
    }
    v.assign(temp.begin(), temp.end());

    std::fill(temp.begin(), temp.end(), 0);
    std::fill(counter_vector.begin(), counter_vector.end(), 0);
  }

  typename std::vector<value_type>::iterator first_negative = std::find_if(
      v.begin(), v.end(), [](value_type elem) { return (elem < 0); });
  std::vector<value_type> v_negative(first_negative, v.end());
  v_negative.shrink_to_fit();

  if (first_negative != v.begin() || first_negative != v.end()) {
    std::copy(v.begin(), first_negative, &v[v_negative.size()]);
    std::copy(v_negative.begin(), v_negative.end(), v.begin());
  }
}

#endif // _HOME_ARCHLINUX_SORTING_ALGORITHMS_RADIX_SORT_HPP
