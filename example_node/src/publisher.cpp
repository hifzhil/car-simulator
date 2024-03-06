/**
* @brief read wiki http://wiki.ros.org/msg#Fields
*/



#include <example_publisher/publisher.h>

// c system
#include <iostream>

PublishWrapper::PublishWrapper()
{
  /**
  * @brief ini adalah publihser untuk nyoba di lokal
  * TODO: comment ini sebelum upload
  */
  publisher = handler.advertise<car_msgs::carCMD>("/carla/ego_vehicle/vehicle_control_cmd", 10);
  /**
  * @brief comment flag
  */
  
  /**
  * @brief FLAG: Publisher SEM untuk upload
  */
  brake_publisher = handler.advertise<std_msgs::Float64>("/brake_command", 10);
  gear_publisher = handler.advertise<std_msgs::String>("/gear_command", 10);
  handbrake_publisher = handler.advertise<std_msgs::Bool>("/handbrake_command", 10);
  steering_publisher = handler.advertise<std_msgs::Float64>("/steering_command", 10);
  throttle_publisher = handler.advertise<std_msgs::Float64>("/throttle_command", 10); 
  /**
  * @brief flag end
  */

  update();
  std::cout << "Preparing connection..." << std::endl;
  usleep(3000);
}

void PublishWrapper::update()
{
  /**
  * @brief ini adalah tipe massage untuk publish lokal
  * TODO: comment ini sebelum upload
  */
  car_msgs::carCMD cmd;
  cmd.throttle = throttle;
  cmd.steer = steering;
  cmd.brake = brake;
  PublishWrapper::publisher.publish(cmd);
  /**
  * @brief comment flag
  */

  /**
  * FLAG: untuk publish ke SEM
  */
  cmd_brake.data = brake;
  cmd_gear.data = "forward";
  cmd_handbrake.data = false;
  cmd_steering.data = steering;
  cmd_throttle.data = throttle;

  PublishWrapper::brake_publisher.publish(cmd_brake);
  PublishWrapper::gear_publisher.publish(cmd_gear);
  PublishWrapper::handbrake_publisher.publish(cmd_handbrake);
  PublishWrapper::steering_publisher.publish(cmd_steering);
  PublishWrapper::throttle_publisher.publish(cmd_throttle);
  /**
  * @brief flag end
  */
}