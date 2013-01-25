#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <ros/console.h>

class ElektronTeleopJoy {
public:
        ElektronTeleopJoy();

//        double x,y,th;

//        void startFeature1();
        
//        void spinOnce();

//        bool teleopEnabled();
                
private:
        void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
//        void odomCallback(const nav_msgs::OdometryConstPtr& msg);

        ros::NodeHandle nh_;

        int linear_, angular_;
        int turbo_, stop_, feature1_, feature2_;
        double l_scale_, a_scale_;
        ros::Publisher vel_pub_;
        ros::Subscriber joy_sub_;
//        ros::Subscriber odom_sub_;

        // feature 1
//        bool feature1;
//        double angle, angleOld;
        
        
//        geometry_msgs::Twist vel;
        
};
/*
bool teleopEnabled() {
        if (feature1)
                return false;
        
        return true;
}

void startFeature1() {
        if (feature1)
                return;
                
        feature1 = true;
        angle = 0;
}

void spinOnce() {
        if (feature1) {
                angleOld = 
                vel_pub_.publish(vel);
        }
}
*/
ElektronTeleopJoy::ElektronTeleopJoy() {
        nh_.param("axis_linear", linear_, 1);
        nh_.param("axis_angular", angular_, 2);
        nh_.param("scale_angular", a_scale_, 1.0);
        nh_.param("scale_linear", l_scale_, 1.0);
        nh_.param("button_turbo", turbo_, 7);
        nh_.param("button_stop", stop_, 6);
        nh_.param("button_feature1", feature1_, 1);
        nh_.param("button_feature2", feature2_, 2);

        vel_pub_ = nh_.advertise<geometry_msgs::Twist> ("cmd_vel", 1);

        joy_sub_ = nh_.subscribe<sensor_msgs::Joy> ("joy", 10,
                        &ElektronTeleopJoy::joyCallback, this);

//        odom_sub_ = nh_.subscribe("odom", 1,
//                        &ElektronTeleopJoy::odomCallback, this);
}

void ElektronTeleopJoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {

        geometry_msgs::Twist vel;

//        if (teleopEnabled()) {
                vel.angular.z = a_scale_ * joy->axes[angular_];
                vel.linear.x = l_scale_ * joy->axes[linear_];
//        }
        
        vel.angular.x = joy->buttons[turbo_];
        vel.angular.y = joy->buttons[stop_];
        
//        if (joy->buttons[feature1_] > 0.5)
//                startFeature1 = true;
        vel.linear.y = joy->buttons[feature1_];
        vel.linear.z = joy->buttons[feature2_];

        vel_pub_.publish(vel);
}
/*
void odomCallback(const nav_msgs::OdometryConstPtr& msg) {
//        th = msg.pose.pose.orientation.y
//        x = msg.
}
*/
int main(int argc, char** argv) {
        ros::init(argc, argv, "piotrek_teleop_node");
        ElektronTeleopJoy elektron_teleop;
        
//        ros::rate loop_rate(10);
  
        ros::spin();      
/*        while (ros::ok()) {

                elektron_teleop.spinOnce();
                
                ros::spinOnce();
                loop_rate.spin();
        }
*/
}
