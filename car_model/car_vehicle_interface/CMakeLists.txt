cmake_minimum_required(VERSION 3.0.2)
project(car_vehicle_interface)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nav_msgs
  sensor_msgs
  geometry_msgs
  gazebo_ros
  car_msgs
  tf
)


# catkin_package(
#   INCLUDE_DIRS include
# #  LIBRARIES mevi_controller
# #  CATKIN_DEPENDS roscpp std_msgs
# #  DEPENDS system_lib
# )


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations



## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
# install(DIRECTORY launch/
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch/
# )

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node 
  src/nodelets/car_vehicle_interface.cpp
#  src/twist_to_joint.cpp
#  src/mevi_controller.cpp
#  src/utils.cpp
  )

# ## Rename C++ executable without prefix
# ## The above recommended prefix causes long target names, the following renames the
# ## target back to the shorter version for ease of user use
# ## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# # set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

# ## Add cmake target dependencies of the executable
# ## same as for the library above
# ## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}_node 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)
