#include <ros/ros.h>
#include <string>

/**
* @brief publisher untuk lokal
* TODO: comment ini sebelum upload
*/
#include "car_msgs/carCMD.h"
/**
* @brief flag untuk comment
*/


// ros massage
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

class PublishWrapper
{
public:
    PublishWrapper();    
    /**
    * @brief Valid values range from 0.0 (no brake) to 1.0 (full brake)
    */
    double brake;

    /**
    * @brief Valid values are "forward" or "reverse"
    */
    std::string gear;

    /**
    * @brief If set to "true", throttle will be ignored
    */
    bool handbrake;
    
    /**
    * @brief values range from -1.0 (full left) to 1.0 (full right)
    */
    double steering;

    /**
    * @brief Valid values range from 0.0 (no throttle) to 1.0 (full throttle)
    */
    double throttle;

    void update();

private:
    ros::NodeHandle handler;
    
    /**
     * @brief publisher untuk lokal
     * TODO: comment ini sebelum upload
    */
    ros::Publisher publisher;
    /**
     * @brief flag untuk comment
    */
    
    /**
     * FLAG: publisher untuk SEM
    */
    std_msgs::Float64 cmd_brake;
    std_msgs::String cmd_gear;
    std_msgs::Bool cmd_handbrake;
    std_msgs::Float64 cmd_steering;
    std_msgs::Float64 cmd_throttle;

    ros::Publisher brake_publisher;
    ros::Publisher gear_publisher;
    ros::Publisher handbrake_publisher;
    ros::Publisher steering_publisher;
    ros::Publisher throttle_publisher; 
    /**
     * @brief flag end
    */
};

