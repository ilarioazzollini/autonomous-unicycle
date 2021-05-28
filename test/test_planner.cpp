#include <iostream>

#include <gtest/gtest.h>

#include "matrix.hpp"
#include "planning/a_star.hpp"

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
    std::vector<Node> plan = planner.compute_plan(occupancy_matrix, starting_point, goal_point);

    EXPECT_EQ(plan.size(), 9);
    EXPECT_EQ(plan[plan.size() - 1].row, goal_point.row);
    EXPECT_EQ(plan[plan.size() - 1].column, goal_point.column);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}