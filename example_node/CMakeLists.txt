cmake_minimum_required(VERSION 3.1.0)
project(example_node)

find_package(Boost REQUIRED)
find_package(catkin REQUIRED COMPONENTS
    car_msgs
    roscpp
    nav_msgs
    std_msgs
    sensor_msgs
    geometry_msgs
    pcl_conversions
    pcl_ros
    message_generation
)

# add_message_files(
#   FILES
#   carCMD.msg
# )

# generate_messages(
#   DEPENDENCIES
#   sensor_msgs
#   std_msgs
#   geometry_msgs
#   car_msgs
# )

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES apc23
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs pcl_conversions pcl_ros
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    src/publisher.cpp
    src/odom.cpp
    src/main_node.cpp
    src/pid_controller.cpp
)

add_dependencies(${PROJECT_NAME}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Mark libraries for installation
# See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)


## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

## Mark other files for installation (e.g. launch and bag files, etc.)
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch/
)