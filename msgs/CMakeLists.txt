cmake_minimum_required(VERSION 2.8.3)
project(car_msgs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  genmsg
  )

add_message_files(
  FILES
  carCMD.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  )

catkin_package(
  CATKIN_DEPENDS message_runtime std_msgs
  )
