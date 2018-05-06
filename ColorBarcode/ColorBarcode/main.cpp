//
//  main.cpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/6.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include "ReadImagesFromDir.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
static double distanceBtwPoints(const cv::Point a, const cv::Point b)
{
    double xDiff = a.x - b.x;
    double yDiff = a.y - b.y;
    
    return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

int main(int argc, const char * argv[]) {
    
    Mat src, src_gray, copyofsrc;
    
    Point2f originalPoint(90,90);
    Point2f locatedPoint;
    Point2f centerOfImage;
    
    ReadImagesFromDir rifd(argv[1]);
    vector<Mat> images = rifd.doReadImages();
    
        cout<<"images.size = "<<images.size()<<endl;
    
    for(auto src : images ){
        //    src = imread(argv[11]);
        cout<<"Source size ---> "<<src.size()<<endl;
        src.copyTo(copyofsrc);
        
        centerOfImage = Point2f( copyofsrc.cols/2, copyofsrc.rows/2 );
        
        cout<<"Resized image size -----> "<< copyofsrc.size()<<endl;
        cout<<"Resized image center ---> "<< centerOfImage <<endl;

//        Mat tempimg;
//        copyofsrc.copyTo(tempimg);
        cvtColor(src, src_gray, CV_BGR2GRAY);
        
        //    x=89.2946 y=89.2926
        //    x=89.29 y=909.756
        //    x=909.756 y=909.759
        
        //Find the three circles
        medianBlur(src_gray, src_gray, 3);
        
        //    namedWindow("src_gray");
        //    imshow("src_gray", src_gray);
        //    waitKey(0);
        
        vector<Vec3f> circles, circles2;
        HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 2, src_gray.rows/16, 1000, 100, 40, 60 );
        cout << circles.size() << endl;
//        array<Point, 3> points;
        array<double, 3> disbtwpoints;
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            //            cout << radius << endl;
            cout << center << endl;
            // Looking for the nearest point from original point
            disbtwpoints[i] = distanceBtwPoints(originalPoint, center);
            
            putText(copyofsrc,to_string(i),cvPoint(center.x, center.y),FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0,0,255),2,CV_AA);
            // circle center
            circle( copyofsrc, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( copyofsrc, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
        
        //Looing for the nearest point from original points
        if( disbtwpoints[0] <= disbtwpoints[1] && disbtwpoints[0] <= disbtwpoints[2]){
            locatedPoint.x = circles[0][0];
            locatedPoint.y = circles[0][1];
        }else if(disbtwpoints[1] < disbtwpoints[0] && disbtwpoints[1] < disbtwpoints[2]){
            locatedPoint.x = circles[1][0];
            locatedPoint.y = circles[1][1];
        }else{
            locatedPoint.x = circles[2][0];
            locatedPoint.y = circles[2][1];
        }
        
//        rectangle(copyofsrc, Point(cvRound(circles[0][0]), cvRound(circles[0][1])), Point(cvRound(circles[1][0]), cvRound(circles[1][1])), cvScalar(255,0,0),8,8,0);
        
        putText(copyofsrc,"n",cvPoint(locatedPoint.x-10, locatedPoint.y+10),FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(255,0,0),2,CV_AA);
        line(copyofsrc, originalPoint, centerOfImage, cvScalar(0,255,0), 4);
        line(copyofsrc, locatedPoint,  centerOfImage, cvScalar(0,255,0), 4);
        /// Show your results
        namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
        imshow( "Hough Circle Transform Demo", copyofsrc );
        waitKey(0);
        
        //Looking for the angle between the original points and center of the image
        double dx1 = centerOfImage.x - originalPoint.x;
        double dy1 = centerOfImage.y - originalPoint.y;
        double dx2 = centerOfImage.x - locatedPoint.x;
        double dy2 = centerOfImage.y - locatedPoint.y;
        
        double anglebtwol =  (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
        cout<<"Angle between three points:  ---> "<<anglebtwol<<endl;
        
        double rotatedAngle;
        if(anglebtwol>=0.95 && anglebtwol<=1){
            rotatedAngle = 0;
        }else{
            rotatedAngle = anglebtwol;
        }
        
        
        Mat rotateM, rotatedImage;
        rotateM = getRotationMatrix2D(centerOfImage, rotatedAngle * 64, 1);
        warpAffine(copyofsrc, rotatedImage, rotateM, copyofsrc.size());
        
        namedWindow( "Rotated Image", CV_WINDOW_AUTOSIZE );
        imshow( "Rotated Image", rotatedImage );
        waitKey(0);
        
    }
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
