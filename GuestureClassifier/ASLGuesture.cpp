//
//  ASLGuesture.cpp
//  GuestureClassifier
//
//  Created by 张亚荣 on 2018/5/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
#include "ASLGuesture.hpp"

#include <cstdio>
#include <vector>
#include <iostream>
#include <dirent.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


RNG rng(12345);

vector<string> ASLGuesture::getFilesInDirectory(const string& directory){
    
    vector<Mat> images;
    
    DIR *dir;
    struct dirent *ent;
    
    if ((dir = opendir (directory.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if ( !strcmp( ent->d_name, "."  )) continue;
            if ( !strcmp( ent->d_name, ".." )) continue;
            
            if(strstr(ent->d_name,".png")){
                
                string imageaddress = directory + "/" + ent->d_name;
                this->files.push_back(imageaddress);
                
            }
        }

        closedir (dir);
        
    } else {
        /* could not open directory */
        perror ("could not open directory");
        exit(-1);
    }
        
    return this->files;
};

ASLGuesture::ASLGuesture(){
}

char ASLGuesture::getClassIntLabel(string& filename)
{
    char className[2];
//    cout<<"filename.substr(filename.find_last_of('/') + 7, 1).c_str()"<<filename.substr(filename.find_last_of('/') + 7, 1).c_str()<<endl;
    
    strcpy(className, filename.substr(filename.find_last_of('/') + 7, 1).c_str());

    cout<<"className === > "<< className << endl;
    int classid;
    classid = int(className[0]);
    cout<<"className[0] === >" << className[0]<<endl;

    return className[0];
}

Mat ASLGuesture::readImage(string& fileName){
    Mat image = imread(fileName, 1);
    Mat imageGray;
    cvtColor(image, imageGray, CV_BGR2GRAY);
//    blur( imageGray, imageGray, Size(3,3) );
    GaussianBlur(imageGray, imageGray, Size(5,5), 0);
    
//    namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
//    namedWindow( "Gray Image", CV_WINDOW_AUTOSIZE );
//
//    imshow( "Original Image", image );
//    imshow( "Gray image", imageGray );
//
//    waitKey(0);
    
    return imageGray;
}

vector<Point> ASLGuesture::getContourLine(const Mat& matImg,
                    vector<Mat>& vmatObjList,
                    const int &iThresh,
                    const int &k)
{
    // copy image as the following methods altered it
    Mat imageCopy = matImg.clone();
    
    //image preparation
    threshold(imageCopy,imageCopy,iThresh,
              255, //set all points meeting the threshold to 255
              THRESH_BINARY //output is a binary image
              );
    
    //perform closing --> dilate first, then erode
    dilate(imageCopy,imageCopy,
           Mat(), //3x3 square kernel
           Point(-1,-1), //upper left corner
           1);

    erode(imageCopy,imageCopy,
          Mat(), //Mat() leads to a 3x3 square kernel
          Point(-1,-1), //upper corner
          k);
    
//    namedWindow("test", CV_WINDOW_AUTOSIZE);
//     imshow("test", imageCopy);
//     waitKey(0);
    
//    namedWindow("test_dilate", CV_WINDOW_AUTOSIZE);
//     imshow("test_dilate", imageCopy);
//     waitKey(0);
//    namedWindow("test_erode", CV_WINDOW_AUTOSIZE);
//     imshow("test_erode", imageCopy);
//     waitKey(0);
    vector<Vec4i> hierarchy;
    findContours(imageCopy, vmatObjList,
                 CV_RETR_LIST , //only outer contours
                 CV_CHAIN_APPROX_NONE //no approximation
                 );
    
    Mat drawing = Mat::zeros( imageCopy.size(), CV_8UC3 );
    
    int largest_area=0;
    int largest_contour_index = 0;
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

    for( int i = 0; i< vmatObjList.size(); i++ )
    {
        double contourIArea = contourArea(vmatObjList[i],false);
//        cout<<" i--> "<< i <<" contourIArea --> "<< contourIArea <<endl;
        if(contourIArea > largest_area){
            largest_area = contourIArea;
            largest_contour_index = i;
            
        }
        
    }
//    cout<<"largest_area = "<< largest_area<< " largest_contour_index -- >  "<<largest_contour_index<<endl;
    
//    drawContours( drawing, vmatObjList, largest_contour_index, color, 2, 8, hierarchy, 0, Point() );
//    cout<<vmatObjList[largest_contour_index].size<<endl;
    /// Show in a window
//    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//    imshow( "Contours", drawing );
//    waitKey(0);
    
    return vmatObjList[largest_contour_index];
}



void ASLGuesture::loadData(){
    
    
    
};

vector<float> ASLGuesture::EllipticFourierDescriptors(vector<Point>& contour)
{
    vector<float> ax , ay , bx , by ;
    vector<float> CE;
    int m = contour.size();
    int n = 20;
    float t=(2*CV_PI)/m;
    for ( int k=0;k<n ; k++){
        
        ax.push_back(0.0) ;
        ay.push_back(0.0) ;
        bx.push_back(0.0) ;
        by.push_back(0.0) ;
        
        for(int i=0;i<m;i++){
            
            ax[k] = ax[k]+contour[i].x*cos((k+1)*t*(i));
            bx[k] = bx[k]+contour[i].x*sin((k+1)*t*(i));
            ay[k] = ay[k]+contour[i].y*cos((k+1)*t*(i));
            by[k] = by[k]+contour[i].y*sin((k+1)*t*(i));
            
        }
        
        ax[k]=(ax[k])/m;
        bx[k]=(bx[k])/m;
        ay[k]=(ay[k])/m;
        by[k]=(by[k])/m;
        
    }
    
    for (int k =0;k<n;k++){
        CE.push_back(sqrt((ax[k]*ax[k]+ay[k]*ay[k])/(ax[0]*ax[0]+ay[0]*ay[0]))+sqrt((bx[k]*bx[k]+by[k]*by[k])/(bx[0]*bx[0]+by[0]*by[0])));
    }
    
//    for(int count=0; count<n && count<CE.size(); count++){
//        printf("%d CE %f ax %f ay %f bx %f by%f \n", count, CE[count], ax[count], ay[count], bx[count], by[count]);
//    }
    
    return CE;
    
}
