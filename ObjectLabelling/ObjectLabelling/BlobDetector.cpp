//
//  BlobDetector.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/16.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "BlobDetector.hpp"

#include <opencv2/core/core.hpp>

int counter;
BlobDetector::BlobDetector(Mat& image){
    
    if(image.data==NULL){
        cout << "No image input" << endl;
        return;
    }

    this -> image = image;
    
//    cout << " image matrix : " <<endl;
//    print(this -> image);
    
    this -> imgMask = Mat(image.size(), CV_32SC1, cvScalar(-1));
    
//    cout << (this->imgMask) <<endl;
    
};

void BlobDetector::print(vector<vector<Point>> &setsOfBlob){
    for(auto sets : setsOfBlob)
        for(auto points: sets){
            cout << points << endl;
            cout << endl;
        }
};

void BlobDetector::findingBlobs(){
    Mat image = this->image;
    vector<vector<Point>> setsOfBlob;
    counter = -1;
    int s1, s2;
    
    
    for(int y = 1; y < image.rows; y++){
        for(int x = 1; x < image.cols; x++){

            if(image.at<uchar>(y,x) != 0){
                
//                cout <<"("<< y <<" , "<< x <<" ) color not 0 --->  " << int(image.at<uchar>(y,x)) << endl;
//                cout << "left -->" << (int)image.at<uchar>(y,x-1) << endl;
//                cout << "top --> " << (int)image.at<uchar>(y-1,x) << endl;
                
                if(int(image.at<uchar>(y,x-1)) != 0 || int(image.at<uchar>(y-1,x)) != 0){

                    s2 = this->imgMask.at<int>(y, x-1);
                    s1 = this->imgMask.at<int>(y-1, x);
                    
//                    cout << "s1= "<< s1 <<" || s2= "<< s2 <<endl;
                    
                    if(s1 != -1){

//                        setsOfBlob[s1].back();
                        setsOfBlob[s1].push_back(Point(y,x));
                        
//                        cout<<" -----s1 != -1------ "<<endl;
//                        for(auto setsblobs : setsOfBlob){
//                            for(auto setspoints : setsblobs)
//                                cout<< setspoints;
//                            cout << endl;
//                        }
                        this->imgMask.at<int>(y,x) = s1;
//                        cout<< (this->imgMask) <<endl;
                        
                    }
                    if(s2 != -1){
                        if(s2 == s1){
                            
//                            cout<<"s2 == s1 do nothing "<<endl;
                            
                        }else{
                        
//                            cout<<" -----s2 != -1------ "<<endl;

                            setsOfBlob[s2].push_back(Point(y,x));
                            
//                            for(auto setsblobs : setsOfBlob){
//                                for(auto setspoints : setsblobs)
//                                    cout<< setspoints;
//                                cout << endl;
//                            }
                            
                            this->imgMask.at<int>(y,x) = s2;
                        }
                    }
                    if(s1 != s2 && s1!=-1 && s2!=-1){

                        setsOfBlob.at(s1).insert(setsOfBlob.at(s1).end(), make_move_iterator(setsOfBlob.at(s2).begin()),make_move_iterator(setsOfBlob.at(s2).end()));
                        
                        for(auto vecS2 : setsOfBlob.at(s2)){
                            this->imgMask.at<int>(vecS2.x, vecS2.y) = s1;

                        }

                        setsOfBlob.at(s2).clear();
                        setsOfBlob.at(s2).shrink_to_fit();

//                        counter --;
                    }
                }
                else{
                    counter ++;

//                    cout<<"counter = "<< counter <<endl;
                    vector<Point> setvec;
                    this->imgMask.at<int>(y,x) = counter;
//                    cout<<(this->imgMask).at<int>(y,x)<<endl;
                    
                    setsOfBlob.push_back(setvec);
                    setvec.push_back(Point(y,x));
                    

//                    for(auto sets: setsOfBlob){
//                        cout << "set size: -> " << sets.size()<< endl;
//                        for(auto points: sets){
//                            cout << points ;
//                        }
//                        cout << endl;
//                    }
                    
                    
                }
            }
        }
    }
    this -> setsOfBlob = setsOfBlob;

    //    cout << "setsOfBlob size -> " << (this -> setsOfBlob).size() << endl;
};

int BlobDetector::getNumberOfBlobs(){
    int blobCounter  = 0;

    for(int i = 0;i < setsOfBlob.size(); i++){
        if(setsOfBlob[i].size()>10){
            blobCounter++;
        }
    }
    counter = blobCounter;
    return counter;
};

//Only blobs, no empty vectors
vector<vector<Point>> BlobDetector::getFullBlobs(){
    vector<vector<Point>> vectemp;
    
    for(auto sets : this->setsOfBlob){
        if(sets.size() > 2){
            vectemp.push_back(sets);
        }
    }
   
    cout << "vectemp.size = " << vectemp.size() << endl;
    
    this->setsOfFullBlobs = vectemp;
    return this->setsOfFullBlobs;
        
};


vector<vector<Point>> BlobDetector::getSetsOfBlob(){
    return this->setsOfBlob;
};
    
Mat BlobDetector::getImgMask(){
        
    return this->imgMask;
};
