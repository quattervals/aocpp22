#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <deque>

#include "day_5.hpp"

TEST_CASE("Day 5 Tests", "[day_4_from_input][.]") {
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

  SECTION("Demonstrate C++'s bizzare move - leaves 'unspecified' vector items behind") {
    std::deque<std::string> v_from;
    std::deque<std::string> v_to;

    std::string s{ " some characters" };

    for (size_t i = 0; i < 10; i++) {
      v_from.push_back(std::to_string(i) + s);
      v_to.push_back(std::to_string(i + 10) + s);
    }

    for (auto& item : v_to) {
      std::cout << "Before move: " << item.substr(item.size() - 2) << " @ " << &item << std::endl;
    }

    constexpr size_t number_items_to_move{ 2 };
    std::move(v_from.end() - number_items_to_move, v_from.end(), std::back_inserter(v_to));

    // The thing that is pointed to is removed. In case of strings, the actual characters are not copied.
    // But the string object in the moved_from vector is empty

    // To remove the unused items, we would have to
    // v_from.erase(v_from.end() - number_items_to_move, v_from.end());

    std::cout << "v_from still contains " << std::endl;
    for (auto& item : v_from) {
      std::cout << "After move: " << item << " @ " << &item << std::endl;
    }
    std::cout << "v_to now contains " << std::endl;
    for (auto& item : v_to) {
      std::cout << item << " @ " << &item << std::endl;
    }
  }
}
