//
//  BinariseThreshold.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "BinariseThreshold.hpp"

#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

BinariseThreshold::BinariseThreshold(Mat image){
    this->image = image;
};
Mat BinariseThreshold::doBinariseImage(){
    for(int x=0; x<this->image.rows; x++){
        for(int y=0; y<this->image.cols; y++){
            if(int(this->image.at<uchar>(x,y)) > 75){
                this->image.at<uchar>(x,y)= uchar(255);
            }else{
                this->image.at<uchar>(x,y)= 0;
            }
        }
    }
    
    return this->image;
};
