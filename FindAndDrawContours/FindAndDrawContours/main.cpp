//
//  main.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/13.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat src; Mat src_gray;
int thresh = 250;
int max_thresh = 255;
RNG rng(12345);

void processImage(int, void*);
int main( int argc, char** argv )
{
    
    src = imread(argv[1], 0);
    if( src.empty() )
    {
        cout << "Couldn't open image \n";
        return 0;
    }
    
    blur( src, src, Size(3,3) );
    
    /// Create Window
    namedWindow( "Source", CV_WINDOW_AUTOSIZE );
    imshow( "Source", src );
    
    createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, processImage);
    
    processImage(0, 0);
    // Wait for a key stroke; the same function arranges events processing
    waitKey();
    return 0;
}
// Define trackbar callback functon. This function find contours,
// draw it and approximate it by ellipses.
void processImage(int /*h*/, void*)
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    Canny( src, canny_output, thresh, thresh*2, 3 );
    findContours(src, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE, Point(0, 0));
    
//    for(auto x : contours){
//        for(auto y : x)
//            cout<< y <<"  ";
//        cout <<  endl;
//    }
    
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    
    for( int i = 0; i< contours.size(); i++ ){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours, i, color, 2, 8 , hierarchy, 1, Point());

    }
    
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    
}

