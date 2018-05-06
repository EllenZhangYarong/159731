//
//  ReadImagesFromDir.hpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ColorBarcode_ReadImagesFromDir_hpp
#define ColorBarcode_ReadImagesFromDir_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class ReadImagesFromDir{
private:
    string path;
    vector<Mat> images;
public:
    ReadImagesFromDir(string path);
    vector<Mat> doReadImages();
};
#endif /* ReadImagesFromDir_hpp */
