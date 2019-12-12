#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <sstream>


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "node1");

  
  ros::NodeHandle n;

  
  ros::Publisher ques_pub = n.advertise<std_msgs::String>("ques", 1000);
  ros::Publisher ans_pub = n.advertise<std_msgs::Int32>("sol", 1000);
    ros::Rate loop_rate(0.5); 
    
    while(ros::ok())
    {

    std_msgs::String msg1;
    std_msgs::String msg2;

    int a=2;
    std::stringstream ss1,ss2;
    std_msgs::Int32 n;
    n.data=a;
    ss1<<"name the tallest building in the world";
    ss2<<"1-burj khalifa 2-burj al-ar 3-Eifel tower 4-none of these";
    msg1.data = ss1.str();
    msg2.data = ss2.str();
       

    ROS_INFO("Question is %s", msg1.data.c_str());
    ROS_INFO("UR OPTIONS ARE %s",msg2.data.c_str());

    
    ques_pub.publish(msg1);
    ans_pub.publish(n);
    loop_rate.sleep();

    ros::spinOnce();
    }

  return 0;
}

