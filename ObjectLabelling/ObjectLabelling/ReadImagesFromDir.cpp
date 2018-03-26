//
//  ReadImagesFromDir.cpp
//  ObjectLabelling
//
//  Created by 张亚荣 on 2018/3/26.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "ReadImagesFromDir.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <dirent.h>

using namespace std;
using namespace cv;

ReadImagesFromDir::ReadImagesFromDir(string path){
    this->path = path;
    cout<<path<<endl;
};

vector<Mat> ReadImagesFromDir::doReadImages(){
    const string path = this->path ;
    cout<<path<<endl;
    char *p = new char[path.length()+1];
    
    strcpy(p, path.c_str());
    
    vector<Mat> images;
    
    DIR *dir;
    struct dirent *ent;
    
    if ((dir = opendir (path.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if ( !strcmp( ent->d_name, "."  )) continue;
            if ( !strcmp( ent->d_name, ".." )) continue;
            
            if(strstr(ent->d_name,".jpg")){
                
                string imageaddress = path + "/" + ent->d_name;
                cout<<"imageaddress -> "<<imageaddress<<endl;
                Mat image = imread(imageaddress,0);
                
                images.push_back(image);

            }
        }
        for(auto image : images ){
            cout<<image.size<<endl;
        }
        closedir (dir);
        
    } else {
        /* could not open directory */
        perror ("could not open directory");
        exit(-1);
    }
    delete[] p;
    this->images = images;
    return this->images;
};
