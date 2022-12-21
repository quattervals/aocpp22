#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include<iostream>

#include "day_5.hpp"

TEST_CASE("Day 5 Tests", "[day_4_from_input]") {
  SECTION("move Dock with crane 9000") {
    std::vector<std::vector<char>> testdock{
      {'Z', 'N' },
      {'M', 'C', 'D' },
      {'P'   }
    };

    std::vector<std::vector<char>> expected_dock{
      {'Z', 'N', 'D' },
      {'M', 'C' },
      {'P'   }
    };
    crane(1, 2, 1, testdock);
    REQUIRE(expected_dock == testdock);
  }

  SECTION("move Dock with crane 9001") {
    std::vector<std::vector<char>> testdock{
      {'Z',  'N', 'D' },
      {
       'M', 'C',
       },
      {'P'    }
    };

    std::vector<std::vector<char>> expected_dock{
      {   },
      { 'M',     'C'},
      { 'P', 'Z', 'N', 'D' }
    };
    crane_9001(3, 1, 3, testdock);
    REQUIRE(expected_dock == testdock);
  }
}
