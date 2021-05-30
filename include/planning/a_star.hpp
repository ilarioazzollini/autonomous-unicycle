#pragma once
#include "matrix.hpp"
#include <vector>

// Position in the matrix: (row,column)
struct MapCoord {
  size_t row;
  size_t column;
};

inline bool operator==(const MapCoord& point1, const MapCoord& point2) {
  return (point1.row == point2.row) && (point1.column == point2.column);
};

inline bool operator!=(const MapCoord& point1, const MapCoord& point2) {
  return (point1.row != point2.row) || (point1.column != point2.column);
};

class AStar {
public:
    // Constructor
    AStar();

    // Compute Plan function -> gives as output an ordered vector of nodes
    std::vector<MapCoord> compute_plan(const Matrix& occupancy_matrix, const MapCoord& starting_point, const MapCoord& end_point);

private:
    // Get feasible neighbors 
    std::vector<MapCoord> get_neighbors(const Matrix& occupancy_matrix, const MapCoord& current_point);
    // Compute cost
    double get_cost_value(const MapCoord& this_point, const MapCoord& end_point);
};

