# Simulator CAR

In developing autonomous algorithms, sometimes we need to model something we need. Many robot models are available on open source, but sometimes we need our own models. In this repo, I will explain my steps in modeling and simulating robots in Gazebo. I hope this can help for you who want to modeling a robot and I will also explain how my kinematics work, especially a mobile robot kinematics

In this project, I will create an easy ROS work environment so that many people can learn and build this project together. As for the model that I have developed, it is a mobile robot with some configuration, An urban Car is using Ackermann Steering, the Formula Car is using anti-ackermann for logitudinal control. A lateral move, I developed an differential drive for Rear Wheel Drive Car, and also developing another kinematics for Rear Wheel Drive Car, Four Drive Car, and a Four Wheel Steering

I tried to match the data type to drive this same car as Carla Simulator, with forking a carla_msgs, and using the same sensor with Carla. My hope in this project is everyone to try to develop their own node even if they don't have a computer compatible with Carla Simulator. Expectation. after trying my model, we can deploy the same node in Carla Simulator (with some additional minor configurations).

Some usefull plugins also appeared on this repo, some is a mandatory for the simulator and some is depend. By using the plugins, I hope another people can make it, or even use it on their own simulator

I really hope this helping people who want to learn about autonomous vehicle, by simulating it, you will get it.

## Simulator
I am using a Gazebo simulator. The world I using is an opensource map, an opendrive, and my custom world to train my autonomous algorithm. I hope poeple will help this repo and create some fun with it

## Car Model
I have create 2 model car. First one is an Urban Car and another is a Formula Car

## Ros Massages
To control a car in simulation, we need to publish a massage to this available topics :
  - /carCMD
    carCMD contains theese data :
      - throttle : the value is in 0 to 1 range
      - steering : the value is in -1 to 1 range
        
## Topics Available
- /odometry
- /lidar

## Launch simulator
roslaunch spawn_car spawn_mevi.launch

## Make the robot move 
rosropic pub /

## Example Node
Node example dibangun dengan roscpp . 

## Vehicle Interface Plugins :
  This project also has a vehicle interface plugins. This is mandatory for theese raequirements :
  
  - converting a steering to joint_trajectory data : this function needed for joint_trajectory_controlleer
    
  - converting a throttle to velocity data : this function needed for diff_drive_controller

## Sensor Plugins : 
  Also, this project has a sensor plugins for current avalable sensor :

  
## WIKI : https://github.com/hifzhil/car-simulator/wiki
