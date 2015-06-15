#ifndef GEOMETRY
#define GEOMETRY

// opencv includes
#include <opencv2/opencv.hpp>

#include "./helpers.h"

typedef cv::Vec< double, 2 >                      Point2DType;
typedef cv::Vec< double, 3 >                      Point3DType;
typedef cv::Vec< double, 4 >                      Point4DType;

typedef std::vector< Point2DType >                Point2DListType;
typedef std::vector< Point3DType >                Point3DListType;
typedef std::vector< Point4DType >                Point4DListType;

typedef std::pair< size_t, size_t >               EdgeType;
typedef std::vector< EdgeType >                   EdgeListType;

typedef std::pair<Point2DListType, EdgeListType > Object2DType;
typedef std::pair<Point3DListType, EdgeListType > Object3DType;
typedef std::pair<Point4DListType, EdgeListType > Object4DType;

typedef std::vector< Object2DType >               Object2DListType;
typedef std::vector< Object3DType >               Object3DListType;
typedef std::vector< Object4DType >               Object4DListType;

void create3DObject(Object3DListType &objects) {  
  Point3DListType _points;
  _points.push_back(Point3DType(-10,  10,  10)); // 0
  _points.push_back(Point3DType(-10, -10,  10)); // 1
  _points.push_back(Point3DType(  0, -20,  0));  // 2
  _points.push_back(Point3DType( 10, -10,  10)); // 3
  _points.push_back(Point3DType( 10,  10,  10)); // 4
  _points.push_back(Point3DType(-10,  10, -10)); // 5
  _points.push_back(Point3DType(-10, -10, -10)); // 6
  _points.push_back(Point3DType( 10, -10, -10)); // 7
  _points.push_back(Point3DType( 10,  10, -10)); // 8
  
  EdgeListType _edges;
  _edges.push_back(EdgeType(0, 1));  // front
  _edges.push_back(EdgeType(1, 2));
  _edges.push_back(EdgeType(2, 3));
  _edges.push_back(EdgeType(3, 4));
  _edges.push_back(EdgeType(4, 0));
  _edges.push_back(EdgeType(0, 3));
  _edges.push_back(EdgeType(3, 1));
  _edges.push_back(EdgeType(1, 4));
  
  _edges.push_back(EdgeType(4, 3));  // right
  _edges.push_back(EdgeType(3, 2));
  _edges.push_back(EdgeType(2, 7));
  _edges.push_back(EdgeType(7, 8));
  _edges.push_back(EdgeType(8, 3));
  _edges.push_back(EdgeType(3, 7));
  _edges.push_back(EdgeType(7, 4));
  _edges.push_back(EdgeType(4, 8));
  
  _edges.push_back(EdgeType(8, 7));  // back
  _edges.push_back(EdgeType(7, 2));
  _edges.push_back(EdgeType(2, 6));
  _edges.push_back(EdgeType(6, 5));
  _edges.push_back(EdgeType(5, 8));
  _edges.push_back(EdgeType(8, 6));
  _edges.push_back(EdgeType(6, 7));
  _edges.push_back(EdgeType(7, 5));
  
  _edges.push_back(EdgeType(5, 6));  // left
  _edges.push_back(EdgeType(6, 2));
  _edges.push_back(EdgeType(2, 1));
  _edges.push_back(EdgeType(1, 0));
  _edges.push_back(EdgeType(0, 6));
  _edges.push_back(EdgeType(6, 1));
  _edges.push_back(EdgeType(1, 5));
  _edges.push_back(EdgeType(5, 0));
  
  objects.push_back(Object3DType(_points, _edges));
}

Object2DType project2D(const Object3DType &object3D) {
  cv::Matx33d m(1, 0, 0, 
                0, 1, 0,
                0, 0, 1);
  
  Point3DListType _points3D = Point3DListType(object3D.first);
  Point2DListType _points2D;
  
  for (Point3DListType::iterator itPoints = _points3D.begin(); 
       itPoints != _points3D.end(); 
       ++itPoints) {
    cv::Matx<double, 3, 1> tmp = m * (*itPoints);
    _points2D.push_back(Point2DType(tmp(0), tmp(1)));
  }
  
  return Object2DType(_points2D, object3D.second);
}

Object2DListType project2D(const Object3DListType &objects3D) {
  Object2DListType result;
  for (Object3DListType::const_iterator it = objects3D.begin();
       it != objects3D.end();
       ++it) {
    result.push_back(project2D(*it));
  }
  
  return result;
}


#endif