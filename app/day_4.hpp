#pragma once

#include <stdint.h>
#include <stdbool.h>

struct section_ids_of_pair {
  struct section_1 {
    int lower;
    int upper;
  } first;

  struct section_2 {
    int lower;
    int upper;
  } second;

  bool operator==(const section_ids_of_pair& rhs) const {
    if (first.lower == rhs.first.lower && first.upper == rhs.first.upper && second.lower == rhs.second.lower &&
        second.upper == rhs.second.upper) {
      return true;
    }
    else {
      return false;
    }
  }

  bool operator!=(const section_ids_of_pair& rhs) const {
    return ! (*this == rhs);
  }
};

void day_4_executor(const std::string& filename);
section_ids_of_pair from_input(const std::string& line);

bool one_contains_the_other(section_ids_of_pair& pair);
