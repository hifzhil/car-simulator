#include <example_node/publisher.h>
#include <example_node/odom.h>
#include <example_node/pid_controller.h>

/// c system
#include <math.h>
#include <iostream>
#include <string>
#include <unistd.h>
// ros
PidController throttle_pid  = PidController();
PublishWrapper *pubWrapper;
OdomWrapper *odomWrapper;

double trajectory[][2] = {
    {-9.7, -2.05},
    {40.0, -2.0},
    {43.7, -2.5},
    {44.7, -6.0},
    {44.7, -39.75},
    {47.2, -43.2},
    {50.8, -45.0},
    {104.85, -44.9},
    {115.9, -44.8},
    {120.0, -42.4},
    {121.4, -38.3},
    {122.1, 44.9},
    {104.5, 44.9},
    {50.9, 45.0},
    {47.1, 42.8},
    {44.95, 39.25},
    {44.85, 6.0},
    {46.9, 2.95},
    {50.0, 1.92},
    {105.45, 1.97},
    {110.35, -0.0},
    {112.0, -6.5},
};

uint index_waypoints = 0;
double ego_steer = 0.0;
double ego_delta = 0.0;
double ego_throttle = 10.0;
bool driving_rules = false;
int a = 1;
void steering_function(double target_x, double target_y);
void update();
void pure_pursuit (double target_x, double target_y); 
double constant_velocity (double vel);

// pure pursuit variable
double L_ = 0.98;
double Kdd_ = 0.2;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "shell_simulation");
    pubWrapper = new PublishWrapper();
    odomWrapper = new OdomWrapper();
    // lidarWrapper = new LidarWrapper();
    odomWrapper->onUpdated = &update;
    // lidarWrapper->onUpdated = &update;

    /**
     * @brief pid(kp,ki,kd,min,max)
    */
    throttle_pid.pid_init(50.0, 7.5000, 2.0, 0.0, 300.0);
    //////
    return odomWrapper->runLoop();
    // return lidarWrapper->runLoop();
}

void update()
{
    switch (a)
    {
    case 1: // trajectory
        driving_rules = true;
        // pubWrapper->throttle = constant_velocity(10);
        pubWrapper->steering = ego_delta;
        steering_function(trajectory[index_waypoints][0], trajectory[index_waypoints][1]);
        pure_pursuit(trajectory[index_waypoints][0], trajectory[index_waypoints][1]);
        if (index_waypoints >= sizeof(trajectory) / sizeof(trajectory[0]))
        {
            driving_rules = false;
            index_waypoints = 0;
            pubWrapper->throttle = 0.0;
            pubWrapper->steering = 0.0;
            a = 2;
        }
        break;
    default:
        break;
    }
    ROS_INFO("Ego Steer: %.2f", ego_steer);
    ROS_INFO("Ego Delta: %.2f", ego_delta);
    if (driving_rules)
    {
        if (odomWrapper->is_junction)
        {
            pubWrapper->throttle = constant_velocity(5);
        }
        else
        {
            pubWrapper->throttle = constant_velocity(8.5);
        }
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
    // ego_steer = sin(error_angle);
    
    /*
    * @brief no need to be sin, bcs it has passed to the car_vehicle_interface first
    */
    ego_steer = error_angle;
}

double constant_velocity (double vel)
{
    // throttle_pid.update_delta_time((sim_time - last_sim_time));
    double error_throttle = vel - odomWrapper->velocity;
    double throttle_out = throttle_pid.update_error(error_throttle);
    // if (odomWrapper->velocity > vel - 0.3)
    // {
    //     throttle_out = 0.0;
    //     brake_buffer= std::abs(throttle_out);
    //     pubWrapper->brake = brake_buffer;
    // }
    // else
    // {
    //     throttle_out = throttle_out;
    //     pubWrapper->brake = 0.0;
    // }
    // throttle_pid.show_error(true);
    //last_sim_time = sim_time;
    return std::abs(throttle_out);
}


void pure_pursuit (double target_x, double target_y) 
{
    double ld_ = Kdd_ * odomWrapper ->velocity;
    double alpha_ = atan2(target_y - odomWrapper->posY, target_x - odomWrapper->posX) * 180 / M_PI - odomWrapper->angle;
    alpha_ = -alpha_;
    /*
    * @brief I dont know why, but in my case, the (-) error leading car to left and (+) error leading car to right
            thats why the alpha need to be multiplied by negative 
    */
    if (alpha_ <= -180)
    {
        alpha_ += 360;
    }
    else if (alpha_ >= 180)
    {
        alpha_ -= 360;
    }

    double delta = atan2(2*L_*sin(alpha_* M_PI / 180), ld_);
    ego_delta = delta;
}