//
//  main.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/18.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "BlobDetector.hpp"
#include "ColorBlobs.hpp"
#include "BorderFinder.hpp"
#include "SimpleMedianFilter.hpp"
#include "BinariseThreshold.hpp"
#include "ReadImagesFromDir.hpp"
#include "SharpenEdge.hpp"



using namespace std;
using namespace cv;
using namespace chrono;

string type2str(int type);

Mat frame;//, image;

int main(int argc, const char * argv[]) {

    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened())
    {
        cout << "Failed to open camera" << endl;
        return 0;
    }
    cout << "Opened camera" << endl;
    namedWindow("WebCam", 1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    //   cap.set(CV_CAP_PROP_FRAME_WIDTH, 960);
    //   cap.set(CV_CAP_PROP_FRAME_WIDTH, 1600);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    //   cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
    //   cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1200);
    cap >> frame;
    printf("frame size %d %d \n",frame.rows, frame.cols);
    int key=0;
    
    double fps=0.0;
    while (1){
        system_clock::time_point start = system_clock::now();
        //for(int a=0;a<10;a++){
        cap >> frame;
        if( frame.empty() )
            break;
        
        char printit[100];
        sprintf(printit,"%2.1f",fps);
        
        cvtColor(frame, frame, CV_BGR2GRAY);
        
        //Code here
        BinariseThreshold bt(frame);
        Mat btimage = bt.doBinariseImage();
        
        BlobDetector blobDetector(btimage);
        blobDetector.findingBlobs();
        
        int blobs = blobDetector.getNumberOfBlobs();
        cout << "Final blobs ---> " << blobs << endl;
        
        //sb: sets of blobs without empty vectors, just blobs
        vector<vector<Point>> sb = blobDetector.getFullBlobs();
        
        
//
        putText(frame, to_string(blobs) , cvPoint(40,40),
                FONT_HERSHEY_COMPLEX_SMALL, 2.0, cvScalar(0,255,255), 2, CV_AA);
//
//        namedWindow("fillcolor", 0);
//        imshow("fillcolor", filled);
//        waitKey(0);
        
        putText(frame, printit, cvPoint(10,30), FONT_HERSHEY_PLAIN, 2, cvScalar(255,255,255), 2, 8);
        imshow("WebCam", frame);
        key=waitKey(1);
        if(key==113 || key==27) return 0;//either esc or 'q'
        
        //}
        system_clock::time_point end = system_clock::now();
        double seconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        //fps = 1000000*10.0/seconds;
        fps = 1000000/seconds;
        cout << "frames " << fps << " seconds " << seconds << endl;
    }
/*
     For test a batch of images
    
    
    ReadImagesFromDir rifd(argv[1]);
    vector<Mat> images = rifd.doReadImages();

//    cout<<"images.size = "<<images.size()<<endl;

    for(auto image : images ){

        SimpleMedianFilter smf(image);
        Mat filteredImage = smf.doMedianFiter(3, 3);

        BinariseThreshold bt(filteredImage);
        Mat btimage = bt.doBinariseImage();

        BlobDetector blobDetector(btimage);
        blobDetector.findingBlobs();

        int blobs = blobDetector.getNumberOfBlobs();
        cout << "Final blobs ---> " << blobs << endl;

        //sb: sets of blobs without empty vectors, just blobs
        vector<vector<Point>> sb = blobDetector.getFullBlobs();

        ColorBlobs colorBlobs(image, sb);
        Mat filled = colorBlobs.fillBlobs();
        
        putText(filled, to_string(blobs) , cvPoint(40,40),
                FONT_HERSHEY_COMPLEX_SMALL, 2.0, cvScalar(0,255,255), 2, CV_AA);
        
        namedWindow("fillcolor", 0);
        imshow("fillcolor", filled);
        waitKey(0);
    }
*/
    
/*
     For test one single image
    
    Mat src = imread(argv[3], 0);
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

    int seKernel[]={0,-1,0,-1,5,-1,0,-1,0};
    SharpenEdge se(filteredImage, seKernel);
    Mat seImage = se.doSharpenEdge();
    
    string ty3 =  type2str( seImage.type() );
    printf(" sharpen edge Image Matrix: %s %dx%d \n", ty3.c_str(), seImage.cols, seImage.rows );
    
    namedWindow("seImage", 0);
    imshow("seImage", seImage);
    waitKey(0);
    
    BinariseThreshold bt(seImage);
    Mat btimage = bt.doBinariseImage();

    BlobDetector blobDetector(btimage);
    blobDetector.findingBlobs();

    int blobs = blobDetector.getNumberOfBlobs();
    cout << "Final blobs ---> " << blobs << endl;

    //sb: sets of blobs without empty vectors, just blobs
    vector<vector<Point>> sb = blobDetector.getFullBlobs();

    ColorBlobs colorBlobs(src, sb);

    Mat filled = colorBlobs.fillBlobs();

    putText(filled, to_string(blobs) , cvPoint(30,30),
            FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    
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
 */
    
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

