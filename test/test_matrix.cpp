#include <iostream>

#include <gtest/gtest.h>

#include "matrix.hpp"

TEST(test_matrix, initialization_and_fill)
{
    Matrix matrix = Matrix(2,2);

    matrix.fill(5);
    matrix.set(0,0,10);
    matrix[1][1] = 2.5;

    EXPECT_EQ(matrix[0][0], 10);
    EXPECT_EQ(matrix[0][1], 5);
    EXPECT_EQ(matrix[1][0], 5);
    EXPECT_EQ(matrix[1][1], 2.5);

    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.columns(), 2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}