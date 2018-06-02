//
//  main.cpp
//  GuestureClassifier
//
//  Created by 张亚荣 on 2018/5/10.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <cstdlib>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ASLGuesture.hpp"
#include "TrainingAndTest.cpp"

using namespace std;
using namespace cv;

//! Threshold for image binarization.
static const int iBinThreshold = 10;
//! Number of applications of the erosion operator.
static const int iNumOfErosions = 1;

int main(int argc, const char * argv[]) {
    // insert code here...

    int classid;
    string fileName = "/Users/ellen/EllenZhangYarong/159731/GuestureClassifier/GuestureClassifier/Glass.data";

//        FILE* f = fopen( fileName.c_str(), "rt" );
    ofstream dataFile;
    dataFile.open(fileName, ios::in|ios::out|ios::binary);

    if( !dataFile )
        {
            cout << "Could not read the database " << fileName << endl;
            return -1;
        }

        else{

            ASLGuesture aSLGuesture;
            vector<string> files = aSLGuesture.getFilesInDirectory(argv[1]);
            random_shuffle(files.begin(), files.end());

            for (auto file : files){
//                cout << file << endl;

                char className = aSLGuesture.getClassIntLabel(file);
                cout << "MAIN: className ----->  "<< className << endl;
                cout << "MAIN: int(className) ----->  "<< int(className) << endl;

                string ceString = "";
                int classId;

                if(int(className) >= 97){
                    classId = int(className)- 97 + 10 ;
                }
                else{
                    classId = int(className) - 48;
                }
                cout << "MAIN: classId ----->  "<< classId << endl;

                char label = char(classId+48);
                cout << "MAIN: label ----->  "<< label << endl;

                ceString += label;



                cout<< "Main::ceString ===> "<<ceString<< endl;

//                cout << "classid ----> " << classid << endl;
                Mat image = aSLGuesture.readImage(file);

//                namedWindow( "Gray Image", CV_WINDOW_AUTOSIZE );
//
//                imshow( "Gray image", image );
//
//                waitKey(0);

                vector<Mat> vmatContourLines1;
                vector<Point> largestContour = aSLGuesture.getContourLine(image, vmatContourLines1, iBinThreshold, iNumOfErosions);

                vector<float> CE = aSLGuesture.EllipticFourierDescriptors(largestContour);
//                CE[0] = classid;


                cout<<"The first of ceString----->"<<ceString<<endl;
//                dataFile << (char)classid;


                for(int i = 1; i<CE.size();i++){

                    ceString =  ceString + "," + to_string(CE[i]) ;
                }
                ceString += "\n";

                cout<<"CE -- > "<< ceString <<endl;
                dataFile << ceString;
            }
            dataFile.close();
        }


    std::cout << "Hello, World!\n";
    return 0;
//
}


