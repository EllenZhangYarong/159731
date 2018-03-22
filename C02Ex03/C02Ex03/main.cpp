//
//  main.cpp
//  C02Ex03
//
//  Created by 张亚荣 on 2018/2/28.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
// 3. Modify the program to copy the image to a grey-scale image.
//    Save the grey-scale image with a dierent format than the original one.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if(argc <1 ){
        exit(0);
    }
    namedWindow("Original Image");
    namedWindow("Grey Image");
    
    Mat image , imageGrey ;
    image = imread(argv[1]);
    
    cvtColor(image,imageGrey,CV_BGR2GRAY);
    
    imwrite("gray.tiff", imageGrey);
    
    imshow("Color", image);
    imshow("Gray", imageGrey);
    
    waitKey(0);
    
    std::cout << "Hello, World!\n";
    return 0;
}
