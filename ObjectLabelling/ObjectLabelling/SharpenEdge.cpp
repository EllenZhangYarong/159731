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

SharpenEdge::SharpenEdge(Mat image, int *seKernel){
    this->image = image;
    this->seKernel = seKernel;
};


Mat SharpenEdge::doSharpenEdge(){
    
    Mat cImage;
    cImage = Mat(this->image.size(), CV_8UC1);
    
    for(int x = 0; x < this->image.rows; x++){
        for(int y = 0; y<this->image.cols; y++){
            if(x >= 1 && x < this->image.rows-1 && y >= 1 && y< this->image.cols-1){
                int sumPixels;
                sumPixels =cvRound(  this->image.at<uchar>(x-1, y-1) * this->seKernel[0]
                                   + this->image.at<uchar>(x,   y-1) * this->seKernel[1]
                                   + this->image.at<uchar>(x+1, y-1) * this->seKernel[2]
                                   + this->image.at<uchar>(x-1, y)   * this->seKernel[3]
                                   + this->image.at<uchar>(x,   y)   * this->seKernel[4]
                                   + this->image.at<uchar>(x+1, y)   * this->seKernel[5]
                                   + this->image.at<uchar>(x-1, y+1) * this->seKernel[6]
                                   + this->image.at<uchar>(x,   y+1) * this->seKernel[7]
                                   + this->image.at<uchar>(x+1, y+1) * this->seKernel[8]);
//                cout << "sumPixels = " <<sumPixels << endl;
                if(sumPixels<0){
                    sumPixels = 0;
                    
                }else if(sumPixels>255){
                    sumPixels = 255;
                }
                
                cImage.at<uchar>(x,y)= sumPixels;
                
            }
        }
    }
    return cImage;
};
