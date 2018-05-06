//
//  BorderFinder.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/21.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ObjectLabelling_BorderFinder_hpp
#define ObjectLabelling_BorderFinder_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class BorderFinder{
private:
    Mat image;
    Mat borderMat;
    vector<vector<Point>> setsBlobs;
    
public:
    BorderFinder(Mat image, vector<vector<Point>> setsBlobs);
    vector<vector<Point>> findingBorders();
};
#endif /* BorderFinder_hpp */
