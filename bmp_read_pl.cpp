//
//  bmp_read_pl.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/1.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

#include "bmp_read_pl.hpp"

Mat bmp_read_pl(int num, string foalderName)
{
    Mat srcImage;
    string fileName;
    fileName = foalderName + "/pl" + to_string(num) + ".bmp";
    srcImage = imread(fileName);
    if (!srcImage.data)
    {
        cout << "No data!" << endl;
    }
    else
    {
        cout << "Successful read the NO:" << num << " picture" << endl;
    }
    //cout << "NO: " << num << endl;
    return srcImage;
}
