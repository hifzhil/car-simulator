#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <std_msgs/Float64.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <car_msgs/carCMD.h>

using JointTrajectory = trajectory_msgs::JointTrajectory;
using Float64 = std_msgs::Float64;
using CarCMD = car_msgs::carCMD;

namespace car_vehicle_interface
{
class MeviVehicleInterface : public nodelet::Nodelet
{
    public : 
        MeviVehicleInterface()
        {
            car_cmd_sub_ = handler_.subscribe("/mevi_command", 1, 
                            &MeviVehicleInterface::HandleCmdInput,this);
            // car_info_sub_ =
            steering_pub_ = handler_.advertise<JointTrajectory>("/mevi_model/steer_controller/command", 10);
            motor_left_pub_ = handler_.advertise<Float64>("/mevi_model/left_motor_controller/command", 10);
            motor_right_pub_ = handler_.advertise<Float64>("/mevi_model/right_motor_controller/command", 10);

        }
        ~MeviVehicleInterface()
        { 
        }
        Float64 motor_left_cmd;
        Float64 motor_right_cmd;
        double steeringCMD;
        JointTrajectory jointTrajectoryCMD;

        // double ackermannSteering(double angle)
        // {
        //     double 
        // }

    void HandleCmdInput(const car_msgs::carCMD::ConstPtr &msg)
    {
        motor_left_cmd.data = msg->throttle;
        motor_right_cmd.data = msg->throttle;   
        steeringCMD = msg->steer;
        //jointTrajectoryCMD.points[0] = steeringCMD;
        //jointTrajectoryCMD.points.po[0] = steeringCMD;
        //diff_drive_motor();gmail
        //ackerman_steering();

    }

    void update() 
    {
        motor_left_pub_.publish(motor_left_cmd);
        motor_right_pub_.publish(motor_right_cmd);
        //steering_pub_.publish(jointTrajectoryCMD);
    }

    private : 
        ros::NodeHandle handler_;
        // ros::Subscriber steering_sub_;
        ros::Subscriber car_cmd_sub_;
        ros::Publisher steering_pub_;
        ros::Publisher motor_left_pub_;
        ros::Publisher motor_right_pub_;




}; //class
} //namespace

//register this stuff as plugins
