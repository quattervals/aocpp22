#include <stdint.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "day_5.hpp"

#include "utils.hpp"

void crane(uint32_t quantity, uint32_t from, uint32_t to, std::vector<std::vector<char>>& dock) {
  from -= 1;
  to -= 1;

  for (int operations = 0; operations < quantity; operations++) {
    dock[to].push_back(dock[from].back());
    dock[from].pop_back();
  }
}

void crane_9001(uint32_t quantity, uint32_t from, uint32_t to, std::vector<std::vector<char>>& dock) {
  from -= 1;
  to -= 1;

  std::move(dock[from].end() - quantity, dock[from].end(), back_inserter(dock[to]));
  dock[from].erase(dock[from].end() - quantity, dock[from].end());
}

void day_5_executor(const std::string& filename) {
  std::vector<std::vector<char>> real_dock{
    {'R', 'P', 'C', 'D', 'B', 'G' },
    {'H', 'V', 'G'   },
    {'N', 'S', 'Q', 'D', 'J', 'P', 'M' },
    {'P', 'S', 'L', 'G', 'D', 'C', 'N', 'M' },
    {'J', 'B', 'N', 'C', 'P', 'F', 'L', 'S' },
    {'Q', 'B', 'D', 'Z', 'V', 'G', 'T', 'S' },
    {'B', 'Z', 'M', 'H', 'F', 'T', 'Q' },
    {'C', 'M', 'D', 'B', 'F' },
    {'F', 'C', 'Q', 'G'   }
  };

  std::cout << "this is day 5" << std::endl;

  std::ifstream file(filename);

  if (file.is_open()) {
    for (std::string line; std::getline(file, line);) {
      auto cmd = collect_numbers_to_vec(line, ' ');
      crane_9001(std::stoi(cmd[0]), std::stoi(cmd[1]), std::stoi(cmd[2]), real_dock);
    }
  }
  else {
    std::cout << "Something wrong with opening the file" << std::endl;
  }
  std::string result{};
  for (auto& stack : real_dock) {
    result.push_back(stack.back());
  }

  std::cout << "top crates are " << result << std::endl;
}
