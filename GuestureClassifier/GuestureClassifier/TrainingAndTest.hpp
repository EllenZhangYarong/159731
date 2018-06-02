//
//  TrainingAndTest.hpp
//  GuestureClassifier
//
//  Created by 张亚荣 on 2018/5/28.
//  Copyright © 2018年 EllenAndAngel. All rights reserved.
//

#ifndef GuestureClassifier_TrainingAndTest_hpp
#define GuestureClassifier_TrainingAndTest_hpp

#include <cstdio>
#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

template<typename T>

class TrainingAndTest{
    
public:
    static bool build_mlp_classifier( const string& data_filename,
                                     const string& filename_to_save,
                                     const string& filename_to_load );
    static bool read_num_class_data( const string& filename, int var_count,
                                    Mat* _data, Mat* _responses );
    static Ptr<T> load_classifier(const string& filename_to_load);


};
#endif /* TrainingAndTest_hpp */
