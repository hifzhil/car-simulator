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
    bool is_junction;
    void (*onUpdated)() = nullptr;

private:
    ros::NodeHandle handler;
    ros::Subscriber subscriber;
    void updateState();
    int index_junction = 0;
    double junctionLocation[7][2] = {
        {43.7,-2.5},
        {47.2,-43.2},
        {120.0,-42.4},
        {122.1,44.9},
        {47.1,42.8},
        {46.9,2.95},
        {110.35,-0.0},
    };

    double traffic_check[7][2] = {
        {45.0,-8.45},
        {53.5,-45.15},
        {121.6,-32.35},
        {114.15,44.8},
        {45.0,35.95},
        {52.4,1.95},
        {111.6,-8.25},
    };  
    void callbackHandler(const nav_msgs::OdometryConstPtr &msg);
};