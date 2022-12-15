#include <stdint.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "utils.hpp"

std::vector<std::string> split_to_vec(const std::string& in, const char delim) {
  std::string s;
  std::vector<std::string> out;
  if (! in.empty()) {
    std::stringstream ss(in);
    while (std::getline(ss, s, delim)) {
      out.push_back(s);
    }
  }
  return out;
}

std::vector<std::string> collect_numbers_to_vec(const std::string& in, const char delim) {
  std::string s;
  std::vector<std::string> out;
  if (! in.empty()) {
    std::stringstream ss(in);
    while (std::getline(ss, s, delim)) {
      if (all_of(s.begin(), s.end(), isdigit)) {
        out.push_back(s);
      }
    }
  }
  return out;
}