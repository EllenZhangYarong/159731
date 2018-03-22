//
//  main.cpp
//  L03
//
//  Created by 张亚荣 on 2018/3/20.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>

#include "IntensityTransformations.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {

    Mat src = imread(argv[1], 0);

    if( src.empty() ){
        cout << "Image not found! \n";
        return 0;
    }
    cout << src.size << endl;
    
    
    IntensityTransformations it(src);
    Mat ni = it.negativeImage();
//
    
    namedWindow("src");
    imshow("src", src);
    waitKey(0);

    namedWindow("negative");
    imshow("negative", ni);
    waitKey(0);
    
    return 0;
}
