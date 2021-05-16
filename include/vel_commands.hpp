#pragma once
#include <iostream>

struct VelCommands {
  double v;
  double omega;
};

// inline if you define a function in the .hpp
inline std::ostream &operator<<(std::ostream &outstr, VelCommands val) {
  return outstr << "v: " << val.v << ", "
                << "omega: " << val.omega;
};

inline bool operator==(VelCommands comm1, VelCommands comm2) {
  return (comm1.v == comm2.v) && (comm1.omega == comm2.omega);
};