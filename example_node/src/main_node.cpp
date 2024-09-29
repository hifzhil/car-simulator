// Sapuangin packages
#include <example_node/publisher.h>
#include <example_node/odom.h>

/// c system
#include <math.h>
#include <iostream>
#include <string>
#include <unistd.h>
// ros
PublishWrapper *pubWrapper;
OdomWrapper *odomWrapper;

double trajectory[][2] = {
    {-175.79, 4.4},
    {-176.55, 4.49},
    {-177.74, 4.68},
    {-178.73, 4.87},
    {-179.88, 5.12},
    {-180.83, 5.64},
    {-181.77, 6.36},
    {-182.49, 7.36},
    {-183.02, 8.76},
    {-183.42, 9.81},
    {-183.85, 11.11},
    {-184.22, 12.38},
    {-184.43, 13.68},
    {-184.56, 15.09},
    {-184.58, 16.38},
};

uint index_waypoints = 0;
double ego_steer = 0.0;
double ego_throttle = 0.233;
int a = 1;
void steering_function(double target_x, double target_y);
void update();

int main(int argc, char **argv)
{
    ros::init(argc, argv, "shell_simulation");
    pubWrapper = new PublishWrapper();
    odomWrapper = new OdomWrapper();
    // lidarWrapper = new LidarWrapper();
    odomWrapper->onUpdated = &update;
    // lidarWrapper->onUpdated = &update;
    return odomWrapper->runLoop();
    // return lidarWrapper->runLoop();
}

void update()
{
    switch (a)
    {
    case 1: // trajectory
        pubWrapper->throttle = 0.5;
        pubWrapper->steering = 0.5;
        steering_function(trajectory[index_waypoints][0], trajectory[index_waypoints][1]);
        if (index_waypoints >= sizeof(trajectory) / sizeof(trajectory[0]))
        {
            index_waypoints = 0;
            pubWrapper->throttle = 0.0;
            pubWrapper->steering = ego_steer;
            a = 2;
        }
        break;
    default:
        break;
    }
    pubWrapper->update();
}

void steering_function(double target_x, double target_y)
{
    double angle_target = atan2(target_y - odomWrapper->posY, target_x - odomWrapper->posX) * 180 / M_PI;
    double error_angle = odomWrapper->angle - angle_target;
    if (error_angle <= -180)
    {
        error_angle += 360;
    }
    else if (error_angle >= 180)
    {
        error_angle -= 360;
    }
    if (target_x - 3 < odomWrapper->posX && odomWrapper->posX < target_x + 3 && target_y - 3 < odomWrapper->posY && odomWrapper->posY < target_y + 3)
    {
        index_waypoints += 1;
    }
    error_angle = error_angle * M_PI / 180;
    ego_steer = sin(error_angle);
}
