#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "day_5.hpp"

TEST_CASE("Day 5 Tests", "[day_4_from_input]") {
  SECTION("move Dock") {
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
}
