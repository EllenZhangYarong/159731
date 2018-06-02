//
//  FeatureExtract.cpp
//  GuestureClassifier
//
//  Created by 张亚荣 on 2018/5/30.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#include "FeatureExtract.hpp"
#include <cstdio>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

vector<float> FeatureExtract::EllipticFourierDescriptors(vector<Point>& contour)
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

