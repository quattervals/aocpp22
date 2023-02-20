#include <cstddef>
#include <stdint.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>
#include <unordered_map>

#include "day_12.hpp"

#include "utils.hpp"

int heigth_from(char letter) {
  return int(letter) - int('a');
}

void find_neighbours(std::unordered_map<Coordinates, Node>& nodes) {
  for (auto& n : nodes) {
    std::array<Coordinates, 4> neighbourKeys{ n.first.x + 1, n.first.y,     n.first.x - 1, n.first.y,
                                              n.first.x,     n.first.y + 1, n.first.x,     n.first.y - 1 };

    for (auto& nbor : neighbourKeys) {
      if (const auto neighbour = nodes.find(nbor); neighbour != nodes.end()) {
        if (n.second.height + 1 >= neighbour->second.height) {
          n.second.neighbours.push_back(nbor);
        }
      }
    }
  }
}

std::optional<Coordinates> node_with_lowest_distance(const std::unordered_map<Coordinates, Node>& nodes) {
  /*
  Can't work with std::min_element(begin, end, comp).
   In case no suitable min_element ist found, begin is returned, which might be non-sense
*/

  auto best_fit = nodes.end();
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    if (! it->second.visited && best_fit == nodes.end()) {
      best_fit = it;   // the first un-visited is our best guess
    }
    else if ((! it->second.visited) &&
             (it->second.cost_from_starting_node < best_fit->second.cost_from_starting_node)) {
      best_fit = it;
    }
  }

  if (best_fit != nodes.end()) {
    return best_fit->first;
  }
  else {
    return std::nullopt;
  }
}

int dijkstra(std::unordered_map<Coordinates, Node>& nodes, const Coordinates& start_node, const Coordinates& end_node) {
  nodes.at(start_node).cost_from_starting_node = 0;

  auto key_current_node = node_with_lowest_distance(nodes);
  while (key_current_node) {
    auto& current_node = nodes.at(key_current_node.value());

    for (auto& neighour : current_node.neighbours) {
      nodes.at(neighour).cost_from_starting_node =
        std::min(current_node.cost_from_starting_node + 1, nodes.at(neighour).cost_from_starting_node);
    }
    current_node.visited = true;

    key_current_node = node_with_lowest_distance(nodes);
  };

  return nodes.at(end_node).cost_from_starting_node;
}

void day_12_executor(const std::string& filename) {
  std::cout << "=== this is day 10 ===" << std::endl;

  std::ifstream file(filename);

  std::unordered_map<Coordinates, Node> nodes{};

  Coordinates start_node{};
  Coordinates end_node{};
  int num_rows{ 0 };
  int num_cols{ 0 };

  if (file.is_open()) {
    for (std::string line; std::getline(file, line);) {
      num_cols = line.size();

      for (size_t l{ 0 }; l < line.size(); l++) {
        Coordinates key{ int(l), num_rows };
        Node node(line[l]);
        nodes.insert({ key, node });

        if (line[l] == 'S') {
          start_node.x = int(l);
          start_node.y = num_rows;
        }
        if (line[l] == 'E') {
          end_node.x = int(l);
          end_node.y = num_rows;
        }
      }

      num_rows++;
    }
  }

  else {
    std::cout << "Something wrong with opening the file" << std::endl;
  }

  std::cout << "Part One" << std::endl;
  find_neighbours(nodes);
  int path_length = dijkstra(nodes, start_node, end_node);

  std::cout << "Length to the top is " << path_length << std::endl;
}
