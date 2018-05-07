//
//  main.cpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/6.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include "ReadImagesFromDir.hpp"
#include "RightAngleAndRightTopPoint.hpp"


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
    Point2f centerOfImage;
    
    ReadImagesFromDir rifd(argv[1]);
    vector<Mat> images = rifd.doReadImages();
    
        cout<<"images.size = "<<images.size()<<endl;
    
    for(auto src : images ){

        cout<<"Source size ---> "<<src.size()<<endl;
        src.copyTo(copyofsrc);
        
        centerOfImage = Point2f( copyofsrc.cols/2, copyofsrc.rows/2 );

        cvtColor(src, src_gray, CV_BGR2GRAY);
        
        //    x=89.2946 y=89.2926
        //    x=89.29 y=909.756
        //    x=909.756 y=909.759
        
        //Find the three circles
        medianBlur(src_gray, src_gray, 3);
        
        vector<Vec3f> circles;
        HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 2, src_gray.rows/16, 1000, 100, 40, 60 );
        cout << circles.size() << endl;

        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            //            cout << radius << endl;
            cout << center << endl;
        
            putText(copyofsrc,to_string(i),cvPoint(center.x, center.y),FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0,0,255),2,CV_AA);
            // circle center
            circle( copyofsrc, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( copyofsrc, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
        
        RightAngleAndRightTopPoint raart;
        raart.findRightAngle(circles);
        raart.computeTheMissingPoint();
        Point2f missingPoint,rightAnglePoint, otherPoint1, otherPoint2;
        missingPoint = raart.getMissingPoint();
        rightAnglePoint = raart.getRightAnglePoint();
        otherPoint1 = raart.getOtherPoint1();
        otherPoint2 = raart.getOtherPoint2();
        
        
        circle( copyofsrc, missingPoint, 20, Scalar(0,0,255), 3, 8, 0 );
        circle( copyofsrc, rightAnglePoint, 20, Scalar(255,0,255), 3, 8, 0 );

        putText(copyofsrc,"n",cvPoint(rightAnglePoint.x-10, rightAnglePoint.y+10),FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(255,0,0),2,CV_AA);
        
        line(copyofsrc, originalPoint, centerOfImage, cvScalar(0,255,0), 4);
        line(copyofsrc, rightAnglePoint,  centerOfImage, cvScalar(0,255,0), 4);
        
        /// Show your results
        namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
        imshow( "Hough Circle Transform Demo", copyofsrc );
        waitKey(0);
        
        vector<Point2f> desPoints, orgPoints;
        desPoints.push_back(Point2f(90,90));
        desPoints.push_back(Point2f(90,910));
        desPoints.push_back(Point2f(910,910));
        desPoints.push_back(Point2f(910, 90));
        orgPoints.push_back(otherPoint1);
        orgPoints.push_back(rightAnglePoint);
        orgPoints.push_back(otherPoint2);
        orgPoints.push_back(missingPoint);
        
        Mat M = getPerspectiveTransform(orgPoints, desPoints);
        warpPerspective(src,src,M,Size(1000,1000));
        
        namedWindow( "warpPerspective", CV_WINDOW_AUTOSIZE );
        imshow( "warpPerspective", src );
        waitKey(0);
        
        
    }
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
