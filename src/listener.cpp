#include "ros/ros.h"
#include "std_msgs/Int32.h"

void info2Callback(const std_msgs::Int32::ConstPtr& no2)
{
  ROS_INFO("I got the square [%d]", no2->data);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");

  
  ros::NodeHandle nh1;

  
  ros::Subscriber sub1 = nh1.subscribe("info2", 1000, info2Callback);

  
  ros::spin();

  return 0;
}
