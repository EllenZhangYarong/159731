//
//  RightAngleAndRightTopPoint.cpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/6.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
//  Looking for the right angle in the hough circles
//

#include <iostream>
#include <stdio.h>

#include "RightAngleAndRightTopPoint.hpp"

using namespace std;

RightAngleAndRightTopPoint::RightAngleAndRightTopPoint(){
    this->rightAnglePoint = Point(0,0);
    this->otherPoint1     = Point(0,0);
    this->otherPoint2     = Point(0,0);
    this->missingPoint    = Point(0,0);
};

void RightAngleAndRightTopPoint::findRightAngle(vector<Vec3f> circles){
    Point2f rightAngelPoint;
    Point2f otherPoint1, otherPoint2;

    Vector2D<double> p1(circles[0][0], circles[0][1]);
    Vector2D<double> p2(circles[1][0], circles[1][1]);
    Vector2D<double> p3(circles[2][0], circles[2][1]);
    
    double angle1 = Vector2D<double>::angle(p2-p1, p3-p1);
    double angle2 = Vector2D<double>::angle(p1-p2, p3-p2);
    double angle3 = Vector2D<double>::angle(p1-p3, p2-p3);

//    cout<<"angle1 --> "<< angle1 << endl;
//    cout<<"angle2 --> "<< angle2 << endl;
//    cout<<"angle3 --> "<< angle3 << endl;
    
    if(angle1 > angle2 && angle1 > angle3 ){
//        cout<<"1--->"<<endl;
        
        rightAngelPoint.x = circles[0][0];
        rightAngelPoint.y = circles[0][1];
        this->rightAnglePoint = rightAngelPoint;
        otherPoint1.x = circles[2][0];
        otherPoint1.y = circles[2][1];
        otherPoint2.x = circles[1][0];
        otherPoint2.y = circles[1][1];
    }
    
    if(angle2 > angle1 && angle2 > angle3 ){
//        cout<<"2--->"<<endl;
        
        rightAngelPoint.x = circles[1][0];
        rightAngelPoint.y = circles[1][1];
        this->rightAnglePoint = rightAngelPoint;
        
        otherPoint1.x = circles[0][0];
        otherPoint1.y = circles[0][1];
        otherPoint2.x = circles[2][0];
        otherPoint2.y = circles[2][1];
    }
    
    if(angle3 > angle2 && angle3 > angle1 ){
//        cout<<"3--->"<<endl;
        rightAngelPoint.x = circles[2][0];
        rightAngelPoint.y = circles[2][1];
        this->rightAnglePoint = rightAngelPoint;
        otherPoint1.x = circles[0][0];
        otherPoint1.y = circles[0][1];
        otherPoint2.x = circles[1][0];
        otherPoint2.y = circles[1][1];
    }
    
    this->otherPoint1 = otherPoint1;
    this->otherPoint2 = otherPoint2;
//    cout<<"rightAngelPoint --->"<<rightAngelPoint<<endl;
//    cout<< "this->rightAngelPoint--->"<< this->rightAnglePoint<<endl;
//    cout<<"this->otherPoint1 ---> " << this->otherPoint1 << endl;
//    cout<<"this->otherPoint2 ---> " << this->otherPoint2 << endl;

};

void RightAngleAndRightTopPoint::computeTheMissingPoint(){

    Point2f missingPoint1, missingPoint2;
    Point2f dCenter, hDiag;
    dCenter.x = (this->otherPoint1.x + this->otherPoint2.x)/2;
    dCenter.y = (this->otherPoint1.y + this->otherPoint2.y)/2;
    hDiag.x   = (this->otherPoint1.x - this->otherPoint2.x)/2;
    hDiag.y   = (this->otherPoint1.y - this->otherPoint2.y)/2;

    missingPoint1.x = dCenter.x - hDiag.y ;
    missingPoint1.y = dCenter.y + hDiag.x ;
    missingPoint2.x = dCenter.x + hDiag.y ;
    missingPoint2.y = dCenter.y - hDiag.x ;
    
        if(abs( missingPoint1.x - this->rightAnglePoint.x ) < 300 && abs( missingPoint1.y - this->rightAnglePoint.y ) < 300){
            
            this->missingPoint = missingPoint2;
        }else{
            
            this->missingPoint = missingPoint1;
        }
    
//    cout<<"missingPoint1 : " << missingPoint1 << endl;
//    cout<<"missingPoint2 : " << missingPoint2 << endl;
//    cout<< "this-> missingPoint : "<< this->missingPoint << endl;
};
Point2f RightAngleAndRightTopPoint::getMissingPoint(){
    
    return this->missingPoint;
    
};
Point2f RightAngleAndRightTopPoint::getRightAnglePoint(){
    return this->rightAnglePoint;
};
Point2f RightAngleAndRightTopPoint::getOtherPoint1(){
    return this->otherPoint1;
};
Point2f RightAngleAndRightTopPoint::getOtherPoint2(){
    return this->otherPoint2;
};

