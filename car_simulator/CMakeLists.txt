cmake_minimum_required(VERSION 3.0.2)
project(car_simulator)
find_package(catkin REQUIRED)
catkin_metapackage()
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch/
)