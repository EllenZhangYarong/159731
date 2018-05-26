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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ASLGuesture.hpp"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    ASLGuesture aSLGuesture;
    vector<string> files = aSLGuesture.getFilesInDirectory(argv[1]);
    random_shuffle(files.begin(), files.end());
    for (auto file : files){
        cout << file << endl;
    }

        std::cout << "Hello, World!\n";
    return 0;
}
