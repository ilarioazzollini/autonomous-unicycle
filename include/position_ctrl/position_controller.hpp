#pragma once
#include "pose2d.hpp"
#include "vel_commands.hpp"

class PosCtrl {
public:
  VelCommands input_function(double e_x, double e_y, Pose2D pose);
  PosCtrl(double len, double gain_x, double gain_y);

private:
  double m_len;
  double m_gain_x;
  double m_gain_y;
};