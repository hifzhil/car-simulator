cmake_minimum_required(VERSION 3.0.2)
project(car_bridge)

set(COMMON_DEPS
  std_msgs
  car_msgs
  nodelet
  pluginlib
)

find_package(catkin REQUIRED COMPONENTS
  ${COMMON_DEPS}
)


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

add_library(CarSimulatorVehicleInterface
  src/nodelets/car_vehicle_interface.cpp
)

target_link_libraries(CarSimulatorVehicleInterface
  ${catkin_LIBRARIES}
)

add_dependencies(CarSimulatorVehicleInterface
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

set_target_properties(CarSimulatorVehicleInterface
  PROPERTIES COMPILE_FLAGS "-std=c++14 -DPCL_NO_PRECOMPILE"
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch/
)

install(TARGETS CarSimulatorVehicleInterface
  DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
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