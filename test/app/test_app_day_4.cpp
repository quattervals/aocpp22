#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include "day_4.hpp"

section_ids_of_pair from_input(const std::string& line);

TEST_CASE("Simple Day 4 Tester", "[day_4_from_input]") {
  SECTION("input with empty string") {
    std::string input{};
    section_ids_of_pair empty_ids{};
    REQUIRE(empty_ids == from_input(input));
  }

  SECTION("input with valid string") {
    section_ids_of_pair ids{
      .first{.lower{ 2 }, .upper{ 3 }},
      .second{.lower{ 4 }, .upper{ 5 }}
    };
    REQUIRE(ids == from_input("2-3,4-5"));
  }

  SECTION("one contains the other") {
    section_ids_of_pair ids{
      .first{.lower{ 1 }, .upper{ 5 }},
      .second{.lower{ 2 }, .upper{ 5 }}
    };
    REQUIRE(true == one_contains_the_other(ids));
  }

  SECTION("none  contains the other") {
    section_ids_of_pair ids{
      .first{ .lower{ 1 },  .upper{ 5 }},
      .second{.lower{ 29 }, .upper{ 50 }}
    };
    REQUIRE(false == one_contains_the_other(ids));
  }

  SECTION("none partial overlap") {
    section_ids_of_pair ids{
      .first{ .lower{ 1 },  .upper{ 5 }},
      .second{.lower{ 29 }, .upper{ 50 }}
    };
    REQUIRE(false == partial_overlap(ids));
  }
}
