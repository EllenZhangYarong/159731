//
//  DecodingAndEncoding.cpp
//  ColorBarcode
//
//  Created by 张亚荣 on 2018/5/7.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//
  
#include "DecodingAndEncoding.hpp"
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

DecodingAndEncoding::DecodingAndEncoding(Mat image){
    this->image = image;
    this->encodingarray = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y','w','z',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','X','Y','W','Z',
        '0','1','2','3','4','5','6','7','8','9','.'};
};
DecodingAndEncoding::DecodingAndEncoding(Mat image, string message, Mat pic){
    this->image = image;
    this->message = message;
    this->pic = pic;
};
string DecodingAndEncoding::decodingQR(){
    Mat image = this->image;
    
    string mesFinal="", mesCode="", meschar="";

    for(int i = 1; i <= 47; i++){
        for(int j = 1; j <= 47; j++){

            if( i <= 6 && j <= 6){
                //do nothing at left-top corner
                continue;
            }
            if( i >= 42 && j >= 42){
                //do nothing at right-bottom corner
                continue;
            }
            if( i >= 42 && j <= 6){
               //do nothing at left-bottom corner
                continue;
            }
            
            int b = (image.at<Vec3b>(i-1 ,j-1)[0] > 127 ) ? 1 : 0;
            int g = (image.at<Vec3b>(i-1 ,j-1)[1] > 127 ) ? 1 : 0;
            int r = (image.at<Vec3b>(i-1 ,j-1)[2] > 127 ) ? 1 : 0;
            
            meschar += to_string(r)+to_string(g)+to_string(b);

            if(meschar.length()!=0 && meschar.length() % 6 == 0){

                
                int h = stoi(meschar,nullptr,2);

                mesCode = this->encodingarray[h];
//                mesCode = static_cast<char>(std::bitset<6>(meschar).to_ulong() + 64);
                
                cout<<mesCode;
                mesFinal.append(mesCode);

                meschar = "";
                mesCode = "";
            }
            
        }
    }

//    cout<<"Message Length ---> " << mesFinal.length()<<endl;

    return mesFinal;
};
void DecodingAndEncoding::encodingQR(string message){
    this->message = message;
};
