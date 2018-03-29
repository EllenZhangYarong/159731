//
//  MedianFilter.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/23.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "SimpleMedianFilter.hpp"

#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

SimpleMedianFilter::SimpleMedianFilter(Mat image){
    this->image = image;
//    cout << "image enter --> \n" << this->image << endl;
};

Mat SimpleMedianFilter::doMedianFiter(int kWidth, int kHeight){
    Mat outImage( this->image.rows - 2, this->image.cols - 2, CV_8UC1);
    vector<uint> kWin(kWidth * kHeight);
    cout<<"image.cols = "<<this->image.cols<<"image.rows = "<< this->image.rows<<endl;
    cout<< "outImage.cols = " << outImage.cols << "outImage.rows = " << outImage.rows << endl;
    
    int edgeX = kWidth / 2 ;
    int edgeY = kHeight / 2 ;
    
    cout<< "(edgeX,edgeY) = (" << edgeX << "," << edgeY << ")" << endl;
    
    for(int x = edgeX; x < this->image.rows; x++){
        for(int y = edgeY; y < this->image.cols; y++){
            int i = 0 ;
            for(int kX = 0 ; kX < kWidth; kX++){
                for(int kY = 0 ; kY < kHeight; kY++){
                    kWin.at(i)= uint(this->image.at<uchar>(x + kX - edgeX, y + kY - edgeY)) ;
//                    cout<<"i = "<<i<<endl;
                    i ++;
                }
            }
            
            auto first = kWin.begin();
            auto last  = kWin.end();
            auto middle = first + ( last - first)/2;
            
            nth_element(first, middle, last);

//            cout << "Middle value is -> "<< *middle << endl;
            outImage.at<uchar>(x-1,y-1) = *middle;
            
//            kernel.clear();
            kWin.begin();
        }
    }
    
    return outImage;
};
