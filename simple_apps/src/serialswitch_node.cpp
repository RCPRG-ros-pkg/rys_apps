#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/Int16.h>

#include "serialswitch.hpp"


//ros::Time cmd_time;

SerialSwitch *sp;

int main(int argc, char** argv){
    ros::init(argc, argv, "serialswitch_node");
    ros::NodeHandle n;
    ros::NodeHandle nh("~");
  //  bool dump;
    ros::Publisher serialswitch_pub = n.advertise<std_msgs::Int16>("state",1);
    
    ros::Rate loop_rate(100);
    
    std::string dev;
    
 //   if(!nh.getParam("device", dev)){
//	dev = "dev/serialswitch";
 //   }

    std_msgs::Int16 state;
    state.data = 12;
    
  //  p = new SerialSwitch(dev);
 	sp = new SerialSwitch();
	    
	while(ros::ok()){
	  //  ros::Time current_time = ros::Time::now();
	    serialswitch_pub.publish(state);
	    
	    ros::spinOnce();
	    loop_rate.sleep();
	}

    
    return 0;
}       
