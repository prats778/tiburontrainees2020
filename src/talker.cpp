#include"ros/ros.h"
#include"std_msgs/Int32.h"

int main(int argc,char **argv)
{ ros::init(argc,argv,"talker");
  ros::NodeHandle n;
  ros::Publisher pub=n.advertise<std_msgs::Int32>("info",1000);
  ros::Rate loop_rate(10);
  std_msgs::Int32 no;
     no.data=0;
  while(ros::ok())
  {  
     ROS_INFO("number is %d",no.data);
     pub.publish(no);
     ros::spinOnce();
     loop_rate.sleep();
     no.data++;
  }
  return 0;
}

