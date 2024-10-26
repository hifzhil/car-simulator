#include <example_node/publisher.h>
#include <example_node/odom.h>
#include <example_node/pid_controller.h>

/// c system
#include <math.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream> // Include for file handling
#include <chrono>  // Include for time handling
#include <ctime>   // Include for time functions
#include <sstream> // Include for string stream
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
double ego_throttle = 0.0;
bool driving_rules = false;
double target_vel = 0;
int a = 1;
void steering_function(double target_x, double target_y);
void update();
void pure_pursuit (double target_x, double target_y); 
void log_to_csv(double velocity, double reference_speed, double crosstrack_e, double delta, double yaw, double posX, double posY, double time_step);
double constant_velocity (double vel);

// pure pursuit variable
double L_ = 0.98;
double Kdd_ = 0.2;
double crosstrack_e_ = 0.0;
double delta_ = 0.0;

auto prev_time = std::chrono::system_clock::now();
double time_step = 1.0;

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
    throttle_pid.pid_init(150.0, 70.000, 5.0, -50.0, 200.0);
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
        
        // pubWrapper->throttle = 200;
        // pubWrapper->steering = 0.0;
        // pubWrapper->throttle = constant_velocity(5);
        
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
            target_vel = 5;
            pubWrapper->throttle = constant_velocity(5);
        }
        else
        {
            target_vel = 8.5;
            pubWrapper->throttle = constant_velocity(8.5);
        }
    }
    pubWrapper->update();

    /*
    * @brief save to CSV, littlebit sloppy but ah who cares
    */
    auto current_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_time = current_time - prev_time;
    if(elapsed_time.count()>= time_step)
    {
        std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
        log_to_csv(odomWrapper->velocity, target_vel, crosstrack_e_, delta_, odomWrapper->angle, odomWrapper->posX, odomWrapper->posY, current_time_t);
        prev_time = current_time;
    }
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
    
    /*
    * @brief no need to be sin, bcs it has passed to the car_vehicle_interface first
    */
    // ego_steer = error_angle;
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
    throttle_pid.show_error(true);
    //last_sim_time = sim_time;
    return throttle_out;
}


void pure_pursuit (double target_x, double target_y) 
{
    double ld_ = Kdd_ * odomWrapper ->velocity;
    double alpha_ = atan2(target_y - odomWrapper->posY, target_x - odomWrapper->posX) * 180 / M_PI - odomWrapper->angle;
    crosstrack_e_ = sin(alpha_)*ld_;
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

    delta_ = atan2(2*L_*sin(alpha_* M_PI / 180), ld_);
    ego_delta = delta_;
}

void log_to_csv(double velocity, double reference_speed, double crosstrack_e, double delta, double yaw, double posX, double posY, double time_step)
{
    std::ofstream file;
    file.open("/home/foccy/noetic_ws/src/car-simulator/vehicle_data_log.csv", std::ios::app); // Open file in append mode
    if (file.is_open())
    {
        file << velocity << ","
             << reference_speed << ","
             << crosstrack_e << ","
             << delta << ","
             << yaw << ","
             << posX << ","
             << posY << ","
             << time_step << "\n";
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing\n";
    }
}
