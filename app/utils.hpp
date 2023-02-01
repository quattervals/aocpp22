#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <algorithm>
#include <iterator>

std::vector<std::string> split_to_vec(const std::string& in, const char delim);
std::vector<std::string> collect_numbers_to_vec(const std::string& in, const char delim);

template <typename T>
void print_vector(std::vector<T> const& input) {
  std::copy(input.begin(), input.end(), std::ostream_iterator<T>(std::cout, ", "));
  std::cout << std::endl;
}
