/**
* @brief read wiki http://wiki.ros.org/msg#Fields
*/
#include <example_node/publisher.h>

// c system
#include <iostream>

PublishWrapper::PublishWrapper()
{
  publisher = handler.advertise<car_msgs::carCMD>("/car_command", 10);
  update();
  std::cout << "Preparing connection..." << std::endl;
  usleep(3000);
}

void PublishWrapper::update()
{
  /**
   * @brief This will attempt to send the data to the simulator
   */
  car_msgs::carCMD cmd;
  cmd.throttle = throttle;
  cmd.steer = steering;
  cmd.brake = brake;
  PublishWrapper::publisher.publish(cmd);
}