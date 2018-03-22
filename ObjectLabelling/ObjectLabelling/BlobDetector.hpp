//
//  BlobDetector.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/16.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
//  Blob Detector: find blob
//

#ifndef ObjectLabelling_BlobDetector_hpp
#define ObjectLabelling_BlobDetector_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class BlobDetector{
private:
    Mat image, imgMask;
    vector<vector<Point>> setsOfBlob; // blobs including empty vector
    vector<vector<Point>> setsOfFullBlobs; //only blobs
    
    vector<vector<Point>> getSetsOfBlob();

public:
    BlobDetector(Mat& image);
    void print(vector<vector<Point>> &setsOfBlob);
    void findingBlobs();
    int getNumberOfBlobs(); // get the numbers of the blobs
    vector<vector<Point>> getFullBlobs();
    Mat getImgMask();

};
#endif /* BlobDetector_hpp */
