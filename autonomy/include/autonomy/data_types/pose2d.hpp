#pragma once
#include <iostream>

struct Pose2D {
  double x;
  double y;
  double theta;
  void print() {
    std::cout << "x: " << x << "\n"
              << "y: " << y << "\n"
              << "theta: " << theta << std::endl;
  };
};

// inline if you define a function in the .hpp
inline std::ostream &operator<<(std::ostream &outstr, Pose2D val) {
  return outstr << "x: " << val.x << "\n"
                << "y: " << val.y << "\n"
                << "theta: " << val.theta;
};

inline bool operator==(Pose2D pose1, Pose2D pose2) {
  return (pose1.x == pose2.x) && (pose1.y == pose2.y) &&
         (pose1.theta == pose2.theta);
};