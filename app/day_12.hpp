#pragma once

#include <climits>
#include <stdbool.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <optional>

struct Coordinates {
  int x;
  int y;

  bool operator==(const Coordinates& other) const {
    return (this->x == other.x) && (this->y == other.y);
  }

  friend std::ostream& operator<<(std::ostream& os, const Coordinates& self) {
    return os << "x:" << self.x << ", y:" << self.y << std::endl;
  }
};

template <>
struct std::hash<Coordinates> {
  std::size_t operator()(const Coordinates& c) const {
    return (std::hash<int>()(c.x) ^ std::hash<int>()(c.y));
  }
};

struct Node {
  bool visited{};
  int height{};
  int cost_from_starting_node{ INT_MAX };
  std::vector<Coordinates> neighbours{};

  Node(const Node&) = default;
  Node(Node&&) = default;
  Node& operator=(const Node&) = default;
  Node& operator=(Node&&) = default;

  Node(char letter) {
    switch (letter) {
      case 'S':
        height = 0;
        break;
      case 'E':
        height = int('z') - int('a');
        break;
      default:
        height = int(letter) - int('a');
    }
  }

  Node(std::vector<Coordinates>&& neighbours, int cost, bool visited) :
      visited(visited),
      height(0),
      cost_from_starting_node(cost),
      neighbours(std::move(neighbours)) {}

  friend std::ostream& operator<<(std::ostream& os, const Node& self) {
    return os << "height:" << self.height << ", visited:" << self.visited << ", cost: " << self.cost_from_starting_node
              << std::endl;
  }
};

int heigth_from(char letter);
void find_neighbours(std::unordered_map<Coordinates, Node>& nodes);

std::optional<Coordinates> node_with_lowest_distance(const std::unordered_map<Coordinates, Node>& nodes);

int dijkstra(std::unordered_map<Coordinates, Node>& nodes, const Coordinates& start_node, const Coordinates& end_node);

void day_12_executor(const std::string& filename);
