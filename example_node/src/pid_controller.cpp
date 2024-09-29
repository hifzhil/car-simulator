#include <example_node/pid_controller.h>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdlib.h>
//#include <algorithm>

PidController::PidController() {}

PidController::~PidController() {}

void PidController::pid_init(double kpp, double kii, double kdd, double min, double max)
{
    Kp = kpp;
    Ki = kii;
    Kd = kdd;
    limit_min = min;
    limit_maks = max;
    cte = 0.0;
    diff_cte = 0.0;
    sum_cte = 0.0;
    sum_old = 0.0;
    error_old = 0.0;
    is_first = true;
}

double PidController::update_error(double cte_current)
{
    // if (is_first) 
    // {
    // 	diff_cte = 0;
    // 	is_first = false;
    // } 
    // else 
    // {
    //     diff_cte = (cte_current - cte)/(delta_time * 0.7 + 0.3 * diff_cte);
        
    //     // if (std::abs(delta_time) < 0.0001)
    //     // {
    //     // diff_cte = 0;
    //     // }
    //     // else
	// 	// {
    //     // diff_cte = (cte_current - cte)/(delta_time * 0.7 + 0.3 * diff_cte);
    //     // }
    // }
    //sum_cte = (sum_cte + cte_current *0.3);
    up = cte_current*Kp;
    ui = sum_old + Ki*cte_current;
    ud = (cte_current - error_old)*Kd;
    u = up + ui + ud;
    /**
    *@brief anti wind up
    */
    if(u < limit_min)
    {
        u = limit_min;
    }
    else if(u > limit_maks)
    {
        u = limit_maks;
    }
    else
    {
        sum_old = ui;
    }
    error_old = cte_current;
    return u;
}
void PidController::show_error (bool debug)
{
    if(debug)
    {
        std::cout<<"Cte :"<<error_old<<" Control :"<<u<<"P : "<<up<<"I : "<<ui<<"D : "<<ud<<std::endl;
    }
}

void PidController::update_delta_time(double new_delta)
{
    delta_time = new_delta;
}