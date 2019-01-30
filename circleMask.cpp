//
//  circleMask.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/27.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "circleMask.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


Mat circleMask(int rows, int cols, Point2f center, int radius)
{
    Mat dstImage(rows, cols, CV_8U);
    for (int i = 0; i < dstImage.size().height; i ++) {
        uchar* data = dstImage.ptr<uchar>(i);
        for (int j = 0; j < dstImage.size().width; j ++) {
            if ((j-int(center.x))*(j-int(center.x))+(i-int(center.y))*(i-int(center.y))<=radius*radius)
            {
                data[j] = 1;
            }
            else
            {
                data[j] = 0;
            }
                
        }
    }
    //imshow("result", dstImage);
    return dstImage;
}
