#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include "day_1.hpp"



TEST_CASE("Simple Day One Tester", "[day_1_testable]") {
  REQUIRE(day_1_testable(4) == 46);
}