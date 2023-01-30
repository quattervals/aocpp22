#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <deque>

#include "day_10.hpp"

TEST_CASE("Day 10 Tests") {
  SECTION("addx") {
    std::vector<int> reg;

    auto ret = addx(reg, 4, 1);

    REQUIRE(reg[0] == 1);
    REQUIRE(reg[1] == 1);
    REQUIRE(ret == 5);
  }
  SECTION("noop") {
    std::vector<int> reg;

    noop(reg, 1);

    REQUIRE(reg[0] == 1);
  }
}
