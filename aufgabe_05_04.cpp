
// standard includes
#include <cstdlib>
#include <iostream>
#include <math.h>

#include <opencv2/opencv.hpp>

#define e 2.71828182845904523536
#define ONE_APROX_LOW  0.9999999
#define ONE_APROX_HIGH 1.0000001

void countPixels(int* vec,cv::Mat img)
{
  for(int i=0;i<256;i++)
    vec[i]=0;
  cv::Size s=img.size();
  for (int x=0;x<s.width;x++)
    for(int y=0;y<s.height;y++)
      vec[img.at<uchar>(cv::Point(x,y))]++;
}

int getMax(int* vec)
{
  int res=0;
  for (int i=0;i<256;i++)
    res+=vec[i];
  return res;
}

cv::Mat printHistogram(int* vec)
{
  int maxVal=getMax(vec);
  double scale=500.0/maxVal;
  cv::Mat canvas=cv::Mat::zeros( 600, 600,CV_8U);
  int curHeight=0;
  for(int i=0;i<256;i++)
  {
    curHeight+=vec[i];
    cv::line(canvas,cv::Point(i*2+50,550),cv::Point(i*2+50,550-(curHeight*scale)),cv::Scalar(254,254,254),2,8);
  }
  return canvas;
}

cv::Mat grayscaleLinearization(int* vec,cv::Mat img)
{
  cv::Size s=img.size();
  int pixelAmount=s.width*s.height;
  double* f=new double[256];
  double sum=0.0;
  for(int i=0;i<256;i++)
      {
        sum+=((double)vec[i])/((double)pixelAmount);
        f[i]=sum*255.0;
      }
  cv::Mat canvas=cv::Mat::zeros( s.height, s.width,CV_8U);
  for (int x=0;x<s.width;x++)
    for(int y=0;y<s.height;y++)
      canvas.at<uchar>(cv::Point(x,y))=(uchar)(f[img.at<uchar>(cv::Point(x,y))]);
  return canvas;
}

int main(int argc, char **argv) {
  std::cout << "**************************************************\n"
            << "*** Introduction to Visual Computing, SS 2015  ***\n"
            << "*** Excercise Series 5 - Sascha Tetkov         ***\n"
            << "*** Exercise 05-1                              ***\n"
            << "**************************************************\n";

  cv::Mat img=cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Image", img);// show image

  int* vec=new int[256];
  countPixels(vec,img);

  cv::namedWindow("Histogram", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Histogram", printHistogram(vec));// show image

  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press
  std::cout<<"Creating window\n";

  cv::Mat procImg=grayscaleLinearization(vec,img);
  countPixels(vec,procImg);
  cv::namedWindow("Linearization", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Linearization", procImg);// show image



  cv::namedWindow("Linearized Histogram", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Linearized Histogram", printHistogram(vec));// show image

  cv::waitKey();                     // wait for key press

  return 0;                                   // everything's gone fine ;)
}
