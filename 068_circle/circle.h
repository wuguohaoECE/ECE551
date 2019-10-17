#include <cmath>
#include "point.h"
#define pi acos(-1)


class Circle{
 private:
  Point center;
  const double radius;
 public:
 Circle(Point p, double r) : center(p), radius(r){};
  void move (double dx, double dy){
    center.move(dx, dy);
  }
  double intersectionArea(const Circle & otherCircle){
    double d = center.distanceFrom(otherCircle.center);
    double r1 = otherCircle.radius;
    double r2 = radius;
    if(d >= r1 + r2){
      return 0;
    }
    if(r1 > r2){
      double tmp = r1;
      r1 = r2;
      r2 = tmp;
    }
    if(r2 - r1 >= d){
      return pi * pow(r1, 2);
    }
    double ang1=acos((r1*r1+d*d-r2*r2)/(2*r1*d));
    double ang2=acos((r2*r2+d*d-r1*r1)/(2*r2*d));
    return ang1*r1*r1 + ang2*r2*r2 - r1*d*sin(ang1);
  }
};
