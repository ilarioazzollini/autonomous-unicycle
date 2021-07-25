#include <iostream>

#include <gtest/gtest.h>

#include "autonomy/data_types/matrix.hpp"
#include "autonomy/planning/a_star.hpp"

TEST(test_planner, no_obstacles)
{
    Matrix occupancy_matrix = Matrix(5,5);
    occupancy_matrix.fill(255);

    MapCoord starting_point;
    starting_point.row = 0;
    starting_point.column = 0;

    MapCoord goal_point;
    goal_point.row = 4;
    goal_point.column = 4;

    AStar planner = AStar();
    std::vector<MapCoord> plan = planner.compute_plan(occupancy_matrix, starting_point, goal_point);

    EXPECT_EQ(plan.size(), 9);
    EXPECT_EQ(plan[plan.size() - 1], goal_point);
}

TEST(test_planner, feasible_with_obstacles)
{
    Matrix occupancy_matrix = Matrix(5,5);
    occupancy_matrix.fill(255);

    MapCoord starting_point;
    starting_point.row = 0;
    starting_point.column = 0;

    MapCoord goal_point;
    goal_point.row = 4;
    goal_point.column = 4;

    // First wall
    occupancy_matrix[1][0] = 0;
    occupancy_matrix[1][1] = 0;
    occupancy_matrix[1][2] = 0;

    // Second wall
    occupancy_matrix[3][3] = 0;
    occupancy_matrix[4][3] = 0;


    AStar planner = AStar();
    std::vector<MapCoord> plan = planner.compute_plan(occupancy_matrix, starting_point, goal_point);

    EXPECT_EQ(plan[plan.size() - 1], goal_point);
}

TEST(test_planner, unfeasible_problem)
{
    Matrix occupancy_matrix = Matrix(5,5);
    occupancy_matrix.fill(255);

    MapCoord starting_point;
    starting_point.row = 0;
    starting_point.column = 0;

    MapCoord goal_point;
    goal_point.row = 4;
    goal_point.column = 4;

    // Wall encapsulating the goal point
    occupancy_matrix[3][3] = 0;
    occupancy_matrix[3][4] = 0;
    occupancy_matrix[4][3] = 0;

    AStar planner = AStar();
    std::vector<MapCoord> plan = planner.compute_plan(occupancy_matrix, starting_point, goal_point);

    EXPECT_TRUE(plan.empty());
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}