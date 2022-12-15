#include <stdint.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <string>

#include "day_4.hpp"

void day_4_executor(const std::string& filename) {
  std::cout << "this is day four" << std::endl;

  std::ifstream file(filename);

  if (file.is_open()) {
    for (std::string line; std::getline(file, line);) {
      std::cout << line << std::endl;
    }
  }
  else {
    std::cout << "Something wrong with opening the file" << std::endl;
  }
}
