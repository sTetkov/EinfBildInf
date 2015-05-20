// standard includes
#include <iostream>
#include <vector>
#include <stdlib.h>

// opencv includes
#include <opencv2/opencv.hpp>

#define RND_LINE_AMT 10
int getOctant(int x0, int y0, int x1, int y1)
{
  int dx=x1-x0;
  int dy=y1-y0;
  if(dx>0 && dy>0)
  {
    if(dx>dy)
      return 0;
    else
      return 1;
  }
  if (dx<0 && dy>0)
  {
    if(-dx < dy)
      return 2;
    else
      return 3;
  }
  if (dx < 0 && dy < 0)
  {
    if(dx<dy)
      return 4;
    else
      return 5;
  }
  if(dx<(-dy))
    return 6;
  return 7;

}
void DrawLineBresenham(int x0, int y0, int x1, int y1, cv::Mat canvas)
{
  int y=y0;
  int x=x0;

  int octant=getOctant(x0,y0,x1,y1);

  int dx=x1-x0;
  int dy=y1-y0;
  int e;

  cv::Vec3b dotColor;
  dotColor[0]=254;
  dotColor[1]=254;
  dotColor[2]=254;

  canvas.at<cv::Vec3b>(cv::Point(x,y))=dotColor;

  std::cout<<"Octant : "<<octant<<"\n";
  switch(octant)
  {
    case 0:
      e=dx>>1;
      while(x<=x1)
      {
        x++;
        e=e-dy;
        if( e < 0)
        {
          y = y+1;
          e = e + dx;
        }
        canvas.at<cv::Vec3b>(cv::Point(x,y))=dotColor;
      }
      break;
    case 1:
      e=dy>>1;
      while(y<=y1)
      {
        y++;
        e=e-dx;
        if( e < 0)
        {
          x = x+1;
          e = e + dy;
        }
        canvas.at<cv::Vec3b>(cv::Point(x,y))=dotColor;
      }
      break;
    default:
      break;
  }
}

void BresenhamCircle(int x0, int y0, int radius, cv::Mat canvas)
{
  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  cv::Vec3b dotColor;
  dotColor[0]=254;
  dotColor[1]=254;
  dotColor[2]=254;

  canvas.at<cv::Vec3b>(cv::Point(x0, y0 + radius))=dotColor;
  canvas.at<cv::Vec3b>(cv::Point(x0, y0 - radius))=dotColor;
  canvas.at<cv::Vec3b>(cv::Point(x0 + radius, y0))=dotColor;

  canvas.at<cv::Vec3b>(cv::Point(x0 - radius, y0))=dotColor;
  while(x < y)
  {
    if(f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;

    canvas.at<cv::Vec3b>(cv::Point(x0 + x, y0 + y))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 - x, y0 + y))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 + x, y0 - y))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 - x, y0 - y))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 + y, y0 + x))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 - y, y0 + x))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 + y, y0 - x))=dotColor;
    canvas.at<cv::Vec3b>(cv::Point(x0 - y, y0 - x))=dotColor;
  }
}

bool isInPolygon(cv::Point a,cv::Point b,cv::Point c,cv::Point x)
{
  return false;
}

int main(int argc, char** argv)
{
  std::cout << "**************************************************\n"
            << "*** Übung 02 Aufgabe 1                         ***\n"
            << "*** Sascha Tetkov                              ***\n"
            << "**************************************************\n"
            << "\n";

  int w=1200;
  int h=600;

  double t;
  cv::Mat canvas=cv::Mat::zeros( h, w, CV_8UC3);
  srand(42);
  cv::line(canvas,cv::Point(w/3,0),cv::Point(w/3,h),cv::Scalar(0,254,0),1,8);
  cv::line(canvas,cv::Point(2*(w/3),0),cv::Point(2*(w/3),h),cv::Scalar(0,254,0),1,8);
  for(int i=0; i<RND_LINE_AMT;i++)
  {
    int x1=rand() % (w/3);
    int y1=rand() % h;
    int x2=x1+rand() % ((w/3)-x1);
    int y2=y1+rand() % (h-y1);

    t=(double)cv::getTickCount();
    DrawLineBresenham(x1,y1,x2,y2,canvas);
    t=((double)cv::getTickCount()-t)/cv::getTickFrequency();
    std::cout<<"Bresenham Line: "<<t<<" seconds\n";
    t=(double)cv::getTickCount();
    cv::line(canvas,cv::Point(x1+(w/3),y1),cv::Point(x2+(w/3),y2),cv::Scalar(254,254,254),1,8);
    t=((double)cv::getTickCount()-t)/cv::getTickFrequency();
    std::cout<<"OpenCV Line: "<<t<<" seconds\n";
  }
  cv::namedWindow("My Image Window", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  cv::imshow("My Image Window", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

  canvas=cv::Mat::zeros( h, w, CV_8UC3);

  cv::line(canvas,cv::Point(w/3,0),cv::Point(w/3,h),cv::Scalar(0,254,0),1,8);
  cv::line(canvas,cv::Point(2*(w/3),0),cv::Point(2*(w/3),h),cv::Scalar(0,254,0),1,8);

  t=(double)cv::getTickCount();
  BresenhamCircle(200,300,190,canvas);
  t=((double)cv::getTickCount()-t)/cv::getTickFrequency();
  std::cout<<"Bresenham Circle: "<<t<<" seconds\n";

  t=(double)cv::getTickCount();
  cv::circle(canvas,cv::Point(600,300),190,cv::Scalar(254,254,254));
  t=((double)cv::getTickCount()-t)/cv::getTickFrequency();
  std::cout<<"OpenCv Circle: "<<t<<" seconds\n";

  cv::imshow("My Image Window", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

  canvas=cv::Mat::zeros( h, w, CV_8UC3);

  cv::Point a=cv::Point(10,10);
  cv::Point b=cv::Point(900,450);
  cv::Point c=cv::Point(30,500);
  cv::line(canvas,a,b,cv::Scalar(254,254,254),1,8);
  cv::line(canvas,b,c,cv::Scalar(254,254,254),1,8);
  cv::line(canvas,c,a,cv::Scalar(254,254,254),1,8);

  cv::Vec3b dotColor;
  dotColor[0]=254;
  dotColor[1]=254;
  dotColor[2]=254;

  for (int i=0; i<200;i++)
  {
    int x=rand() % w;
    int y=rand() % h;
    if(isInPolygon(a,b,c,cv::Point(x,y)))
    {
      dotColor[1]=0;
      dotColor[2]=0;
      canvas.at<cv::Vec3b>(cv::Point(x,y))=dotColor;
    }
    else
    {
      dotColor[1]=254;
      dotColor[2]=254;
      canvas.at<cv::Vec3b>(cv::Point(x,y))=dotColor;
    }
  }

  cv::imshow("My Image Window", canvas);// show image
  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

}
