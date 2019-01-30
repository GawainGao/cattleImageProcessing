//
//  colorLevel.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/19.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "colorLevel.hpp"
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;

double colorLevel(Mat srcImage, Rect rect)
{
    int n = 0;
    int sumsums = 0;
    for (int i = rect.x + 1; i < rect.x - 1 + rect.width; i ++) {
        uchar* data = srcImage.ptr<uchar>(i);
        for (int j = rect.y + 1; j < rect.y - 1 + rect.height; j ++) {
            sumsums = sumsums + (int)data[j];
            ++n;
        }
    }
    double res;
    res = sumsums / n;
    return res;
}
