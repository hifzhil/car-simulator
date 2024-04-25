# Simulator CAR

Welcome to Simulator CAR! This project aims to provide a comprehensive guide and resources for modeling and simulating various types of vehicles in Gazebo for autonomous algorithm development. Whether you're new to robotics or looking to dive deeper into vehicle kinematics and control, this repository is designed to be an accessible learning resource.

## Overview

In this repository, you'll find instructions, models, plugins, and examples to help you build and simulate your own autonomous vehicles in Gazebo. The primary focus is on creating a flexible ROS (Robot Operating System) environment that allows for easy experimentation and development.

## Features

- Multiple Vehicle Models: Simulator CAR offers several vehicle models, including an Urban Car and a Formula Car, each with different configurations and kinematics.
  
- ROS Messages: To control the simulated vehicles, you can publish messages to the \`/carCMD\` topic, specifying throttle and steering values.
  
- Available Topics: Key topics like \`/odometry\` and \`/lidar\` are available for accessing vehicle data and sensor information.
  
- Launch Commands: Use \`roslaunch\` to spawn the simulator environment with \`spawn_mevi.launch\`.
  
- Example Node: An example node built with \`roscpp\` is provided to demonstrate how to control the vehicles.
  
- Vehicle Interface Plugins: Mandatory plugins are included to handle steering-to-joint trajectory conversion and throttle-to-velocity conversion, enabling various kinematic controls.
  
- Sensor Plugins: Essential plugins for available sensors are provided to facilitate autonomous algorithm development.

## Simulator Environment

Simulator CAR utilizes the Gazebo simulator along with open-source maps and custom worlds to create realistic environments for training autonomous algorithms.

## Getting Started

If you're new to autonomous vehicle simulation or want to start building your own, check out the WIKI for detailed guides on topics like URDF, spawning sensors in Gazebo, using ROS controllers, and step-by-step instructions for creating your autonomous car in Gazebo.

## Contribution

Contributions to this repository are highly encouraged! Whether it's adding new vehicle models, improving documentation, fixing bugs, or implementing new features, your input can help make this project even more valuable for the community.

## Explore Further

To explore additional resources and autonomous algorithms developed using this simulator, visit my profile and check out my other repositories.

Let's build and simulate amazing autonomous vehicles together! 🚗💻🤖
