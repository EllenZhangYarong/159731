//
//  main.cpp
//  C02Ex02
//
//  Created by 张亚荣 on 2018/2/28.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
//  2. Write a program to copy an image and mirror it. Show the original image and the mirrored
//     image simultaneously (open two windows).
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    if(argc < 1){
        exit(0);
    }
    
    Mat image = imread(argv[1]);
    Mat image_mirror = Mat(image.rows,image.cols,CV_8UC3);
    flip(image, image_mirror, 1);
    namedWindow("image");
    namedWindow("mirror image");
    imshow("image", image);
    imshow("mirror image", image_mirror);
    
    waitKey(0);
    
    std::cout << "Hello, World!\n";
    return 0;
}
