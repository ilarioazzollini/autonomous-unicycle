#pragma once
#include "pose2d.hpp"

class KinModel {
public:
  // v [m/s], omega [rad/s], delta_t [s]
  Pose2D integration(double v, double omega, double delta_t);
  KinModel(Pose2D initial_pose);

private:
  Pose2D m_current_pose;
};