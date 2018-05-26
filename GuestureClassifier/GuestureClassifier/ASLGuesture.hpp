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
    vector<Mat> X;
    vector<int> y;
public:
    ASLGuesture();
    vector<string> getFilesInDirectory(const string& directory);
    vector<Mat,int> loadData();
    inline string getClassName(const string& filename);

};
#endif /* ASLGuesture_hpp */
