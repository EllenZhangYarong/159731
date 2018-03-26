//
//  SharpenEdge.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ObjectLabelling_SharpenEdge_hpp
#define ObjectLabelling_SharpenEdge_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class SharpenEdge{
private:
    Mat mask, image;
    
public:
    SharpenEdge(Mat mask, Mat image);
    Mat doSharpenEdge();
    
};
#endif /* SharpenEdge_hpp */
