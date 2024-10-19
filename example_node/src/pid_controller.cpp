#include <example_node/pid_controller.h>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <chrono>
//#include <algorithm>

PidController::PidController() {}

PidController::~PidController() {}

void PidController::pid_init(double kpp, double kii, double kdd, double min, double max)
{
    Kp = kpp;
    Ki = kii;
    Kd = kdd;
    limit_min = min;
    limit_max = max;
    sum_cte = 0.0;
    prev_error = 0.0;
    is_first = true;
}

double PidController::update_error(double cte_current)
{
    /*
    * @brief dt is a elapsed time or delta_T
    */
    auto current_time = std::chrono::steady_clock::now();
    double dt;
    if (is_first)
    {
        is_first = false;
        dt = 0.0;
        prev_time = current_time;
    }
    else
    {
        std::chrono::duration<double> elapsed = current_time - prev_time;
        dt = elapsed.count();
        ROS_INFO("dt: %f", dt);
    }
    double error = cte_current;
    
    /*
    * @brief now we can calculate the P, I, and D terms
    */
    up = Kp * error;
    if (dt > 0)
    {
        sum_cte += error * dt;
        ui = Ki * sum_cte;
        ud = Kd * (error - prev_error)/ dt;
    }
    else
    {
        ui = 0;
        ud = 0;
    }

    /*
    * @brief compute the control output
    */
    u = up + ui + ud;
    
    /**
    *@brief anti windup
    */
    if(u < limit_min)
    {
        u = limit_min;
        sum_cte -= error * dt;
    }
    else if(u > limit_max)
    {
        u = limit_max;
        sum_cte -= error * dt;
    }

    /*
    * @brief update the prev val
    */
    prev_error = error;
    prev_time = current_time;

    return u;
}
void PidController::show_error (bool debug)
{
    if(debug)
    {
        ROS_INFO("Cte: %.3f, Control: %.3f, P: %.3f, I: %.3f, D: %.3f", prev_error, u, up, ui, ud);
    }
}