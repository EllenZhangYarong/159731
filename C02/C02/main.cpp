//
//  main.cpp
//  C02
//
//  Created by 张亚荣 on 2018/2/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
//  Write a program using OpenCV that opens two images and shows them in the screen in
//  sequence (one at a time).
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    if(argc < 2 ){
        cout << "Need 1 argument, e.g. image.jpg" << endl;
        exit(0);  
    }
    
    cout << "Argc == " << argc << endl;
    namedWindow("Window1", 1);
    Mat image1 = imread(argv[1]);
    Mat image2 = imread(argv[2]);
    imshow("Window1", image1);
    waitKey();
    imshow("Window1",image2);
    
    waitKey(0);

    std::cout << "Hello, World!\n";
    return 0;
}
