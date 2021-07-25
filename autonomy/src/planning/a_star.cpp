#include "autonomy/planning/a_star.hpp"
#include <algorithm> // std::sort, std::find
#include <math.h>
#include <iostream>
#include <list>
struct Node {
  Node* previous_node;
  MapCoord this_point;
  double cost_g; // Dijkstra's cost
  double cost_h; // Greedy's cost  
};

inline bool operator<(const Node& node1, const Node& node2) {
  if (node1.cost_g == node2.cost_g){
    return (node1.cost_h < node2.cost_h);
  }
  else {
      return (node1.cost_g + node1.cost_h < node2.cost_g + node2.cost_h);
  }
};

inline bool operator==(const Node& node1, const Node& node2) {
  return (node1.this_point == node2.this_point);
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
    // We want to use pointers to visited nodes to represent the previous node for efficient lookup.
    // This requires that we don't use a vector to store these data.
    // A vector data-structure is stored in contiguous memory and operations such as `push_back`, `erase`, etc
    // may result in moving the structure to a whole different location in memory, thus invalidating all pointers we may
    // have stored.
    // On the other hand, a list is not stored in a contiguous region of memory and thus pointers are guaranteed to remain
    // valid across the aforementioned operations.
    std::list<Node> visited_nodes;
    std::vector<Node> available_nodes;

    // Print occupancy matrix
    std::cout<<"occupancy matrix \n" << occupancy_matrix << std::endl;

    // Create the initial node and set it as the first explored node
    Node starting_node;
    starting_node.this_point = starting_point;
    starting_node.previous_node = nullptr;
    starting_node.cost_g = 0;
    starting_node.cost_h = get_cost_value(starting_node.this_point, end_point);
    available_nodes.push_back(starting_node);

    while (available_nodes.size()!= 0){

        // Sort the list of explored nodes
        std::sort(available_nodes.begin(), available_nodes.end());

        Node current_node = available_nodes.front();
        available_nodes.erase(available_nodes.begin()); // Erase it from the available, it will not be an option in the future

        // The first node has the min cost so it's the best -> move there and go visit
        visited_nodes.push_back(current_node);
        auto previous_node = &(visited_nodes.back());

        std::cout
            <<"current point: " << current_node.this_point.row << " " <<current_node.this_point.column
            << " with cost g: " << current_node.cost_g << " h: " << current_node.cost_h << std::endl;

        if (current_node.this_point == end_point){
            break;
        }

        // Explore: 1) Get neighbors and
        //          2) compute the related costs and
        //          3) push them inside the list of available nodes
        std::vector<MapCoord> neighbors = get_neighbors(occupancy_matrix, current_node.this_point);

        for (size_t i=0; i < neighbors.size(); i++){

            Node neighbor_node;
            neighbor_node.this_point = neighbors[i];
            neighbor_node.previous_node = previous_node;
            neighbor_node.cost_g = current_node.cost_g + 1;
            neighbor_node.cost_h = get_cost_value(neighbor_node.this_point, end_point);
            
            // We add the neighbor node to the available list only if it's not already included among the available or visited ones
            if (std::find(available_nodes.begin(), available_nodes.end(), neighbor_node) == available_nodes.end() &&
                std::find(visited_nodes.begin(), visited_nodes.end(), neighbor_node) == visited_nodes.end())
            {
                std::cout<<"Add neighbor with cost G "<< neighbor_node.cost_g << " H "<< neighbor_node.cost_h<<std::endl;
                available_nodes.push_back(neighbor_node);
            }
        }
    }

    // Final plan reconstruction
    std::vector<MapCoord> final_plan;

    // Return empty plan if we didn't reach the goal
    if (visited_nodes.back().this_point != end_point) {
        return final_plan;
    }

    Node plan_node = visited_nodes.back();
    final_plan.push_back(plan_node.this_point);

    while(plan_node.this_point != starting_point) {
        plan_node = *(plan_node.previous_node);
        final_plan.push_back(plan_node.this_point);
    }

    // Reverse the order in order to have the plan from start to end
    std::reverse(final_plan.begin(),final_plan.end());

    return final_plan;
}
