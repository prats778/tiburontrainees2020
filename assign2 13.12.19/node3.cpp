#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <sstream>
int comp;
void submit(const std_msgs::Int32::ConstPtr& a)
{
    comp = a->data;
    
 
}
void compare(const std_msgs::Int32::ConstPtr& n)
{
 if(n->data==comp)
 ROS_INFO("congo\n");
 else
 ROS_INFO("better luck next time");
}
	
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "node3");
  ros::NodeHandle n;
  ros::Subscriber sub1 = n.subscribe("ans", 1000, submit);
  ros::Subscriber sub2 = n.subscribe("sol", 1000, compare);
  ros::spin();
  return 0;
}
