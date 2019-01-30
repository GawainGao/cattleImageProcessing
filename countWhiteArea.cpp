//
//  countWhiteArea.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/27.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "countWhiteArea.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>



using namespace cv;
using namespace std;

double countWhiteArea(Mat srcImage, bool white)
{
    int n = 0;
    for (int i = 1; i < srcImage.size().height; i ++)
    {
        uchar* data = srcImage.ptr<uchar>(i);
        for (int j = 1; j < srcImage.size().width; j ++)
        {
            if ((int)data[j])
            {
                ++n;
            }
        }
    }
    double radius;
    radius = sqrt(n/M_PI);
    //cout << radius << endl;
    return radius;
}
