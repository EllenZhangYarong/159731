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
#include "LabelBlobs.hpp"
#include "BorderFinder.hpp"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    Mat src = imread(argv[1], 0);
    Mat image;
    int thresh = 1;
    
    if( src.empty() )
    {
        cout << "Image not found! \n";
        return 0;
    }
//    Size size(400,330);
//    Size size(50,42);
    
//    resize(src, image, size);
//
//    cout << src.size() << endl;
//    cout << image.size() << endl;

//        namedWindow("src");
//        imshow("src", src);
//        waitKey(0);
//
//        namedWindow("resized");
//        imshow("resized", image);
//        waitKey(0);

//    cout<<image<<endl;

    threshold(src, image, 0, 255, THRESH_BINARY|THRESH_OTSU);
    
    BlobDetector blobDetector(image);
    blobDetector.findingBlobs();

    int blobs = blobDetector.getNumberOfBlobs();
    cout << "Final blobs ---> " << blobs << endl;

    //sb: sets of blobs without empty vectors, just blobs
    vector<vector<Point>> sb = blobDetector.getFullBlobs();
    
    ColorBlobs colorBlobs(image, sb);
    
    Mat filled = colorBlobs.fillBlobs();

//    namedWindow("fillcolor", 0);
//    imshow("fillcolor", filled);
//    waitKey(0);
    
    Rect myRoi(300,250,180,210);
    image = filled(myRoi);
    
//    namedWindow("Crop For Test", 0);
//    imshow("Crop For Test", image);
//    waitKey(0);
    
    BorderFinder borderFinder(filled, sb);
    sb = borderFinder.findingBorders();
    
    ColorBlobs colorBlobsFrame(src, sb);
    Mat framed = colorBlobsFrame.fillBlobs();
    
//    cvtColor(filled, filled, CV_BGR2GRAY);
//    Mat framed;
//    threshold(filled, framed, thresh, 255, CV_THRESH_BINARY);
//
//    framed = colorBlobs.frameBlobs(framed);
//
    namedWindow("framed", 0);
    imshow("framed", framed);
    waitKey(0);
    
    return 0;
}
