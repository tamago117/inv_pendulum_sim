#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>
#include "nav_msgs/Odometry.h"

#include "PID.h"

const double kp = 21;
const double kd = 17;
const double ki = 0.1;
const double kx = 50;
const double kv = 0;

double yaw;
double roll;
void imu_callback(const sensor_msgs::Imu& imu_message)
{
    yaw = imu_message.orientation.y;
    //cmd_vel.linear.y = joy_data.axes[3];
    roll = imu_message.orientation.z;
}

double dis;
void odom_callback(const nav_msgs::Odometry& odom_message)
{
    dis = odom_message.pose.pose.position.x;
    //std::cout<<dis<<std::endl;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pendulum_controller");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::Subscriber imu_sub = nh.subscribe("imu/data", 10, imu_callback);
    ros::Subscriber odom_sub = nh.subscribe("dtw_robot/diff_drive_controller/odom", 10, odom_callback);
    PID pid(kp,ki,kd);

    geometry_msgs::Twist cmd_vel;
    ros::Rate loop_rate(1000);
    
    while(ros::ok())
    {
        
        cmd_vel.linear.x = -pid.updata(0, yaw);
        //cmd_vel.linear.x = -dis*100;
        pub.publish(cmd_vel);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}