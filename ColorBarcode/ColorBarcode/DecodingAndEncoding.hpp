//
//  DecodingAndEncoding.hpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/7.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef ColorBarcode_DecodingAndEncoding_hpp
#define ColorBarcode_DecodingAndEncoding_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class DecodingAndEncoding{
private:
    Mat image;
    string message;
    Mat pic;
    array<char, 64> encodingarray;
    
public:
    DecodingAndEncoding(Mat);
    DecodingAndEncoding(Mat, string, Mat);
    string decodingQR();
    void encodingQR(string);
};
#endif /* DecodingAndEncoding_hpp */
