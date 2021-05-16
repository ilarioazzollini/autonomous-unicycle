#include "assert.h"
#include "pose2d.hpp"
#include "position_ctrl/model_f_euler_dis.hpp"
#include <iostream>

int main() {
  double delta_t = 0.1; // [s]

  // Test 1
  Pose2D initial_pose = {0, 0, 0};
  KinModel unicycle = KinModel(initial_pose);
  Pose2D output_pose = unicycle.integration(0, 0, delta_t);
  // std::cout << output_pose << std::endl;
  assert(output_pose == initial_pose);

  // Test 2
  unicycle = KinModel(initial_pose);
  output_pose = unicycle.integration(0, 1, delta_t);
  // std::cout << output_pose << std::endl;
  Pose2D expected_pose = {0, 0, delta_t};
  assert(output_pose == expected_pose);

  // Test 3
  unicycle = KinModel(initial_pose);
  output_pose = unicycle.integration(1, 0, delta_t);
  // std::cout << output_pose << std::endl;
  expected_pose = {delta_t, 0, 0};
  assert(output_pose == expected_pose);

  // Test 4
  unicycle = KinModel(initial_pose);
  double final_time = 2; //[s]
  for (double i = 0; i <= final_time; i = i + delta_t) {
    output_pose = unicycle.integration(1, 0, delta_t);
    // std::cout << output_pose << std::endl;
    expected_pose = {i + delta_t, 0, 0};
    // std::cout << expected_pose << std::endl;
    assert(output_pose == expected_pose);
  }

  std::cout << "All tests successfully passed." << std::endl;

  return 0;
}