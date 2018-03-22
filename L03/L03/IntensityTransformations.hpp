//
//  IntensityTransformations.hpp
//  L03
//
//  Created by 张亚荣 on 2018/3/20.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef L03_IntensityTransformations_hpp
#define L03_IntensityTransformations_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


class IntensityTransformations{
private:
    Mat image;
    
public:
    IntensityTransformations(Mat image);
    Mat negativeImage();
    Mat simpleThreshold();
    Mat otsusThreshold();
    
};
#endif /* IntensityTransformations_hpp */
