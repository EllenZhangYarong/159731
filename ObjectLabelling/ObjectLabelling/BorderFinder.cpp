//
//  BorderFinder.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/21.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "BorderFinder.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

BorderFinder::BorderFinder(Mat image, vector<vector<Point>> setsBlobs){
    cvtColor(image, image, CV_RGB2BGRA);
    this->image = image;
    this->setsBlobs = setsBlobs;
    this->borderMat = Mat(image.size(), CV_32SC1, cvScalar(-1));
};


vector<vector<Point>> BorderFinder::findingBorders(){
    int top , bottom, left, right ;
    vector<vector<Point>> setsOfBorder;
    for(auto points : this->setsBlobs)
        cout<<"before --> points = "<<points.size()<<endl;
    
    
    for(int i = 0 ; i < this->setsBlobs.size(); i++){
        
        vector<Point> bordersPixel;

        vector<Point> points = this->setsBlobs.at(i);
        for(int j = 0 ; j< points.size(); j++){

            top = int(image.at<uchar>(points.at(j).x,points.at(j).y-1));
            bottom =int( image.at<uchar>(points.at(j).x,points.at(j).y+1));
            left = int(image.at<uchar>(points.at(j).x-1,points.at(j).y));
            right = int(image.at<uchar>(points.at(j).x+1,points.at(j).y));
            
            cout<<" top= "<<top<<" bottom= "<<bottom<<" left = "<<left<<" right ="<<right<<endl;
            if( (top != 0 && bottom != 0 && right != 0 && left != 0) ||
               (top == bottom==right==left == 0)){
                
                cout<<"coming ~~ ";
                points.erase(points.begin()+j);
            }else{
                
                bordersPixel.push_back(points[j]);
                
            }
        }
        setsOfBorder.push_back(bordersPixel);
    }
    for(auto points : setsOfBorder)
        cout<<"before --> points = "<< points.size()<< endl << endl;
    
    return setsOfBorder;
};
