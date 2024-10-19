#include <ros/ros.h>
#include <string>

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
class PidController
{
private:
    bool is_first;
    std::chrono::steady_clock::time_point prev_time;
public:
    /**
    * @brief Constructor
    */
    PidController();

    /**
    * @brief Destructor.
    */
    virtual ~PidController();

    /**
    * @brief koefisien
    */

    double Kp;
    double Ki;
    double Kd;

    double cte;
    double diff_cte;
    double sum_cte;
    
    double limit_max;
    double limit_min;
    double prev_error;
    double dt;

    double u;
    double up;
    double ui;
    double ud;

    /**
    * @brief init
    */
    void pid_init (double kpp, double kii, double kdd, double min, double max);
    
    /**
    * @brief update error
    */    
    double update_error (double cte_current);
    
    /**
    * @brief kalkulasi total error
    */
    void show_error (bool debug=false);
    /**
    * @brief update delta time
    */
    // void update_delta_time (double new_delta);
};
#endif //PID_CONTROLLER_H