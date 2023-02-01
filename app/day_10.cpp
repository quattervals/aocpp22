#include <stdint.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string_view>

#include "day_10.hpp"

#include "utils.hpp"

inline constexpr auto hash_djb2a(const std::string_view sv) {
  unsigned long hash{ 5381 };
  for (unsigned char c : sv) {
    hash = ((hash << 5) + hash) ^ c;
  }
  return hash;
}

inline constexpr auto operator"" _sh(const char* str, size_t len) {
  return hash_djb2a(std::string_view{ str, len });
}

int sum_of_six(std::vector<int>& reg, int start = 19, int increment = 40, int num = 6) {
  int sum{ 0 };
  for (int i = start; i < start + num * increment; i += increment) {
    auto to_add = reg[i] * (i + 1);
    sum += to_add;
  }
  return sum;
}

int addx(std::vector<int>& reg, int op, int pass_on) {
  reg.emplace_back(pass_on);
  reg.emplace_back(pass_on);

  return reg.back() + op;
}

int noop(std::vector<int>& reg, int pass_on) {
  reg.emplace_back(pass_on);   // does it make a copy?}
  return pass_on;
}

bool drawSolid(int idx, int val) {
  int idx_off_by_one = (idx +0) % 40;

  if (idx_off_by_one <= val + 1 && idx_off_by_one >= val - 1) {
    return true;
  }
  else {
    return false;
  }
}

void day_10_executor(const std::string& filename) {
  std::cout << "this is day 10" << std::endl;

  std::ifstream file(filename);

  std::vector<int> alu_register;
  int pass_on{ 1 };

  if (file.is_open()) {
    for (std::string line; std::getline(file, line);) {
      std::string operation = line.substr(0, 4);
      auto pos = line.find(" ");
      int val = 0;
      if (std::string::npos != pos) {
        val = std::stoi(line.substr(5));
      }

      switch (hash_djb2a(operation)) {
        case "noop"_sh:
          pass_on = noop(alu_register, pass_on);
          break;
        case "addx"_sh:
          pass_on = addx(alu_register, val, pass_on);
          break;
        default:
          break;
      }

      std::cout << "operation: " << operation << ", val: " << val << std::endl;
    }
  }
  else {
    std::cout << "Something wrong with opening the file" << std::endl;
  }

  print_vector(alu_register);

  int sum_part_1 = sum_of_six(alu_register);
  std::cout << "Sum of six is " << sum_part_1 << std::endl;   //15000 too high
}
