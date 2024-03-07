An autonoomuous Simulator based on Gazebo & Ros. First model based on Mevi BRIN Bandung

# Car Model
Model pertama dari simulator ini adalah mobil autonomous milik BRIN Bandung, yaitu MEVI

# Example Node
Node example dibangun dengan roscpp . 

# Ros Massages
To control a car in simulation, we need to publish a massage to this available topics :
  - /throttle_cmd (Float64)
  - /steering_cmd (Float64)

# Vehicle Interface Plugins :
  This project also has a vehicle interface plugins. This is mandatory for theese raequirements :
  
  - converting a steering to joint_trajectory data : this function needed for joint_trajectory_controlleer
    
  - converting a throttle to velocity data : this function needed for diff_drive_controller

# Sensor Plugins : 
  Also, this project has a sensor plugins for current avalable sensor :
    
# Topics Available

 - /base_pose_ground_truth
 - /clicked_point
 - /clock
 - /gazebo/link_states
 - /gazebo/model_states
 - /gazebo/parameter_descriptions
 - /gazebo/parameter_updates
 - /gazebo/performance_metrics
 - /gazebo/set_link_state
 - /gazebo/set_model_state
 - /initialpose
 - /joint_states
 - /mevi/front_center_camera/camera_info
 - /mevi/front_center_camera/image_raw
 - /mevi/front_center_camera/parameter_descriptions
 - /mevi/front_center_camera/parameter_updates
 - /mevi_model/left_motor_controller/command
 - /mevi_model/right_motor_controller/command
 - /mevi_model/steer_controller/command
 - /mevi_model/steer_controller/follow_joint_trajectory/cancel
 - /mevi_model/steer_controller/follow_joint_trajectory/feedback
 - /mevi_model/steer_controller/follow_joint_trajectory/goal
 - /mevi_model/steer_controller/follow_joint_trajectory/result
 - /mevi_model/steer_controller/follow_joint_trajectory/status
 - /mevi_model/steer_controller/state
 - /move_base_simple/goal
 - /rosout
 - /rosout_agg
 - /tf
 - /tf_static
 - /velodyne_points

# Launch simulator
roslaunch spawn_car spawn_mevi.launch

  
# WIKI : https://github.com/hifzhil/car-simulator/wiki
