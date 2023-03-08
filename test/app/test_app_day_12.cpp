#include <cstdint>
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <deque>
#include <array>
#include <algorithm>
#include <ranges>

#include "day_12.hpp"


namespace {
bool hasNeighbour(std::vector<Coordinates>& neighbours, Coordinates neighbour) {
  return std::find(neighbours.begin(), neighbours.end(), neighbour) != neighbours.end();
}

std::vector<Coordinates> coordinates_of_low_nodes(std::unordered_map<Coordinates, Node>& nodes) {
  std::vector<Coordinates> low_nodes{};
  for (auto& node : nodes) {
    if (node.second.height == 0) {
      low_nodes.push_back(node.first);
    }
  }
  return low_nodes;
}

}

TEST_CASE("Day 12 Helpers") {
  SECTION("Find node with lowest distance") {
    std::unordered_map<Coordinates, Node> nodes{};
    nodes.insert({
      Coordinates{       5, 4 },
      Node({{ 4, 4 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       3, 3 },
      Node({{ 3, 4 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       3, 4 },
      Node({{ 4, 4 } },
      INIT_VAL, false)
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
      INIT_VAL, false)
    });
    nodes.insert({ Coordinates{ end_node }, Node({}, INIT_VAL, false) });
    nodes.insert({
      Coordinates{       4, 2 },
      Node({{ 5, 2 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       5, 2 },
      Node({{ 5, 3 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       5, 3 },
      Node({{ 5, 4 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       5, 4 },
      Node({{ 4, 4 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       3, 3 },
      Node({{ 3, 4 } },
      INIT_VAL, false)
    });
    nodes.insert({
      Coordinates{       3, 4 },
      Node({{ 4, 4 } },
      INIT_VAL, false)
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
    REQUIRE(INIT_VAL == nodes.at({ 7, 4 }).cost_from_starting_node);
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

  SECTION("Find all lowest ('a') nodes") {
    auto view_to_low_nodes = nodes | std::views::filter([](auto& v) {
                               return v.second.height == 0;
                             });

    // copy nodes matching zero height to vector for convenience
    // otherwise, we have to check the contents like this or find better helpers
    REQUIRE(std::find_if(view_to_low_nodes.begin(), view_to_low_nodes.end(), [](auto& s) {
              return s.first == Coordinates{ 0, 0 };
            }) != view_to_low_nodes.end());

    std::vector<Coordinates> low_nodes = coordinates_of_low_nodes(nodes);

    REQUIRE(std::find(low_nodes.begin(), low_nodes.end(), Coordinates{ 1, 0 }) != low_nodes.end());
    REQUIRE(std::find(low_nodes.begin(), low_nodes.end(), Coordinates{ 0, 1 }) != low_nodes.end());
    REQUIRE(std::find(low_nodes.begin(), low_nodes.end(), Coordinates{ 0, 2 }) != low_nodes.end());
    REQUIRE(std::find(low_nodes.begin(), low_nodes.end(), Coordinates{ 0, 3 }) != low_nodes.end());
    REQUIRE(std::find(low_nodes.begin(), low_nodes.end(), Coordinates{ 0, 4 }) != low_nodes.end());
  }

  SECTION("find path lengths for all lowest nodes") {
    auto view_to_low_nodes = nodes | std::views::filter([](auto& v) {
                               return v.second.height == 0;
                             });

    find_neighbours(nodes);

    std::vector<int> shortest_paths{};
    for (auto& low_node : view_to_low_nodes) {
      shortest_paths.push_back(dijkstra(nodes, low_node.first, end_node));
    }

    REQUIRE(6 == shortest_paths.size());
    REQUIRE(29 == *std::min_element(shortest_paths.begin(), shortest_paths.end()));
  }
}
