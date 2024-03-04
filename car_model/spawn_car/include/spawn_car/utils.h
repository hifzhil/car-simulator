/**
 * @file utils.h
 **/

#pragma once

//ros massage type
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

namespace utils {
geometry_msgs::Vector3 calc_linear(const double& va_x, const double& va_y, const double& va_z);
geometry_msgs::Vector3 calc_angular(const double& vl_x, const double& vl_y, const double& vl_z);

}  // namespace utils