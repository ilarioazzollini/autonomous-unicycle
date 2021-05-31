#include "planning/a_star.hpp"
#include <algorithm> // std::sort, std::find
#include <math.h>
#include <iostream>

struct Node {
  MapCoord previous_point;
  MapCoord this_point;
  double cost_g; // Dijkstra's cost
  double cost_h; // Greedy's cost  
};

inline bool operator<(Node node1, Node node2) {
  if (node1.cost_g == node2.cost_g){
    return (node1.cost_h < node2.cost_h);
  }
  else {
      return (node1.cost_g + node1.cost_h < node2.cost_g + node2.cost_h);
  }
};

inline bool operator==(Node node1, Node node2) {
  return (node1.previous_point == node2.previous_point) && (node1.this_point == node2.this_point) && (node1.cost_g == node2.cost_g) && (node1.cost_h == node2.cost_h);
};


// Constructor definition
AStar::AStar() {

}

std::vector<MapCoord> AStar::get_neighbors(const Matrix& occupancy_matrix, const MapCoord& current_point) {
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

double AStar::get_cost_value(const MapCoord& this_point, const MapCoord& end_point){

    double cost_value = std::abs(static_cast<int>(end_point.row) - static_cast<int>(this_point.row)) + 
                std::abs(static_cast<int>(end_point.column) - static_cast<int>(this_point.column)); // Manhattan distance

    return cost_value;
}

std::vector<MapCoord> AStar::compute_plan(const Matrix& occupancy_matrix, const MapCoord& starting_point, const MapCoord& end_point) {
    MapCoord current_point;
    MapCoord new_point;
    Node new_node;
    std::vector<MapCoord> neighbors;
    std::vector<Node> explored_nodes;
    std::vector<Node> visited_nodes;
    double current_cost_g;

    // Print occupancy matrix
    std::cout<<"occupancy matrix \n" << occupancy_matrix << std::endl;

    // Create the initial node and set it as the first explored node
    new_node.this_point = starting_point;
    new_node.previous_point = starting_point;
    new_node.cost_g = 0;
    new_node.cost_h = get_cost_value(current_point,end_point);
    explored_nodes.push_back(new_node);

    // Initialization
    current_point = starting_point;

    std::cout<< explored_nodes.size() <<std::endl;

    while (!explored_nodes.empty()){

        // Sort the list of explored nodes
        std::sort (explored_nodes.begin(), explored_nodes.end());

        // The first node has the min cost so it's the best -> move there and go visit
        visited_nodes.push_back(explored_nodes[0]);
        current_point = explored_nodes[0].this_point; // Update current_point
        current_cost_g = explored_nodes[0].cost_g; // Update current_point

        std::cout<<"current point"<<std::endl;
        std::cout<<"x: "<< current_point.row << " y: "<<current_point.column<<std::endl;

        std::cout<<"current cost"<<std::endl;
        std::cout<<"cost_g: "<< explored_nodes[0].cost_g << " cost_h: "<<explored_nodes[0].cost_h<<std::endl;

        explored_nodes.erase (explored_nodes.begin()); // Erase it from the explored, it will not be an option in the future

        if (current_point == end_point){
            break;
        }

            // Explore: 1) Get neighbors and
            //          2) compute the related costs and
            //          3) push them inside the list of explored nodes
        neighbors = get_neighbors(occupancy_matrix, current_point);


        for (size_t i=0; i < neighbors.size(); i++){
            new_point = neighbors[i];
            std::cout<<"neighbor: "<< new_point.row << " "<< new_point.column<<std::endl;
            bool found = false;
            for (size_t j = 0; j < explored_nodes.size(); j++) {
                if (explored_nodes[j].this_point == new_point) {
                    std::cout<<"Found in explored"<<std::endl;
                    found = true;
                }
            }
            for (size_t j = 0; j < visited_nodes.size(); j++) {
                if (visited_nodes[j].this_point == new_point) {
                    std::cout<<"Found in visited"<<std::endl;
                    found = true;
                }
            }

            if (!found) {
                new_node.this_point = new_point;
                new_node.previous_point = current_point;
                new_node.cost_g = current_cost_g + 1;
                new_node.cost_h = get_cost_value(new_point,end_point);
                std::cout<<"Add neighbor with cost G "<< new_node.cost_g << " H "<< new_node.cost_h<<std::endl;
                explored_nodes.push_back(new_node);
            }
        }


    }

    // Final plan reconstruction
    std::vector<MapCoord> final_plan;

    Node plan_node = visited_nodes[visited_nodes.size() - 1];

    if (plan_node.this_point != end_point) {
        return final_plan;
    }

    final_plan.push_back(plan_node.this_point);

    while(plan_node.this_point != starting_point) {
        for (size_t w = 0; w < visited_nodes.size(); w++){
            if (visited_nodes[w].this_point == plan_node.previous_point){
                plan_node = visited_nodes[w];
                break;
            }
        }
        final_plan.push_back(plan_node.this_point);
    }

    // Reverse the order in order to have the plan from start to end
    std::reverse(final_plan.begin(),final_plan.end());

    return final_plan;

}
