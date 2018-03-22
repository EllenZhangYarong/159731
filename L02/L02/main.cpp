//
//  main.cpp
//  L02
//
//  Created by 张亚荣 on 2018/2/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << argv[0] << "\n Hello, World!\n";
    
    namedWindow("yes", 0);
    
    Mat image = imread(argv[1]);

    if(image.data == NULL){
        cout << "No pictures found !"  << endl;
    }else{
        imshow("yes",image);
        waitKey();
    }
    
    return 0;
}


