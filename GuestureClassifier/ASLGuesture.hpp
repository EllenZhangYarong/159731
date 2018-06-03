//
//  ASLGuesture.hpp
//  GuestureClassifier
//
//  Created by 张亚荣 on 2018/5/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef GuestureClassifier_ASLGuesture_hpp
#define GuestureClassifier_ASLGuesture_hpp

#include <cstdio>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ASLGuesture{
    
private:
    vector<string> files;
    
    Mat image;
public:
    ASLGuesture();
    vector<string> getFilesInDirectory(const string&);
    void loadData();
    char getClassIntLabel(string&);
    Mat readImage(string&);
    Vec2f findDescriptor(Mat);
    vector<Point> getContourLine(const Mat& matImg,
                        vector<Mat>& vmatObjList,
                        const int &iThresh,
                        const int &k);

    Mat makeFD(const Mat& matContour);
    Mat normFD(Mat& matFD, const int &n);
    vector<float> EllipticFourierDescriptors(vector<Point>&);


};
#endif /* ASLGuesture_hpp */
