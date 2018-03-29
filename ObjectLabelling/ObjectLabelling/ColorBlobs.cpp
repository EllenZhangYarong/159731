//
//  ColorBlobs.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/18.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "ColorBlobs.hpp"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;


RNG rng(012345);
//int thresh = 250;
//int max_thresh = 255;

ColorBlobs::ColorBlobs(Mat image, vector<vector<Point>> setsOfBlobs){
    this->image = image;
    this->setsOfBlobs = setsOfBlobs;
    
};

Mat ColorBlobs::fillBlobs(){
    
    Mat d , drawing;
    this->image.copyTo(d);
    d.convertTo(drawing, CV_8UC3);
//    cvtColor(drawing, drawing, CV_GRAY2RGB);
    
//    Mat drawing = Mat(this->image.rows, this->image.cols, CV_8UC3, Scalar(0,0,0));
    
//    cout<<"Before fill-->"<<endl;
//    cout<< drawing <<endl;
    
    for( auto blobs : this->setsOfBlobs ){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

        for( auto points : blobs){

//            cout<< points <<endl;
//            cout<< points.x<< " || " << points.y<<endl;
//            cout<< drawing.cols<< " || " << drawing.rows <<endl;

            assert(points.y <= drawing.cols && points.x <= drawing.rows);
            
            Range xr(points.x, points.x+1);
            Range yr(points.y,points.y+1);
            drawing(xr,yr) = color;
            
        }
                
    }
//    cout<<"After fill -->"<<endl;
//    cout<< drawing <<endl;
    
    this->image = drawing;
    return this->image;
};


