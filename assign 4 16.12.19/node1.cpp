#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("cam1", 1);
  image_transport::Publisher pub2 = it.advertise("cam2", 1);


  cv::VideoCapture cap(0);
  
  if(!cap.isOpened()) return 1;
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;
  
  ros::Rate loop_rate(50);
  int key=1;
    cv::namedWindow("view");
    cv::startWindowThread();
  
  while (nh.ok()) {
    cap>>frame;
    if(!frame.empty()){
    cv::imshow("view", frame);
    key=cv::waitKey(10);//&0xff;
    
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub.publish(msg);
      pub2.publish(msg);
      cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
     cv::destroyWindow("view");
     return 0;
}
