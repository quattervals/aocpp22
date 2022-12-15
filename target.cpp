#include <iostream>
#include <string>

#include "app/day_1.hpp"
#include "app/day_4.hpp"

int main() {
  std::cout << "hi from main" << std::endl;

  day_1_executor();

  day_4_executor("inputs/day_4_example.txt");

  return 0;
}
