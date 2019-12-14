#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<opencv2/highgui/highgui.hpp>
#include<cv_bridge/cv_bridge.h>

void imagecallback(const sensor_msgs::ImageConstPtr& msg)
{
 try
 {
  cv::imshow("view2",cv_bridge::toCvShare(msg,"bgr8")->image);
  cv::waitKey(30);
 }
 catch(cv_bridge::Exception& e)
 {
  ROS_ERROR("could not convert from '%s' to 'bgr8'. ",msg->encoding.c_str())  ;
 }
}
int main(int argc,char **argv)
{
  ros::init(argc,argv,"image_show");
  ros::NodeHandle nh;
  cv::namedWindow("view2");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image2",1,imagecallback);
  ros::spin();
  cv::destroyWindow("view2");
}

