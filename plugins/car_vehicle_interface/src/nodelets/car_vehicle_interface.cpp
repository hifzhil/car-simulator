//register  stuff as plugins
#include <pluginlib/class_list_macros.h>
#include <car_vehicle_interface/car_vehicle_interface.h>
PLUGINLIB_EXPORT_CLASS(car_bridge::CarSimulatorVehicleInterface, nodelet::Nodelet)

namespace car_bridge
{
    void CarSimulatorVehicleInterface::onInit()
    {
        ros::NodeHandle pnh_ = getMTPrivateNodeHandle();
        //joint_points.velocities.resize(2);
            
        // one shoot delay so the plugins can loaded succesfully        
        // a pause also needed for ros to connect to /rosout
        double initialization_delay = 1.0;
        pnh_.param("initialization_delay_s", initialization_delay, 1.0);
        init_timer_ = pnh_.createWallTimer(ros::WallDuration(initialization_delay),
                                            &CarSimulatorVehicleInterface::initialize,
                                            this, 
                                            true);
            
            
    }

    void CarSimulatorVehicleInterface::initialize(const ros::WallTimerEvent &)
    {
        NODELET_INFO("Initializing controller nodelet");
        // take param from global namespace
        auto nh_ = getMTNodeHandle();
        // take param from private namespace
        auto pnh_ = getMTPrivateNodeHandle();

        car_cmd_sub_ = nh_.subscribe("/car_command", 1, 
                        &CarSimulatorVehicleInterface::HandleCmdInput,this);
        // car_info_sub_ =
        steering_pub_ = nh_.advertise<trajectory_msgs::JointTrajectory>("/mevi_model/steer_controller/command", 10);
        motor_left_pub_ = nh_.advertise<std_msgs::Float64>("/mevi_model/left_motor_controller/command", 10);
        motor_right_pub_ = nh_.advertise<std_msgs::Float64>("/mevi_model/right_motor_controller/command", 10);


        NODELET_INFO("Controller ready");
        update_car_cmd_ = nh_.createWallTimer(ros::WallDuration(ros::Rate(10.0)),
                                                &CarSimulatorVehicleInterface::update,
                                                this);
        
    }

    void CarSimulatorVehicleInterface::HandleCmdInput(const car_msgs::carCMD::ConstPtr &msg)
    {
        motor_cmd.data = msg->throttle;
        steering_cmd = msg->steer;
        //jointTrajectoryCMD.points.po[0] = steeringCMD;
        //diff_drive_motor();gmail
        //ackerman_steering();
    }
    
    void CarSimulatorVehicleInterface::update(const ros::WallTimerEvent &event) 
    {
        double max_steer = 0.785398;
        double max_speed = 10.0;
        trajectory.header.stamp = ros::Time::now();
        trajectory.header.frame_id = 'steer';
        trajectory.joint_names.resize(2);
        trajectory.joint_names[0] = "front_left_steer_joint";
        trajectory.joint_names[1] = "front_right_steer_joint";
        //trajectory.points.resize(1);

        steering_cmd = -0.78;
        point.positions.resize(2);
        point.positions[0] = steering_cmd;
        point.positions[1] = steering_cmd;
        point.time_from_start = ros::Duration(0.01);

        trajectory.points.resize(1);
        trajectory.points[0] = point;
        steering_pub_.publish(trajectory);

        // for throttle
        motor_cmd.data = 1.5;
        motor_left_pub_.publish(motor_cmd);
        motor_right_pub_.publish(motor_cmd);
    }
}