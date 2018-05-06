//
//  RightAngleAndRightTopPoint.cpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/6.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
//  Looking for the right angle in the hough circles
//

#include "RightAngleAndRightTopPoint.hpp"

RightAngleAndRightTopPoint::RightAngleAndRightTopPoint(){
    this->rightAngle = Point2f(0.0,0.0);
    this->leftTopPoint = Point2f(0.0,0.0);
};
void RightAngleAndRightTopPoint::findRightAngle(vector<Vec3f> circles){
    Point2d rightAngelPoint;
    double angel;
    
    double dx1 = circles[0][0] - circles[1][0];
    double dy1 = circles[0][1] - circles[1][1];
    double dx2 = circles[0][0] - circles[2][0];
    double dy2 = circles[0][1] - circles[2][1];
    
    angel =  (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
    cout<<"0--->"<< angel <<endl;
    if( angel< M_PI/4+0.1 && angel> M_PI/4-0.1){
        rightAngelPoint.x = circles[0][0];
        rightAngelPoint.y = circles[0][1];
        this->rightAngle = rightAngelPoint;
        
        if(circles[1][0] > circles[0][0] || circles[1][1] < circles[0][1]){
            
        }
    }else{
        double dx1 = circles[1][0] - circles[2][0];
        double dy1 = circles[1][1] - circles[2][1];
        double dx2 = circles[1][0] - circles[0][0];
        double dy2 = circles[1][1] - circles[0][1];
        
        angel =  (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
        cout<<"1--->"<<angel<<endl;
        if(angel < M_PI/4+0.1 && angel > M_PI/4-0.1){
            rightAngelPoint.x = circles[1][0];
            rightAngelPoint.y = circles[1][1];
            this->rightAngle = rightAngelPoint;
        }else{
            cout<<"2--->"<<endl;
            rightAngelPoint.x = circles[2][0];
            rightAngelPoint.y = circles[2][1];
            this->rightAngle = rightAngelPoint;
        }
    }
    cout<<"rightAngelPoint --->"<<rightAngelPoint<<endl;
    cout<< "this->rightAngelPoint--->"<< this->rightAngle<<endl;
};
