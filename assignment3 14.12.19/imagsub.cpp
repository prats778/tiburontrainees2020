#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <sstream>

image_transport::Publisher pub;
int count=0;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{ int key=1;
  cv::Mat frame;
  try
  { ROS_INFO("ENTER S FOR SAVING AN IMAGE AND P FOR TRANSFERRING image");
    frame=cv_bridge::toCvShare(msg,"bgr8")->image;

  
    cv::imshow("view", frame);
    key=cv::waitKey(10)&0xff;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
  if(key=='s')
    { 
      std::stringstream ss;
      ss<<"/home/prats/catkin_ws/src/task3/src/img"<<count++<<".jpg";
      cv::imwrite(ss.str(),frame);}
  else if (key=='p')
        pub.publish(msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
  pub=it.advertise("camera/image2",1);
  ros::spin();
  cv::destroyWindow("view");
  return 0;

}
