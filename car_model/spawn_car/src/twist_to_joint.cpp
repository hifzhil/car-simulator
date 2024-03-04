#include<spawn_car/twist_to_joint.h>
JointToTwist::OdomPublihser()
{
    steering_sub = handler.subscribe<std_msgs::Float64>(
        "/steering",
        10,
        boost::bind(&JointToTwist::throttle_callbackHandler, this, ::_1));
        ros::Rate loop_rate(100);
    steering_sub = handler.subscribe<std_msgs::Float64>(
        "/throttle",
        10,
        boost::bind(&JointToTwist::steering_callbackHandler, this, ::_1));
        ros::Rate loop_rate(100);
    
    cmd_pub = handler.advertise<std_msgs::Float64>("/cmd_vel", 10);
}

void JointToTwist::throttle_callbackHandler(const sensor_msgs::JointStateConstPtr &msg)
{
    throttle = msg->data;
}

void JointToTwist::steering_callbackHandler(const sensor_msgs::JointStateConstPtr &msg)
{
    steering = msg->data;
}
