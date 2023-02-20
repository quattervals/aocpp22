#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <deque>
#include <array>
#include <algorithm>

#include "day_12.hpp"
#include "utils.hpp"

namespace {
bool hasNeighbour(std::vector<Coordinates>& neighbours, Coordinates neighbour) {
  return std::find(neighbours.begin(), neighbours.end(), neighbour) != neighbours.end();
}
}

TEST_CASE("Day 12 Helpers") {
  SECTION("Find node with lowest distance") {
    std::unordered_map<Coordinates, Node> nodes{};
    nodes.insert({
      Coordinates{       5, 4 },
      Node({{ 4, 4 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       3, 3 },
      Node({{ 3, 4 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       3, 4 },
      Node({{ 4, 4 } },
      INT_MAX, false)
    });

    nodes.at({ 5, 4 }).cost_from_starting_node = 7;
    nodes.at({ 3, 3 }).cost_from_starting_node = 2;
    nodes.at({ 3, 3 }).visited = true;
    nodes.at({ 3, 4 }).cost_from_starting_node = 5;

    REQUIRE(Coordinates{ 3, 4 } == node_with_lowest_distance(nodes).value());
  }

  SECTION("dijkstra with two paths") {
    std::unordered_map<Coordinates, Node> nodes{};

    Coordinates start_node{ 3, 2 };
    Coordinates end_node{ 4, 4 };

    nodes.insert({
      Coordinates{start_node},
      Node({ { 4, 2 },  { 3, 3 } },
      INT_MAX, false)
    });
    nodes.insert({ Coordinates{ end_node }, Node({}, INT_MAX, false) });
    nodes.insert({
      Coordinates{       4, 2 },
      Node({{ 5, 2 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       5, 2 },
      Node({{ 5, 3 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       5, 3 },
      Node({{ 5, 4 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       5, 4 },
      Node({{ 4, 4 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       3, 3 },
      Node({{ 3, 4 } },
      INT_MAX, false)
    });
    nodes.insert({
      Coordinates{       3, 4 },
      Node({{ 4, 4 } },
      INT_MAX, false)
    });

    REQUIRE(3 == dijkstra(nodes, start_node, end_node));
  }
}

TEST_CASE("Day 12 Tests") {
  std::array<char, 4> letters{ 'a', 'b', 'c', 'b' };
  int M{ 2 };
  int N{ 2 };

  std::unordered_map<Coordinates, Node> nodes{};

  for (int m{ 0 }; m < M; m++) {
    for (int n{ 0 }; n < N; n++) {
      nodes.insert({
        Coordinates{n, m},
        Node(letters[m * N + n])
      });
    }
  }

  SECTION("fill nodes") {
    REQUIRE(nodes.at({ 0, 1 }).height == heigth_from('c'));
  }

  SECTION("find neighbours") {
    find_neighbours(nodes);

    REQUIRE(hasNeighbour(nodes.at({ 0, 0 }).neighbours, { 1, 0 }));

    REQUIRE(hasNeighbour(nodes.at({ 1, 0 }).neighbours, { 0, 0 }));
    REQUIRE(hasNeighbour(nodes.at({ 1, 0 }).neighbours, { 1, 1 }));

    REQUIRE(hasNeighbour(nodes.at({ 0, 1 }).neighbours, { 0, 0 }));
    REQUIRE(hasNeighbour(nodes.at({ 0, 1 }).neighbours, { 1, 1 }));

    REQUIRE(hasNeighbour(nodes.at({ 1, 1 }).neighbours, { 1, 0 }));
    REQUIRE(hasNeighbour(nodes.at({ 1, 1 }).neighbours, { 0, 1 }));
  }
}

TEST_CASE("Day 12 Example") {
  std::array<char, 8 * 5> letters{ 'S', 'a', 'b', 'q', 'p', 'o', 'n', 'm', 'a', 'b', 'c', 'r', 'y', 'x',
                                   'x', 'l', 'a', 'c', 'c', 's', 'z', 'E', 'x', 'k', 'a', 'c', 'c', 't',
                                   'u', 'v', 'w', 'j', 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'i' };
  int M{ 5 };
  int N{ 8 };

  std::unordered_map<Coordinates, Node> nodes{};

  Coordinates start_node{};
  Coordinates end_node{};

  for (int m{ 0 }; m < M; m++) {
    for (int n{ 0 }; n < N; n++) {
      nodes.insert({
        Coordinates{n, m},
        Node(letters[m * N + n])
      });

      if (letters[m * N + n] == 'S') {
        start_node.x = n;
        start_node.y = m;
      }
      if (letters[m * N + n] == 'E') {
        end_node.x = n;
        end_node.y = m;
      }
    }
  }

  SECTION("Constructor") {
    REQUIRE(INT_MAX == nodes.at({ 7, 4 }).cost_from_starting_node);
  }

  SECTION("fill nodes") {
    REQUIRE(nodes.at({ 7, 4 }).height == heigth_from('i'));
    REQUIRE(nodes.at({ 4, 2 }).height == heigth_from('z'));
  }

  SECTION("find neighbours") {
    find_neighbours(nodes);

    REQUIRE(hasNeighbour(nodes.at({ 0, 0 }).neighbours, { 1, 0 }));
    REQUIRE(hasNeighbour(nodes.at({ 0, 0 }).neighbours, { 0, 1 }));
    REQUIRE(2 == nodes.at({ 0, 0 }).neighbours.size());

    REQUIRE(hasNeighbour(nodes.at({ 5, 3 }).neighbours, { 6, 3 }));
    REQUIRE(hasNeighbour(nodes.at({ 5, 3 }).neighbours, { 5, 4 }));
    REQUIRE(hasNeighbour(nodes.at({ 5, 3 }).neighbours, { 4, 3 }));
    REQUIRE(3 == nodes.at({ 5, 3 }).neighbours.size());
  }

  SECTION("find shortest path") {
    find_neighbours(nodes);
    int path_length = dijkstra(nodes, start_node, end_node);
    REQUIRE(31 == path_length);
  }
}
