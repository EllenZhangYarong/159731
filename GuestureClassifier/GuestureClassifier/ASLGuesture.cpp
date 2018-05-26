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

using namespace std;
using namespace cv;

struct ImageData
{
    std::string classname;
    cv::Mat bowFeatures;
};

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

inline string ASLGuesture::getClassName(const string& filename)
{
    return filename.substr(filename.find_last_of('/') + 1, 7);
}
