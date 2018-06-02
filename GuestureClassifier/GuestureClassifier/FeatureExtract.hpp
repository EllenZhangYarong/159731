//
//  FeatureExtract.hpp
//  GuestureClassifier
//
//  Created by 张亚荣 on 2018/5/30.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef FeatureExtract_hpp
#define FeatureExtract_hpp

#include <stdio.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class FeatureExtract{
private:
    string datasetDir;
    
public:
    vector<float> EllipticFourierDescriptors(vector<Point>&);
    
};
#endif /* FeatureExtract_hpp */
