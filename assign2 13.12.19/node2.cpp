#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"

ros::Publisher userans;
void callback(const std_msgs::String msg1)
{
    ROS_INFO("The question is :-%s\n 1-burj khalifa 2-burj al-ar 3-Eifel tower 4-none of these   \n" ,msg1.data.c_str());
    ROS_INFO("pls enter ur answer") ;
    std_msgs::Int32 a;	
    std::cin>>a.data;
	
    ROS_INFO("My answer is %d",a.data);
    userans.publish(a); 
}
int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "node2");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("ques", 1000, callback);
  userans = n.advertise<std_msgs::Int32>("ans", 1000);
  ros::spin();
  return 0;
}


