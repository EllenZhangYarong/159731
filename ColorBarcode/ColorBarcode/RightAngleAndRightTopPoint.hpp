//
//  RightAngleAndRightTopPoint.hpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/6.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
//  Looking for the right angle in the hough circles
//

#ifndef ColorBarcode_RightAngleAndRightTopPoint_hpp
#define ColorBarcode_RightAngleAndRightTopPoint_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class RightAngleAndRightTopPoint{
private:
    Point2f rightAnglePoint;
    Point2f otherPoint1, otherPoint2, missingPoint;
    
public:
    RightAngleAndRightTopPoint();
    void findRightAngle(vector<Vec3f>);
    void computeTheMissingPoint();
    Point2f getMissingPoint();
    Point2f getRightAnglePoint();
    
    Point2f getOtherPoint1();
    Point2f getOtherPoint2();
};

template <typename T> class Vector2D
{
private:
    T x;
    T y;
    
public:
    explicit Vector2D(const T& x=0, const T& y=0) : x(x), y(y) {}
    Vector2D(const Vector2D<T>& src) : x(src.x), y(src.y) {}
    virtual ~Vector2D() {}
    
    // Accessors
    inline T X() const { return x; }
    inline T Y() const { return y; }
    inline T X(const T& x) { this->x = x; }
    inline T Y(const T& y) { this->y = y; }
    
    // Vector arithmetic
    inline Vector2D<T> operator-() const
    { return Vector2D<T>(-x, -y); }
    
    inline Vector2D<T> operator+() const
    { return Vector2D<T>(+x, +y); }
    
    inline Vector2D<T> operator+(const Vector2D<T>& v) const
    { return Vector2D<T>(x+v.x, y+v.y); }
    
    inline Vector2D<T> operator-(const Vector2D<T>& v) const
    { return Vector2D<T>(x-v.x, y-v.y); }
    
    inline Vector2D<T> operator*(const T& s) const
    { return Vector2D<T>(x*s, y*s); }
    
    // Dot product
    inline T operator*(const Vector2D<T>& v) const
    { return x*v.x + y*v.y; }
    
    // l-2 norm
    inline T norm() const { return sqrt(x*x + y*y); }
    
    // inner angle (radians)
    static T angle(const Vector2D<T>& v1, const Vector2D<T>& v2)
    {
        return acos( (v1 * v2) / (v1.norm() * v2.norm()) );
    }
};

#endif /* RightAngleAndRightTopPoint_hpp */
