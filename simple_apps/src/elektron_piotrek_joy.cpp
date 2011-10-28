#include <ros/ros.h>
#include <joy/Joy.h>
#include <geometry_msgs/Twist.h>
#include <ros/console.h>

class ElektronTeleopJoy {
public:
	ElektronTeleopJoy();

private:
	void joyCallback(const joy::Joy::ConstPtr& joy);

	ros::NodeHandle nh_;

	int linear_, angular_;
	int turbo_, stop_, feature1_, feature2_;
	double l_scale_, a_scale_;
	ros::Publisher vel_pub_;
	ros::Subscriber joy_sub_;

};

ElektronTeleopJoy::ElektronTeleopJoy() {
	nh_.param("axis_linear", linear_, 1);
	nh_.param("axis_angular", angular_, 3);
	nh_.param("scale_angular", a_scale_, 1.0);
	nh_.param("scale_linear", l_scale_, 0.23);
	nh_.param("button_turbo", turbo_, 7);
	nh_.param("button_stop", stop_, 6);
	nh_.param("button_feature1", feature1_, 1);
	nh_.param("button_feature2", feature2_, 2);

	vel_pub_ = nh_.advertise<geometry_msgs::Twist> ("cmd_vel", 1);

	joy_sub_ = nh_.subscribe<joy::Joy> ("joy", 10,
			&ElektronTeleopJoy::joyCallback, this);

}

void ElektronTeleopJoy::joyCallback(const joy::Joy::ConstPtr& joy) {
	geometry_msgs::Twist vel;
	vel.angular.z = a_scale_ * joy->axes[angular_];
	vel.linear.x = l_scale_ * joy->axes[linear_];

	vel.angular.x = joy->buttons[turbo_];
	vel.angular.y = joy->buttons[stop_];
	vel.linear.y = joy->buttons[feature1_];
	vel.linear.z = joy->buttons[feature2_];

	vel_pub_.publish(vel);

	ROS_DEBUG("joy: %d %d\n", (int)vel.angular.z, (int)vel.linear.x);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "piotrek_teleop_node");
	ElektronTeleopJoy elektron_teleop;
        ROS_DEBUG("elektron_piotrek_joy.cpp: main()\n");
	ros::spin();
}
