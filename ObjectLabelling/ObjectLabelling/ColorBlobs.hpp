//
//  ColorBlobs.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/18.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ObjectLabelling_ColorBlobs_hpp
#define ObjectLabelling_ColorBlobs_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class ColorBlobs{
private:
    Mat image;
    vector<vector<Point>> setsOfBlobs;
    
public:
    ColorBlobs(Mat &image, vector<vector<Point>> setsOfBlobs);
    Mat fillBlobs();
};
#endif /* ColorBlobs_hpp */
