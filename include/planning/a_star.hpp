#pragma once
#include "matrix.hpp"
#include <vector>

// Map coordinate (row,column)
struct MapCoord {
  size_t row;
  size_t column;
};

inline bool operator==(MapCoord coord1, MapCoord coord2) {
  return (coord1.row == coord2.column) && (coord1.row == coord2.column);
};

inline bool operator!=(MapCoord coord1, MapCoord coord2) {
  return (coord1.row != coord2.column) || (coord1.row != coord2.column);
};

class AStar {
public:
    // Constructor
    AStar();

    // Compute Plan function -> gives as output an ordered vector of points
    std::vector<MapCoord> compute_plan(Matrix occupancy_matrix, MapCoord starting_point, MapCoord end_point);

private:
    // Get neighbors
    std::vector<MapCoord> get_neighbors(Matrix occupancy_matrix, MapCoord current_point);
    // Compute cost
    double get_cost_value(MapCoord this_point, MapCoord end_point);
};
