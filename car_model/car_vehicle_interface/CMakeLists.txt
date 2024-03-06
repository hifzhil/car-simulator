cmake_minimum_required(VERSION 3.0.2)
project(car_bridge)

set(COMMON_DEPS
  std_msgs
  car_msgs
  nodelet
  pluginlib
)

find_package(catkin REQUIRED COMPONENTS
  ${COMMON_DEPS})


catkin_package(
  LIBRARIES car_vehicle_interface
  CATKIN_DEPENDS ${COMMON_DEPS}
)


## Locations fpr header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare C++ library

add_library(
  ${PROJECT_NAME}_node
  src/nodelets/car_vehicle_interface.cpp
)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
)

add_dependencies(
  ${PROJECT_NAME}_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

set_target_properties(
  ${PROJECT_NAME}_node
  PROPERTIES COMPILE_FLAGS "-std=c++14 -DPCL_NO_PRECOMPILE"
)

# car_nodelet_add_node(
#   car_simulator_vehicle_interface_node ${PROJECT_NAME} CarSimulatorVehicleInterface
# )
# target_link_libraries(
#   car_simulator_vehicle_interface_node ${PROJECT_NAME}
# )
# set_target_properties(
#   car_simulator_vehicle_interface_node PROPERTIES COMPILE_FLAGS "-std=c++14 -DPCL_NO_PRECOMPILE"
# )
# add_dependencies(car_simulator_vehicle_interface_node ${PROJECT_NAME})