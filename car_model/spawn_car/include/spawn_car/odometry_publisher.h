#include <ros/ros.h>
#include <string>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/JointState.h>
class OdomPublihser
{
public:
    OdomPublihser();
    nav_msgs::Odometry odometry_msg;
    void (*onUpdated)() = nullptr;
    std::string name;
    double position;
    double velocity;
    double effort;

    double fr_steer_;
    double fr_wheel_;
    double fl_steer_;
    double fl_wheel_;
    double rr_wheel_;
    double rl_wheel_;



    // double posX;
    // double posY;
    // double kecX;
    // double kecY;
    // double qW;
    // double qX;
    // double qY;
    // double qZ;
    
private:
    ros::NodeHandle handler;
    ros::Subscriber joint_states_subs;
    ros::Publisher odom_pub;
    void callbackHandler(const sensor_msgs::JointStateConstPtr &msg);
};

