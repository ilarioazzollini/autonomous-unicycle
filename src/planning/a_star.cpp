#include "planning/a_star.hpp"
#include <algorithm> // std::sort, std::find
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

    double cost_value = std::abs(static_cast<int>(end_point.row) - static_cast<int>(this_point.row)) + 
                std::abs(static_cast<int>(end_point.column) - static_cast<int>(this_point.column)); // Manhattan distance

                // maybe an Euclidian distance should be better?

    return cost_value;
}

std::vector<Node> AStar::compute_plan(Matrix occupancy_matrix, MapCoord starting_point, MapCoord end_point) {
    MapCoord current_point;
    MapCoord new_point;
    Node new_node;
    std::vector<MapCoord> neighbors;
    std::vector<Node> explored_nodes;
    std::vector<Node> visited_nodes;
    double current_cost_g = 0; // starting point cost_g

    // Create the initial node and set it as the first explored node
    new_node.this_node = starting_point;
    new_node.previous_node = starting_point;
    new_node.cost_g = current_cost_g;
    new_node.cost_h = get_cost_value(current_point,end_point);
    explored_nodes.push_back(new_node);

    // Initialization
    current_point = starting_point;

    while ( (explored_nodes.size()!= 0) && (current_point != end_point) ){

        // Sort the list of explored nodes
        std::sort (explored_nodes.begin(), explored_nodes.end());

        // The first node has the min cost so it's the best -> move there and go visit
        visited_nodes.push_back(explored_nodes[0]);
        current_point = explored_nodes[0].this_point; // Update current_point
        explored_nodes.erase (explored_nodes.begin()); // Erase it from the explored, it will not be an option in the future

        while (current_point != end_point){

            // Explore: 1) Get neighbors and
            //          2) compute the related costs and
            //          3) push them inside the list of explored nodes
            neighbors = get_neighbors(occupancy_matrix, current_point);
            if (neighbors.size() != 0){
                current_cost_g++; // Increment the Dijkstra's cost
                for (size_t i=0; i < neighbors.size(); i++){
                    new_point = neighbors[i];
                    new_node.this_node = new_point;
                    new_node.previous_node = current_point;
                    new_node.cost_g = current_cost_g;
                    new_node.cost_h = get_cost_value(new_point,end_point);
                    explored_nodes.push_back(new_node);
                }
            }

        }


    }

    // Final plan reconstruction
    std::vector<Node> final_plan;

    // Notice that at this point we know the plan consists of (current_cost_g + 1) points
    // We start by pushing the last visited node (which, hopefully, is the end point - if the problem was feasible -)
    size_t vis_size = visited_nodes.size();
    size_t k = vis_size - 1;

    for (size_t j=0; j <= current_cost_g; j++){

        final_plan.push_back(visited_nodes[k]);
        new_point = visited_nodes[k].previous_point;

        for (size_t w = 0; w < vis_size; w++){
            if (visited_nodes[w].this_point == new_point){
                k = w;
            }
        }


    }

    // Reverse the order in order to have the plan from start to end
    std::reverse(final_plan.begin(),final_plan.end());

    return final_plan;

}
