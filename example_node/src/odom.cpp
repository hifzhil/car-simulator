// Sapuangin package
#include <example_node/odom.h>
// c system
#include <iostream>
#include <math.h>
// ros
#include <ros/time.h>

OdomWrapper::OdomWrapper()
{
    subscriber = handler.subscribe<nav_msgs::Odometry>(
        "/base_pose_ground_truth",
        10,
        boost::bind(&OdomWrapper::callbackHandler, this, ::_1));
    ros::Rate loop_rate(100);
};

int OdomWrapper::runLoop()
{
    try
    {
        ros::spin();
    }
    catch (std::exception error)
    {
        return 1;
    }
    return 0;
};
void OdomWrapper::callbackHandler(const nav_msgs::OdometryConstPtr &msg)
{

    if (onUpdated != nullptr)
    {
        onUpdated();
    }

    posX = msg->pose.pose.position.x;
    posY = msg->pose.pose.position.y;
    kecX = msg->twist.twist.linear.x;
    kecY = msg->twist.twist.linear.y;
    double qx = msg->pose.pose.orientation.x;
    double qy = msg->pose.pose.orientation.y;
    double qz = msg->pose.pose.orientation.z;
    double qw = msg->pose.pose.orientation.w;
    double siny_cosp = 2.0 * ((qw * qz) + (qx * qy));
    double cosy_cosp = 1 - (2.0 * ((qy * qy) + (qz * qz)));
    double t2 = +2.0 * (qw * qy - qz * qx);
    if (t2 > 1)
    {
        t2 = 1;
    }
    else if (t2 < -1)
    {
        t2 = -1;
    }
    else
    {
        t2 = t2;
    }
    pitch = asin(t2) * (180 / M_PI);
    angle = atan2(siny_cosp, cosy_cosp) * (180 / M_PI);
    angle = atan2(siny_cosp, cosy_cosp) * (180 / M_PI);
    double vx = msg->twist.twist.linear.x;
    double vy = msg->twist.twist.linear.y;
    double vz = msg->twist.twist.linear.z;
    velocity = sqrt(pow(vx, 2) + pow(vy, 2)) * 3.6;
}
