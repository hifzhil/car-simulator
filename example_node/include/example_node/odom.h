#include <ros/ros.h>
#include <string>

// ros masage data
#include <nav_msgs/Odometry.h>

class OdomWrapper
{
public:
    OdomWrapper();
    int runLoop();
    double posX;
    double posY;
    double kecX;
    double kecY;
    double angle;
    double pitch;
    double velocity;
    void (*onUpdated)() = nullptr;

private:
    ros::NodeHandle handler;
    ros::Subscriber subscriber;
    void callbackHandler(const nav_msgs::OdometryConstPtr &msg);
};