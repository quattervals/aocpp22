#include <stdint.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "day_4.hpp"
#include "utils.hpp"

void day_4_executor(const std::string& filename) {
  std::cout << "this is day four" << std::endl;

  int count_fully_containing{ 0 };
  int count_partial_containing{ 0 };
  std::ifstream file(filename);

  if (file.is_open()) {
    for (std::string line; std::getline(file, line);) {
      section_ids_of_pair pair = from_input(line);
      if (one_contains_the_other(pair)) {
        count_fully_containing += 1;
      }
      if (partial_overlap(pair)) {
        count_partial_containing += 1;
      }
    }
  }
  else {
    std::cout << "Something wrong with opening the file" << std::endl;
  }

  std::cout << "Number of fully contained items is " << count_fully_containing << std::endl;
  std::cout << "Number of partially contained items is " << count_partial_containing << std::endl;
}

section_ids_of_pair from_input(const std::string& line) {
  section_ids_of_pair pairs{};

  if (! line.empty()) {
    std::vector<std::string> first_split = split_to_vec(line, ',');

    std::vector<std::string> first_range = split_to_vec(first_split[0], '-');
    pairs.first.lower = std::stoi(first_range[0]);
    pairs.first.upper = std::stoi(first_range[1]);

    std::vector<std::string> second_range = split_to_vec(first_split[1], '-');
    pairs.second.lower = std::stoi(second_range[0]);
    pairs.second.upper = std::stoi(second_range[1]);
  }
  return pairs;
}

bool one_contains_the_other(const section_ids_of_pair& pair) {
  if (pair.first.lower <= pair.second.lower && pair.first.upper >= pair.second.upper) {
    return true;
  }
  else if (pair.second.lower <= pair.first.lower && pair.second.upper >= pair.first.upper) {
    return true;
  }
  else {
    return false;
  }
}

bool partial_overlap(const section_ids_of_pair& pair) {
  if (pair.second.lower <= pair.first.lower && pair.first.lower <= pair.second.upper) {
    return true;
  }
  else if (pair.second.lower <= pair.first.upper && pair.first.upper <= pair.second.upper) {
    return true;
  }
  else if (one_contains_the_other(pair)) {
    return true;
  }
  else {
    return false;
  }
}
