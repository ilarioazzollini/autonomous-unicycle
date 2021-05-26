#pragma once
#include "matrix.hpp"
#include <vector>

// Map coordinate (row,column)
struct MapCoord {
  size_t row;
  size_t column;

  MapCoord& operator=(const MapCoord& other){
    row = other.row;
    column = other.column;
    return *this;
  }
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
