//
//  SharpenEdge.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "SharpenEdge.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

SharpenEdge::SharpenEdge(Mat mask, Mat image){
    this->mask = mask;
    this->image = image;
};
Mat SharpenEdge::doSharpenEdge(){
    
    return this->image;
};
