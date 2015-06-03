// standard includes
#include <iostream>
#include <vector>

// opencv includes
#include <opencv2/opencv.hpp>

void my_mouse_callback(int event, int x, int y, int flags, void *param){
  switch( event ){
      case CV_EVENT_LBUTTONDOWN:
          std::cout << "LBUTTONDOWN" << std::endl;
          std::cout << " x-position: " << x << " y-position: " << y << std::endl;
          break;

      case CV_EVENT_RBUTTONDOWN:
          std::cout << "RBUTTONDOWN" << std::endl;
          break;
  }
}

int main(int argc, char** argv) {

  std::cout << "**************************************************\n"
            << "*** Introduction to Visual Computing, SS 2015  ***\n"
            << "*** Exercise 02-2 OpenCV Mouse Demo            ***\n"
            << "**************************************************\n"
            << "*** Author: Dipl.-Inf. Sven Sickert            ***\n"
            << "**************************************************\n\n"
            << "This program demonstrates the usage of the mouse in the OpenCV library.\n\n";

  if (argc < 2) {
    std::cerr << "ERROR: No filename passed!" << std::endl;
    return 0;
  }

  cv::Mat img = cv::imread(argv[1]);

  cv::namedWindow("My Image Window", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::setMouseCallback("My Image Window", my_mouse_callback);
  cv::imshow("My Image Window", img);// show image
  std::cout << "Press any key to continue ..." << std::endl;
  cv::waitKey();                     // wait for key press

  return 0;
}
