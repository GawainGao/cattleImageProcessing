//
//  bmp_read.cpp
//  New_cattle
//
//  Created by 高源 on 2018/10/26.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "bmp_read.hpp"
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


Mat bmp_read(int num, string foalderName)
{
    Mat srcImage;
    string fileName;
    fileName = foalderName + "/id" + to_string(num) + ".bmp";
    srcImage = imread(fileName);
    if (!srcImage.data)
    {
        cout << "No data!" << endl;
    }
    //cout << " " << endl;
    //cout << "NO: " << num << endl;
    return srcImage;
}
