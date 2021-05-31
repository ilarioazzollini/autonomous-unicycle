#include <iostream>

#include <gtest/gtest.h>

#include "matrix.hpp"
#include "planning/a_star.hpp"

#include <memory> // smart pointers

/*
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
    occupancy_matrix.set(1,0,0);
    occupancy_matrix.set(1,1,0);
    occupancy_matrix.set(1,2,0);

    // Second wall
    occupancy_matrix.set(3,3,0);
    occupancy_matrix.set(4,3,0);

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
    occupancy_matrix.set(3,3,0);
    occupancy_matrix.set(3,4,0);
    occupancy_matrix.set(4,3,0);

    AStar planner = AStar();
    std::vector<MapCoord> plan = planner.compute_plan(occupancy_matrix, starting_point, goal_point);

    EXPECT_TRUE(plan.empty());
}
*/


TEST(test_planner, memory)
{
    // Static memory
    int i = 1; // stack memory
    int* pt = &i; // pointer to the cell memory where there's i (this goes on stack as well)

    // The compiler does not know anything about dynamically allocated memory
    int* x = new int(1); // pointer (on stack memory - 64 bit) to dynamic memory ("1" dynamically allocated)
    delete x; // memory related to "x" is now free


    x = new int(2);
    std::cout<< *x << std::endl; // *x : dereferencing -> it gives the pointed variable
    delete x;
    //std::cout<< x << std::endl; // *x : dereferencing -> it gives the pointed variable
    bool check = (x == nullptr);
    std::cout<< check << std::endl;

    *pt = 5; // modify "i" via dereferencing
    std::cout<< "pt: "<< *pt << std::endl;
    std::cout<< "i: "<< i << std::endl;

    int b = i;
    std::cout<< "b: "<< b << std::endl;
    b = 3;
    int& y = i; // it's a reference: it's like a pointer but it's guaranteed it is valid (it's never a null pointer). It's an alias to a variable
    y = 10; // You use it as a variable, forgetting it is a pointer. It is a reference.
    std::cout<< "i: "<< i << std::endl;
    std::cout<< "b: "<< b << std::endl;

    // Smart pointers
    // solve the ownership problem: who needs to delete, if there are more pointers to the same memory?
    // the smart pointer takes care of deleting with its destructor

    // The "ownership problem" is twofold:
    // 1) Be sure that there is no memory leak (memory needs to be deallocated when a pointer goes out of scope)
    // 2) Be sure no one already deallocated the memory you want to use -> resulting in a segmentation fault

    // Unique pointer
    std::unique_ptr<Matrix> a; // a null pointer before you initialize it
    a = std::make_unique<Matrix>(5,5); // initialization of a unique pointer (it is like "new")
    // then you use it as a pointer: * for dereferencing

    // In order to use a method on a pointer
    a->fill(255);
    // or equivalently: (*a).fill(255);

    std::unique_ptr<Matrix> c;
    // c = a; it fails by definition of unique pointer
    c = std::move(a); // a becomes a null pointer and c is the new unique pointer pointing to that memory cell!
    // move works with everything, not only unique pointers. But, when dealing with unique pointers it is necessary.
    // There's no other way to move its content.

    // Use it as an input as follows
    // std::vector<MapCoord> plan = planner.compute_plan(std::move(a), starting_point, goal_point);

    // As efficient as a normal pointer

    // Shared pointer
    std::shared_ptr<Matrix> e;
    e = std::make_shared<Matrix>(5,5);

    std::shared_ptr<Matrix> f;
    f = e;

    // Less efficient than a normal or unique pointer. It keeps a counter of how many active copies there are.
    // It deallocates memory when the last shared pointer goes out of scope.

    // Spoiler: the counter of a shared pointer is thread safe.

    // Weak pointer
    // It is a shared pointer that does not increment the counter
    std::weak_ptr<Matrix> m;
    // make_weak does not exist: you create a shared pointer and then copy it
    m = e;
    // as long as one copy of "e" exists, the memory exists.
    // It has only one method: lock, which returns a shared pointer.
    std::shared_ptr<Matrix> j = m.lock(); // always check whether it's a null pointer or not: (j != nullptr) ?
    // It cannot do anything else than lock.


    EXPECT_TRUE(true);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}