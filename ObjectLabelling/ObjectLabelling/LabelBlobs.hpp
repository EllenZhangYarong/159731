//
//  LabelBlobs.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/19.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ObjectLabelling_LabelBlobs_hpp
#define ObjectLabelling_LabelBlobs_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class LabelBlobs{
private:
    Mat image;
    vector<vector<Point>> setsBlobs; //sets of blobs
    vector<vector<Point>> setsOfRectangle;
    vector<Point> setsOfCentroid;
    Mat imageFrame;

public:
    LabelBlobs(Mat &image, vector<vector<Point>> setsFullBlobs);
    Mat textOnBlobs();
    Mat getImageFrame();

};
#endif /* LabelBlobs_hpp */
