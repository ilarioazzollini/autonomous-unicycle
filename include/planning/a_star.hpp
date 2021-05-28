#pragma once
#include "matrix.hpp"
#include <vector>

// Position in the matrix: (row,column)
struct MapCoord {
  size_t row;
  size_t column;
};

struct Node {
  MapCoord previous_point;
  MapCoord this_point;
  double cost_g; // Dijkstra's cost
  double cost_h; // Greedy's cost  
}

inline bool operator==(MapCoord point1, MapCoord point2) {
  return (point1.row == point2.column) && (point1.row == point2.column);
};

inline bool operator!=(MapCoord point1, MapCoord point2) {
  return (point1.row != point2.column) || (point1.row != point2.column);
};

inline bool operator<(Node node1, Node node2) {
  return ( (node1.cost_g + node1.cost_h) < (node2.cost_g + node2.cost_h) );
};

inline bool operator==(Node node1, Node node2) {
  return (node1.previous_point == node2.previous_point) && (node1.this_point == node2.this_point) && (node1.cost_g == node2.cost_g) && (node1.cost_h == node2.cost_h);
};

class AStar {
public:
    // Constructor
    AStar();

    // Compute Plan function -> gives as output an ordered vector of nodes
    std::vector<Node> compute_plan(Matrix occupancy_matrix, MapCoord starting_point, MapCoord end_point);

private:
    // Get feasible neighbors 
    std::vector<MapCoord> get_neighbors(Matrix occupancy_matrix, MapCoord current_point);
    // Compute cost
    double get_cost_value(MapCoord this_point, MapCoord end_point);
};

