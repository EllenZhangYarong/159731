//
//  SimpleMedianFilter.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/23.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ObjectLabelling_MedianFilter_hpp
#define ObjectLabelling_MedianFilter_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class SimpleMedianFilter{
private:
    Mat image;
    
public:
    SimpleMedianFilter(Mat image);
    Mat doMedianFiter(int kWidth, int KHeight);
};
#endif /* MedianFilter_hpp */
