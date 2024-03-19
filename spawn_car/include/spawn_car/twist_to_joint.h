#include <ros/ros.h>
#include <string>
#include <geometry_msgs/Twist.h>
class JointToTwist
{
public:
    JointToTwist();
    geometry_msgs::Twist twist_msg;
    void (*onUpdated)() = nullptr;
    
private:
    ros::NodeHandle handler;
    ros::Publisher cmd_pub;
    ros::Subscriber throttle_pub;
    ros::Subscriber steering_pub;   
    void throttle_callbackHandler(const std_msgs::Float64 &msg);
    void steering_callbackHandler(const std_msgs::Float64 &msg);
};

