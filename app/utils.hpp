#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>

std::vector<std::string> split_to_vec(const std::string& in, const char delim);
std::vector<std::string> collect_numbers_to_vec(const std::string& in, const char delim);

template <typename T>
void print_vector(std::vector<T> const& input) {
  std::copy(input.begin(), input.end(), std::ostream_iterator<T>(std::cout, ", "));
  std::cout << std::endl;
}

/// @brief copy part of a vector
/// @tparam T
/// @param v original
/// @param m from
/// @param n to
/// @return new vector
template <typename T>
std::vector<T> copy_slice(std::vector<T> const& v, int m, int n) {
  auto first = v.cbegin() + m;
  auto last = v.cbegin() + n + 1;

  std::vector<T> vec(first, last);   // range constructor
  return vec;
}

template <typename Key, typename Item>
void print_map(std::unordered_map<Key, Item> const& m) {
  for (auto const& keyValPair : m) {
    std::cout << "{" << keyValPair.first << keyValPair.second << "}\n";
  }
}
