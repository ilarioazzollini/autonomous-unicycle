#include "motion_planning/a_star.hpp"
#include <math.h>
#include <iostream>

// Constructor definition
AStar::AStar() {

}

std::vector<MapCoord> AStar::get_neighbors(Matrix occupancy_matrix, MapCoord current_point) {
    std::vector<MapCoord> neighbors;
    MapCoord neig;

    neig.row = current_point.row - 1;
    neig.column = current_point.column;
    if (current_point.row != 0 && occupancy_matrix[neig.row][neig.column]!= 0){
        neighbors.push_back(neig);
    }

    neig.row = current_point.row;
    neig.column = current_point.column + 1;
    if (current_point.column != (occupancy_matrix.columns()-1) && occupancy_matrix[neig.row][neig.column]!= 0){
        neighbors.push_back(neig);
    }

    neig.row = current_point.row + 1;
    neig.column = current_point.column;
    if (current_point.row != (occupancy_matrix.rows()-1) && occupancy_matrix[neig.row][neig.column]!= 0){
        neighbors.push_back(neig);
    }

    neig.row = current_point.row;
    neig.column = current_point.column-1;
    if (current_point.column != 0 && occupancy_matrix[neig.row][neig.column]!= 0){
        neighbors.push_back(neig);
    }

    return neighbors;
}

double AStar::get_cost_value(MapCoord this_point, MapCoord end_point){
    double cost_value;

    cost_value = std::abs(static_cast<int>(end_point.row) - static_cast<int>(this_point.row)) + 
                std::abs(static_cast<int>(end_point.column) - static_cast<int>(this_point.column));

    return cost_value;
}

std::vector<MapCoord> AStar::compute_plan(Matrix occupancy_matrix, MapCoord starting_point, MapCoord end_point) {
    MapCoord current_point;
    std::vector<MapCoord> visited_points;
    double min_cost;
    MapCoord best_neighbor;
    std::vector<MapCoord> neighbors;

    // Initialization
    current_point = starting_point;
    neighbors = get_neighbors(occupancy_matrix, current_point);
    min_cost = 1000;
    best_neighbor = current_point;
    visited_points.push_back(current_point);
    int k = 0;

    while ((current_point.row != end_point.row) || (current_point.column != end_point.column)){
        k++;

        if (k > 15){
            break;
        }

        neighbors = get_neighbors(occupancy_matrix, current_point);

        for (size_t i=0; i < neighbors.size(); i++){
            double current_cost = get_cost_value(neighbors[i],end_point);
            std::cout<< "neighbor row " << neighbors[i].row << " neighbor column " << neighbors[i].column <<std::endl;
            std::cout<< "current cost: " << current_cost << std::endl;
            if (current_cost < min_cost){
                bool already_visited = false;
                for (size_t j=0; j < visited_points.size(); j++){
                    if (visited_points[j].row==neighbors[i].row && visited_points[j].column==neighbors[i].column){
                        already_visited = true;
                    }
                }
                if (!already_visited){
                    min_cost = current_cost;
                    best_neighbor = neighbors[i];
                }
            }
        }

        current_point = best_neighbor;
        visited_points.push_back(current_point);

        std::cout<< "row " << current_point.row << " column " << current_point.column <<std::endl;

    }

    return visited_points;

}
