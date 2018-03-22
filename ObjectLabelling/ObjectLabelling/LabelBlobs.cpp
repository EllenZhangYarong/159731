//
//  LabelBlobs.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/19.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "LabelBlobs.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

LabelBlobs::LabelBlobs(Mat &image, vector<vector<Point>> setsBlobs){
    this->setsBlobs = setsBlobs;
    this->image = image;
};

Mat LabelBlobs::textOnBlobs(){
   
    return this->image;
};

Mat LabelBlobs::getImageFrame(){
    
    return this->imageFrame;
};

