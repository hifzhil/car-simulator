/**
* @brief this is ros header
*/
#include <nodelet/nodelet.h>
#include <ros/ros.h>


/**
* @brief msg header
*/
#include <std_msgs/Float64.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>
#include <car_msgs/carCMD.h>

/**
* @brief c header
*/
#include <vector>
#include <string>
#include <thread>

// using JointTrajectory = trajectory_msgs::JointTrajectory;
// using JointPoints = trajectory_msgs::JointTrajectoryPoint;
using Float64 = std_msgs::Float64;
// using CarCMD = car_msgs::carCMD;

namespace car_bridge
{
class CarSimulatorVehicleInterface : public nodelet::Nodelet
{
    public : 
        ~CarSimulatorVehicleInterface() override
        {
        }
        void onInit() override;
                // double ackermannSteering(double angle)
        // {
        //     double 
        // }

    private : 
        // ros::Subscriber steering_sub_;
        ros::Subscriber car_cmd_sub_;
        ros::Publisher steering_pub_;
        ros::Publisher motor_left_pub_;
        ros::Publisher motor_right_pub_;
        trajectory_msgs::JointTrajectory trajectory;
        trajectory_msgs::JointTrajectoryPoint point;
        std_msgs::Float64 motor_cmd;
        double steering_cmd;
        ros::WallTimer update_car_cmd_;
        ros::WallTimer init_timer_;
        car_msgs::carCMD car_cmd;
        std::mutex mtx;
        
        double front_track_width_ = 0.830;
        double rear_track_width_ = 0.750;
        double wheel_base_length_ = 0.98;

        double max_steer_ = 0.78;
        double max_speed_ = 10;

        void initialize(const ros::WallTimerEvent &);

        void HandleCmdInput(const car_msgs::carCMD &msg);

        void update(const ros::WallTimerEvent &event); 
}; //class
} //namespace