//
//  main.cpp
//  C02Ex04
//
// Write a program that loads a colour image. Using a trackbar,
// the user should be able to change the image to grey-scale and
// back to colour (the trackbar should allow for values 0 and 1).
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//#define Mpixel(image, x, y) ((uchar *)(image.data + y * image.step))[(x)]

Mat image1;

void callback_trackbar(int value, void * object){
    Mat image2;
    image2.create(image1.size(), CV_8SC1 );
    if(value==0){
        
        cvtColor(image1,image2, CV_BGR2GRAY);

    }else{
        cvtColor(image1, image2, CV_8SC1 );
    }

    imshow("Show Results", image2);
}

int main(int argc, const char * argv[]) {
    
    image1 = imread(argv[1]);
    int markerclick =0;
    namedWindow("Show Results",WINDOW_AUTOSIZE);
    createTrackbar("Switch", "Show Results", &markerclick, 1, callback_trackbar);
    setTrackbarPos("Switch", "Show Results", 10);
    imshow("Show Results", image1);
    waitKey(0);
    
    std::cout << "Hello, World!\n";
    return 0;
}
