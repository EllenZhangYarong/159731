//
//  IntensityTransformations.cpp
//  L03
//
//  Created by 张亚荣 on 2018/3/20.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "IntensityTransformations.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

IntensityTransformations::IntensityTransformations(Mat image){
    this->image = image;
};

Mat IntensityTransformations::negativeImage(){
    
    Mat des = this->image.clone();
    
    cout << des.cols << endl;
    cout << des.rows << endl;
    for(int x = 0; x < des.cols; x++){
        for( int y = 0; y < des.rows; y++){
            des.at<uchar>(y,x) = 255 - des.at<uchar>(y,x);
        }
    }
    
    return des;
};

Mat IntensityTransformations::simpleThreshold(){
    
    return this->image;
};

Mat IntensityTransformations::otsusThreshold(){
    
    return this->image;
};
