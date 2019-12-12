#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

ros::Publisher pub2;

void infoCallback(const std_msgs::Int32::ConstPtr& no)
{
  ROS_INFO("I heard: [%d]", no->data);
 

  int ctr=no->data;
  int sq=ctr*ctr;
  std_msgs::Int32 no2;
  no2.data=sq; 
     
   
     ROS_INFO("publishing its square %d",no2.data);
     pub2.publish(no2);     


}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "intermediate");

 
  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("info", 1000, infoCallback);
  pub2=n.advertise<std_msgs::Int32>("info2",1000);

  ros::spin();

  

  return 0;
}
