# Simulator CAR

Welcome to Simulator CAR! This project aims to provide a comprehensive guide and resources for modeling and simulating various types of vehicles in Gazebo for autonomous algorithm development. Whether you're new to robotics or looking to dive deeper into vehicle kinematics and control, this repository is designed to be an accessible learning resource.

## Overview

In this repository, you'll find instructions, models, plugins, and examples to help you build and simulate your own autonomous vehicles in Gazebo. The primary focus is on creating a flexible ROS (Robot Operating System) environment that allows for easy experimentation and development.

## Installation

Follow these steps to set up the simulator:

1. Install ROS Noetic and its dependencies:
   ```bash
   sudo apt install python3-rosdep
   ```

2. Navigate to the project directory:
   ```bash
   cd $HOME/noetic_ws/src/car-simulator
   ```

3. Initialize and update Git submodules:
   ```bash
   git submodule init
   git submodule update
   ```

4. Move to the workspace directory:
   ```bash
   cd $HOME/noetic_ws
   ```

5. Source ROS Noetic:
   ```bash
   source /opt/ros/noetic/setup.bash
   ```

6. Initialize and update rosdep, then install dependencies:
   ```bash
   sudo rosdep init
   rosdep update
   rosdep install --from-path src --ignore-src -y
   ```

## CitySim Setup

To set up the CitySim environment for urban simulation:

1. Navigate to the CitySim plugin directory:
   ```bash
   cd $HOME/noetic_ws/src/car-simulator/plugins/citysim
   ```

2. Create and enter the build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure and build CitySim:
   ```bash
   cmake ..
   sudo make install
   ```

4. Source the CitySim environment:
   ```bash
   source /usr/local/share/citysim-0/setup.sh
   ```

5. Generate and copy the world file:
   ```bash
   cd worlds
   erb simple_city.world.erb > simple_city.world
   cp simple_city.world $HOME/noetic_ws/src/car-simulator/spawn_car/world/
   ```

Important: Before launching any world that uses CitySim features, you must source the CitySim environment:
```bash
source /usr/local/share/citysim-0/setup.sh
```
This ensures all CitySim plugins and resources are properly loaded in Gazebo.

The CitySim environment provides:
- Urban environment models
- Traffic light GUI plugin
- Visual effects plugins (Bloom and Lens Flare)
- Various world configurations for testing

## Building Packages

Before building the packages, ensure you have completed all previous setup steps:

1. Make sure you have sourced ROS Noetic:
   ```bash
   source /opt/ros/noetic/setup.bash
   ```

2. If using CitySim, source its environment:
   ```bash
   source /usr/local/share/citysim-0/setup.sh
   ```

3. Navigate to your workspace:
   ```bash
   cd $HOME/noetic_ws
   ```

4. Build the packages:
   ```bash
   catkin_make
   ```

5. Source the workspace:
   ```bash
   source devel/setup.bash
   ```

Now you can proceed with launching the simulator as described in the Launching the Simulator section.

## Launching the Simulator

After setting up the environment, you can launch the simulator and run example nodes:

1. Spawn the urban car in the simulation:
   ```bash
   roslaunch car-simulator spawn_urban.launch
   ```

2. Run the example control node:
   ```bash
   roslaunch example_node example_node.launch
   ```

Make sure to source the CitySim environment before launching if you're using CitySim features:
```bash
source /usr/local/share/citysim-0/setup.sh
```

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

## Acknowledgments

This project incorporates and builds upon the work of several open-source projects:

- [CitySim](https://github.com/pilsbot/citysim) - Provides the urban environment simulation framework
- [RealSense Gazebo Plugin](https://github.com/issaiass/realsense_gazebo_plugin) - Enables Intel RealSense camera simulation in Gazebo

We are grateful to these projects and their contributors for their valuable work in the robotics simulation community.

Let's build and simulate amazing autonomous vehicles together! 🚗💻🤖
