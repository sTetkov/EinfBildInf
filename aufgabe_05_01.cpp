
// standard includes
#include <cstdlib>
#include <iostream>
#include <math.h>

#include <opencv2/opencv.hpp>

#define e 2.71828182845904523536
#define ONE_APROX_LOW  0.9999999
#define ONE_APROX_HIGH 1.0000001

void fillImgMatr(int* I,int m, int n, cv::Mat img, int xCoord, int yCoord)
{
  int offsetX=(m-1)/2;
  int offsetY=(n-1)/2;
  int i=0;
  cv::Size s=img.size();
  int xP;
  int yP;
  for(int x=xCoord-offsetX;x<=xCoord+offsetX;x++)
    for(int y=yCoord-offsetY;y<=yCoord+offsetY;y++)
    {
      xP=x;
      yP=y;
      if(x<0)
        xP=0;
      if(y<0)
        yP=0;
      if(x>=s.width-1)
        xP=s.width-2;
      if(y>=s.height-1)
        yP=s.height-2;
      I[i]=((int)img.at<uchar>(cv::Point(xP,yP)));
      i++;
    }
}

uchar getFoldedPixel(int* iMtr,double* mtr,int m, int n)
{
  double res=0;
  for (int i=0;i<n;i++)
    for(int j=0;j<m;j++)
    {
      //std::cout<<res<<" += "<<iMtr[mMid*n+i]<<" * "<<mtr[mMid+i*m]<<"\n";
      res+=((double)(iMtr[j*n+i]))*mtr[i*m+j];
    }
  if(res>255)
    res=255;
  if(res<0)
    res=0;
  return (uchar)res;
}

cv::Mat applyMatrixToImage(double* mtr, int m, int n, cv::Mat img)
{
  std::cout<<"applyMatrixToImage\n";
  //Virtual pixels adjacent to the border have the same color as the borderpixel itself
  cv::Size s=img.size();
  cv::Mat canvas=cv::Mat::zeros( s.height,s.width,CV_8U);
  std::cout<<"Image "<<s.width<<"x"<<s.height<<"\n";
  int* imgMatr=new int[m*n];
  for(int x=0; x<s.width;x++)
    for(int y=0;y<s.height;y++)
    {
      fillImgMatr(imgMatr,n,m,img,x,y);
      canvas.at<char>(cv::Point(x,y))=getFoldedPixel(imgMatr,mtr,m,n);
    }
  std::cout<<"deleting imgMatr\n";
  delete[] imgMatr;
  return canvas;
}

cv::Mat applyAVGFilter(cv::Mat img)
{
  std::cout<<"applyAVGFilter\n";
  double val=1.0/9.0;
  double m[3*3]={val, val, val,
                  val, val, val,
                  val, val, val};
  cv::Mat res=applyMatrixToImage(m,3,3,img);
  std::cout<<"Finished applying filter\n";
  return res;
}

double calculateGaussianCoefficient(int m, int i, int j)
{
  double stdDev=m/5.0;
  double pwr=(pow((i-(m/2)),2) + pow((j-(m/2)),2))/2*pow(stdDev,2);
  return pow(e,-pwr);
}

void fillGaussianMatrix(double* mtr,int m)
{
  double sum=0;
  for(int i=0; i<m;i++)
    for(int j=0; j<m;j++)
    {
      mtr[i*m+j]=calculateGaussianCoefficient(m,i,j);
      sum+=mtr[i*m+j];
    }
  if(sum<ONE_APROX_LOW || sum>ONE_APROX_HIGH)
  {
    double coef=1.0/sum;
    for(int i=0; i<m;i++)
      for(int j=0; j<m;j++)
      {
        mtr[i*m+j]=mtr[i*m+j]*coef;
      }
  }
}

cv::Mat applyGaussFilter(cv::Mat img, int m)
{
  double* mtr=new double[m*m];
  fillGaussianMatrix(mtr,m);
  cv::Mat res=applyMatrixToImage(mtr,m,m,img);
  std::cout<<"Finished applying Gauss smoothering size "<<m<<"\n";
  delete[] mtr;
  return res;
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

  std::cout << "Press any key to continue ...\n";
  std::cout<<"Creating window\n";
  cv::waitKey();                     // wait for key press


  std::cout<<"Creating window\n";
  cv::namedWindow("Filtered Image", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  std::cout<<"Creating new image\n";
  cv::Mat procImg_00=applyAVGFilter(img);
  std::cout<<"Showing new image\n";
  cv::imshow("Filtered Image", procImg_00);// show image

  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

  std::cout<<"Creating window\n";
  cv::namedWindow("Gauss smoothering size 3 Image", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  std::cout<<"Creating new image\n";
  cv::Mat procImg_01=applyGaussFilter(img,3);
  std::cout<<"Showing new image\n";
  cv::imshow("Gauss smoothering size 3 Image", procImg_01);// show image

  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press

  std::cout<<"Creating window\n";
  cv::namedWindow("Gauss smoothering size 5 Image", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  std::cout<<"Creating new image\n";
  cv::Mat procImg_02=applyGaussFilter(img,5);
  std::cout<<"Showing new image\n";
  cv::imshow("Gauss smoothering size 5 Image", procImg_02);// show image

  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press


  std::cout<<"Creating window\n";
  cv::namedWindow("Gauss smoothering size 7 Image", CV_WINDOW_AUTOSIZE || CV_WINDOW_KEEPRATIO);
  std::cout<<"Creating new image\n";
  cv::Mat procImg_03=applyGaussFilter(img,7);
  std::cout<<"Showing new image\n";
  cv::imshow("Gauss smoothering size 7 Image", procImg_03);// show image

  std::cout << "Press any key to continue ...\n";
  cv::waitKey();                     // wait for key press


  return 0;                                   // everything's gone fine ;)
}
