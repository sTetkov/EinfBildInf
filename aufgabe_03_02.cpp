
// standard includes
#include <cstdlib>
#include <iostream>
#include <math.h>

#include <opencv2/opencv.hpp>

typedef std::pair< double, double > PointType;

PointType p1;
PointType p2;
int clickCounter;

/**
  * Applies an affine transformation to a given set of points.
  * @param points point set
  * @param m multiplicative matrix
  * @param t additive vector
  */
PointType transform(PointType point,const double m[2 * 2]) {
    double x = point.first;            // get point coordinates
    double y = point.second;
     
    double x1=x*m[0]+y*m[1]+t[0];
    double y1=x*m[2]+y*m[3]+t[1];

    PointType res(x1,y1);
    return res;
}

double[2*2] getTransformationMatrix(PointType p1, PointType p2) {
	double x=0;
	double y=0;
	if(p2.first>=p1.first && p2.second>=p1.second) //First quarter
	{
		x=p2.first-p1.first;
		y=p2.second-p1.second;
	}
	else if (p2.first>=p1.first && p2.second<p1.second)//second quarter
	{
		x=p2.first-p1.first;
		y=p1.second-p2.second;
	}
	else if (p2.first<p1.first && p2.second<p1.second)//third quarter
	{
		x=p1.first-p2.first;
		y=p1.second-p2.second;
	}
	else//fourth quarter
	{
		x=p1.first-p2.first;
		y=p2.second-p1.second;
	}

	double angle=atan2(y,x);
	double m[2 * 2] = {cos(angle), sin(angle),
                          -sin(angle), cos(angle)};
	return m;
}


int colorVal(cv::Mat& img,PointType p, double m[2*2])
{
	PointType q=transform(p,m);
	cv::Size s = img.size();
	int x=(int)std::round(q.first);
	int y=(int)std::round(q.second);
	if(x<0 || x>=s.width || y<0 || y>=s.height)
		return 0;
	return img.at<uchar>(Point(x,y));

}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	  if(clickCounter==0)
	  {
		  p1.first=x;
		  p1.second=y;
	  }
	  if(clickCounter==1)
	  {
		  p2.first=x;
		  p2.second=y;
	  }
	  clickCounter++;
     }
}

int main(int argc, char **argv) {
  std::cout << "**************************************************\n"
            << "*** Introduction to Visual Computing, SS 2015  ***\n"
            << "*** Excercise Series 3 - Sascha Tetkov         ***\n"
            << "*** Exercise 03-2                              ***\n"
            << "**************************************************\n";
  
  clickCounter=0;
  cv::Mat img=imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  double m[2*2]=getTransformationMatrix(p1,p2);
  cv::Size s = img.size();

  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Image", imgPost);// show image
  cv::setMouseCallback("Image", CallBackFunc, NULL);
  while(clickCounter<2)
  {}

  cv::Mat imgPost=cv::Mat::zeros(s.width,s.height,uchar);
  for (int x=0;x<s.width;x++)
	  for(int y=0;y<s.height;y++)
		  imgPost.at<uchar>(Point(x,y))=colorVal(img,PointType(x,y),m);
  
  cv::namedWindow("Rotation", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("Rotation", imgPost);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

  return 0;                                   // everything's gone fine ;)
}
