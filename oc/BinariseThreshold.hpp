//
//  BinariseThreshold.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ObjectLabelling_BinariseThreshold_hpp
#define ObjectLabelling_BinariseThreshold_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class BinariseThreshold{
private:
    Mat image;
    
public:
    BinariseThreshold(Mat image);
    Mat doBinariseImage();
};

#endif /* BinariseThreshold_hpp */
