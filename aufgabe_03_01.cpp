
// standard includes
#include <cstdlib>
#include <iostream>
#include <math.h>

#include <opencv2/opencv.hpp>

#include <vector>

#define POINTS_PER_BATCH 10

typedef std::pair< double, double > PointType;
typedef std::vector< PointType >    PointListType;

/**
  * Applies an affine transformation to a given set of points.
  * @param points point set
  * @param m multiplicative matrix
  * @param t additive vector
  */
void transform(PointListType &points,
               const double m[2 * 2],
               const double t[2]) {
  for (PointListType::iterator it = points.begin(); it != points.end(); ++it) {
     double x = it->first;            // get point coordinates
     double y = it->second;
     
     double x1=x*m[0]+y*m[1]+t[0];
     double y1=x*m[2]+y*m[3]+t[1];

     it->first = x1;                   // update point coordinates
     it->second = y1;
  }
}

/**
  * Translates a set of points by a given vector,
  * @param points point set
  * @param dx translation in x direction
  * @param dy translation in y direction
  */
void translate(PointListType &points,
               const double dx, const double dy) {

  double m[2 * 2] = {1.0, 0.0,
                     0.0, 1.0};
  double t[2]     = {dx, dy};
  transform(points, m, t);
}

/**
  * Scales a given set of points anisotropically.
  * @param points point set
  * @param sx scaling factor in x direction
  * @param sy scaling factor in y direction
  */
void scale(PointListType &points, const double sx, const double sy) {
  //TODO fix this!
  double m[2 * 2] = {sx, 0.0,
                     0.0, sy};
  double t[2]     = {0.0, 0.0};
  transform(points, m, t);
}

/**
  * Scales a given set of points isotropically.
  * @param points point set
  * @param s scaling factor
  */
void scale(PointListType &points, const double s) {
  scale(points, s, s);
}

/**
  * Shears a given set of points according the coordinate axises.
  * @param points point set
  * @param a shearing parameter in x direction
  * @param b shearing parameter in y direction
  */
void shear(PointListType &points, const double a, const double b) {
  //TODO fix this
  double m[2 * 2] = {1.0, a,
                     b, 1.0};
  double t[2]     = {0.0, 0.0};
  transform(points, m, t);
}

/**
  * Rotates a given set of points by a given angle wrt. the coordinate origin.
  * @param points point set
  * @param angle rotation angle
  */
void rotate(PointListType &points, const double angle) {
  
  double m[2 * 2] = {cos(angle), sin(angle),
                     -sin(angle), cos(angle)};
  double t[2]     = {0.0, 0.0};
  transform(points, m, t);
}

void clearCanvas(cv::Mat &img,const int val=0)
{
    cv::Vec3b dotColor;
    dotColor[0]=val;
    dotColor[1]=val;
    dotColor[2]=val;
    
    cv::Size s = img.size();
    for(int x=0; x<s.width; x++)
      for(int y=0; y<s.height;y++)
	img.at<cv::Vec3b>(cv::Point(x,y))=dotColor;
}

/**
  * Draws a given set of points on the image canvas.
  * @param img Image
  * @param points point set
  * @param val gray value
  * @param clear clearing the image before drawing
  */
void drawPoints(cv::Mat &img, PointListType points, const int val = 127, const bool prompt = true, const bool clear = false) {
  
  if(clear)
    clearCanvas(img);
  cv::Vec3b dotColor;
  dotColor[0]=val;
  dotColor[1]=val;
  dotColor[2]=val;

  cv::Size s = img.size();

  for (PointListType::iterator it = points.begin(); it != points.end(); ++it)
  {
    if(it->first>0 && it->second>0 && it->first<s.width && it->second<s.height)
      img.at<cv::Vec3b>(cv::Point(it->first,it->second))=dotColor;
  }
}

int main(int argc, char **argv) {
  std::cout << "**************************************************\n"
            << "*** Introduction to Visual Computing, SS 2015  ***\n"
            << "*** Exercise 02-1                              ***\n"
            << "**************************************************\n"
            << "*** Author: Dipl.-Inf. Sven Sickert            ***\n"
            << "**************************************************\n"
	    << "**************************************************\n"
            << "*** Excercise Series 3 - Sascha Tetkov         ***\n"
            << "*** Exercise 03-1                              ***\n"
            << "**************************************************\n";
  
  PointListType vPoints;
  int w=800;
  int h=800;

  srand(42);
  double x=rand()%(w/2);
  double y=rand()%(h/2);
  for(int i=0; i<200;i++)
  {
    vPoints.push_back(PointType(x,y+i));
    vPoints.push_back(PointType(x+i,y));
  }

  cv::Mat canvas=cv::Mat::zeros( h, w, CV_8UC3);
  drawPoints(canvas,vPoints);
  cv::namedWindow("Translation", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Translation", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press
  translate(vPoints,rand()%(w/2),rand()%(h/2));
  drawPoints(canvas,vPoints,200);
  cv::imshow("Translation", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

  cvDestroyWindow("Translation");
  
  vPoints.clear();
  for(int i=0; i<200;i++)
  {
    vPoints.push_back(PointType(x,y+i));
    vPoints.push_back(PointType(x+i,y));
  }
  drawPoints(canvas,vPoints,125,true,true);
  cv::namedWindow("Scaling", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Scaling", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press
  scale(vPoints,0.5,1.5);
  drawPoints(canvas,vPoints,200);
  cv::imshow("Scaling", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press  

  cvDestroyWindow("Scaling");

  vPoints.clear();
  for(int i=0; i<200;i++)
  {
    vPoints.push_back(PointType(x,y+i));
    vPoints.push_back(PointType(x+i,y));
  }
  drawPoints(canvas,vPoints,125,true,true);
  cv::namedWindow("Shearing", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Shearing", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press
  shear(vPoints,0.5,1.5);
  drawPoints(canvas,vPoints,200);
  cv::imshow("Shearing", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press  
 
  cvDestroyWindow("Shearing");

  vPoints.clear();
  for(int i=0; i<200;i++)
  {
    vPoints.push_back(PointType(x,y+i));
    vPoints.push_back(PointType(x+i,y));
  }
  drawPoints(canvas,vPoints,125,true,true);
  cv::namedWindow("Rotation", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Rotation", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press
  rotate(vPoints,0.5);
  drawPoints(canvas,vPoints,200);
  cv::imshow("Rotation", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press  
  return 0;                                   // everything's gone fine ;)
}
