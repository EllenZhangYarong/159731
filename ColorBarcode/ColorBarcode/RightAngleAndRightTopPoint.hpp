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

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class RightAngleAndRightTopPoint{
private:
    Point2f rightAngle;
    Point2f leftTopPoint;
    
public:
    RightAngleAndRightTopPoint();
    void findRightAngle(vector<Vec3f>);
};
#endif /* RightAngleAndRightTopPoint_hpp */
