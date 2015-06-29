
#define OPENCV_MODE

// standard includes
#include <iostream>
#include <vector>

// opencv includes
#include <opencv2/opencv.hpp>

#include "./helpers.h"
#include "./geometry.h"

void draw2DObject(cv::Mat &img, const Object2DType object) {
  Point2DListType _points = object.first;
  EdgeListType    _edges  = object.second;
  
  for (EdgeListType::iterator itEdges = _edges.begin(); 
       itEdges != _edges.end(); 
       ++itEdges) {
    cv::Point p1(_points[itEdges->first](0), _points[itEdges->first](1));
    cv::Point p2(_points[itEdges->second](0), _points[itEdges->second](1));
    cv::line(img, p1, p2, cv::Scalar(255, 255, 255));
  } 
}

void draw2DObjects(cv::Mat &img, const Object2DListType objects) {
  for (Object2DListType::const_iterator it = objects.begin();
       it != objects.end();
       ++it) {
    draw2DObject(img, *it);
  }
}

int main(int argc, char** argv) {

  std::cout << "**************************************************\n"
            << "*** Introduction to Visual Computing, SS 2015  ***\n"
            << "*** Exercise 03: OpenCV Stub                   ***\n"
            << "**************************************************\n"
            << "*** Author: Dipl.-Inf. Sven Sickert            ***\n"
            << "**************************************************\n\n";

  // create a new window
  cv::namedWindow("My Image Window", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::Mat img(480, 640, CV_8UC3);
  
  Object3DListType objects3D;
  create3DObject(objects3D);
  Object2DListType objects2D = project2D(objects3D);
  draw2DObjects(img, objects2D);

  cv::imshow("My Image Window", img);
  
  std::cout << "Press any key to continue ..." << std::endl;
  cv::waitKey();                     // wait for key press

  return 0;
}
