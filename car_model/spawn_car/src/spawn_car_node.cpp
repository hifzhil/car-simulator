#include <ros/ros.h>
#include <spawn_car/odometry_publisher.h>


int main(int argc, char** argv) {
  ros::init(argc, argv, "spawn_car_node");
  OdomPublihser odom_mevi;
  ros::spin();
  return 0;
}