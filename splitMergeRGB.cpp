//
//  splitMergeRGB.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/27.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "splitMergeRGB.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat splitMergeRGB(Mat srcImage, int r_start, int r_end, int g_start, int g_end, int b_start, int b_end)
{
    Mat dstImage(srcImage.size().height,srcImage.size().width,CV_8U);
    vector<Mat> channelRGB;
    split(srcImage, channelRGB);
    Mat Rchannel;
    Mat Gchannel;
    Mat Bchannel;
    Rchannel = channelRGB.at(0);
    Gchannel = channelRGB.at(1);
    Bchannel = channelRGB.at(2);
    for (int i = 0; i < srcImage.size().height; i ++)
    {
        for (int j = 0; j < srcImage.size().width; j ++) {
            if (Rchannel.at<int>(i, j) > r_start && Rchannel.at<int>(i,j) < r_end && Gchannel.at<int>(i, j) > g_start && Gchannel.at<int>(i,j) < g_end && Bchannel.at<int>(i, j) > b_start && Bchannel.at<int>(i,j) < b_end)
            {
                dstImage.at<int>(i,j) = 0;
            }
            else
            {
                dstImage.at<int>(i,j) = 255;
            }
        }
    }
    return dstImage;
    
}
