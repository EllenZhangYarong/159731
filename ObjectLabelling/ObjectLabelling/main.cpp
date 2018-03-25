//
//  main.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/18.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "BlobDetector.hpp"
#include "ColorBlobs.hpp"
#include "BorderFinder.hpp"
#include "SimpleMedianFilter.hpp"
#include "BinariseThreshold.hpp"

using namespace std;
using namespace cv;

string type2str(int type);

int main(int argc, const char * argv[]) {
    
    Mat src = imread(argv[1], 0);
    Mat image;
    
    if( src.empty() )
    {
        cout << "Image not found! \n";
        return 0;
    }
    string ty =  type2str( src.type() );
    printf(" Src Matrix: %s %dx%d \n", ty.c_str(), image.cols, image.rows );
    
    namedWindow("src");
    imshow("src", src);
    waitKey(0);

    SimpleMedianFilter smf(src);
    Mat filteredImage = smf.doMedianFiter(3, 3);
    
    namedWindow("filteredImage", 0);
    imshow("filteredImage", filteredImage);
    waitKey(0);
    
    string ty2 =  type2str( filteredImage.type() );
    printf(" filtered Image Matrix: %s %dx%d \n", ty2.c_str(), filteredImage.cols, filteredImage.rows );
    
    BinariseThreshold bt(filteredImage);
    Mat btimage = bt.doBinariseImage();
    
        namedWindow("btimage", 0);
        imshow("btimage", btimage);
        waitKey(0);
    
//    Rect myRoi(20,20,20,20);
//    btimage = src(myRoi);
//    cout<<btimage;
    
    BlobDetector blobDetector(btimage);
    blobDetector.findingBlobs();

    int blobs = blobDetector.getNumberOfBlobs();
    cout << "Final blobs ---> " << blobs << endl;

    //sb: sets of blobs without empty vectors, just blobs
    vector<vector<Point>> sb = blobDetector.getFullBlobs();

    ColorBlobs colorBlobs(src, sb);

    Mat filled = colorBlobs.fillBlobs();

    namedWindow("fillcolor", 0);
    imshow("fillcolor", filled);
    waitKey(0);
    
    
//    BorderFinder borderFinder(filled, sb);
//    sb = borderFinder.findingBorders();
//
//    ColorBlobs colorBlobsFrame(src, sb);
//    Mat framed = colorBlobsFrame.fillBlobs();
//
//    namedWindow("framed", 0);
//    imshow("framed", framed);
//    waitKey(0);
    
    //Test simple median filter
    
//    Rect myRoi(300,250,180,210);
//    image = src(myRoi);
//    
//        namedWindow("Crop For Test", 0);
//        imshow("Crop For Test", image);
//        waitKey(0);
    
//    cout << "Image enter into the smf -> \n" << image << endl;

    
    return 0;
}

string type2str(int type) {
    string r;
    
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);
    
    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }
    
    r += "C";
    r += (chans+'0');
    
    return r;
}

