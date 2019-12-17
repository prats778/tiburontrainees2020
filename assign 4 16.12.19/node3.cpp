#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;
const String window_name ="threshold Demo";
int threshold_type=0;

int threshold_value;
const String trackbar_type="Type: \n 0:Binary \n 1:Binary Inverted \n 2:Truncate \n 3:to zero\n 4:to zero inverted";  
  const int max_value = 255;
  const String window_capture_name = "Video Capture";
  const String window_detection_name = "Object Detection";
 
const int max_type=4;

int threshold_value1;
int threshold_value2;
int threshold_value3;

void Threshold_red(int,void*);
void Threshold_green(int,void*);
void Threshold_blue(int,void*);
void Threshold_show(int,void*);

Mat frame,frame_RGB,frame_threshold,src,dst,rgb[3],rgb2[3];

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
 try
  {
   src=cv_bridge::toCvShare(msg,"bgr8")->image;
  
   cv::imshow("view3",src);
   cv::waitKey(30);
  }
 catch (cv_bridge::Exception& e)
 {
   ROS_ERROR("Could not convert from '%s' to 'bgr8'.",msg->encoding.c_str());
  }

  split(src,rgb);
 
  rgb2[0]=rgb[0];
  rgb2[1]=rgb[1];
  rgb2[2]=rgb[2];

  //imshow("red",rgb[0]);
  //imshow("green",rgb[1]);
  //imshow("blue",rgb[2]); 
 
  dst= Mat::zeros(src.rows,src.cols,CV_8UC1);
 
  createTrackbar( "track1",
                  window_name, &threshold_type,
                  max_type, Threshold_show);
  createTrackbar( "track2",
                  window_name, &threshold_type,
                  max_type, Threshold_green );
  createTrackbar( "track3",
                  window_name, &threshold_type,
                  max_type, Threshold_blue );

  createTrackbar("R:",window_name,&threshold_value1,max_value,Threshold_red);
  createTrackbar("G:",window_name,&threshold_value2,max_value,Threshold_green);
  createTrackbar("B:",window_name,&threshold_value3,max_value,Threshold_blue);

  frame=src;
  cvtColor(frame,frame_RGB,COLOR_BGR2RGB);
  Threshold_red(0,0);
  Threshold_green(0,0);
  Threshold_blue(0,0);
  Threshold_show(0,0);

 //while(true)  {
                int key=waitKey(30);
                //if(key==27)break;
             //  }
}


int main(int argc, char** argv)
{ ros::init(argc, argv, "image_listener2");
  ros::NodeHandle nh;
  namedWindow("view3");
  namedWindow(window_name);
  //namedWindow("red");
  //namedWindow("green");
  //namedWindow("blue");
  
  startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("cam2", 1, imageCallback);
  ros::spin();
  destroyWindow("view3");
  
    return 0;
}

int num=3;

void Threshold_red( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

 threshold(rgb[0],rgb2[0],threshold_value1,255,threshold_type);
 cv::merge(rgb2,num,dst);
 imshow(window_name,dst);
}
void Threshold_green( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold(rgb[1],rgb2[1],threshold_value2,255,threshold_type);
 cv::merge(rgb2,num,dst);
 imshow(window_name,dst);
}
void Threshold_blue( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold(rgb[2],rgb2[2],threshold_value3,255,threshold_type);
 cv::merge(rgb2,num,dst);
 imshow(window_name,dst);
}
void Threshold_show(int ,void* )
{
  cv::merge(rgb2,num,dst);
  imshow(window_name,dst);
}

