#include<spawn_car/odometry_publisher.h>
OdomPublihser::OdomPublihser()
{
    joint_states_subs = handler.subscribe<sensor_msgs::JointState>(
        "/joint_states",
        10,
        boost::bind(&OdomPublihser::callbackHandler, this, ::_1));
        ros::Rate loop_rate(100);

    odom_pub = handler.advertise<nav_msgs::Odometry>("/Odometry", 10);
}

void OdomPublihser::callbackHandler(const sensor_msgs::JointStateConstPtr &msg)
{
    fr_steer_ = msg->position[0];
    fr_wheel_ = msg->position[1];
    fl_steer_ = msg->position[2];
    fl_wheel_ = msg->position[3];
    rr_wheel_ = msg->position[4];
    rl_wheel_ = msg->position[5];

    // &position = msg.position;
    // &velocity = msg.velocity;
    // &effort = msg.effort;
    
    // odometry_msg->pose.pose.position.x = posX;
    // odometry_msg->pose.pose.position.y = posY;
    // odometry_msg->pose.pose.position.z = posZ;
    // odometry_msg->twist.twist.linear.x = kecX;
    // odometry_msg->twist.twist.linear.y = kecY;
    // odometry_msg->pose.pose.orientation.x = qX;
    // odometry_msg->pose.pose.orientation.y = qY;
    // odometry_msg->pose.pose.orientation.z = qZ;
    // odometry_msg->pose.pose.orientation.w = qW;
}
