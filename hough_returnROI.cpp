//
//  hough_returnROI.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/14.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "hough_returnROI.hpp"
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace cv;
using namespace std;

// 2 300 100 100 0 200



vector<Vec3f> hough_returnROI(Mat srcImage, int resolution, int distance, int canny, int center, int smallest, int biggest)
{
    Mat midImage, dstImage;
    
    cvtColor(srcImage, midImage, CV_BGR2GRAY);
    GaussianBlur(midImage, midImage, Size(9,9), 2,2);
    
    std::vector<Vec3f> circles;
    HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, resolution, distance , canny , center , smallest , biggest);
    int max_y = 0;
    size_t flag;
    for (size_t i=0;i<circles.size();i++)
    {
        //Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
        //int radius = cvRound(circles[i][2]);
        
        cout << "Hough circle parameters" << endl;
        cout << "Point center x : " << circles[i][0] << " y: " << circles[i][1] << " radius: " << circles [i][2] <<endl;
        max_y = max(int(circles[i][1]), max_y);
        if (max_y == circles[i][1])
        {
            flag = i;
        }
        //circle(srcImage,center,3,Scalar(0,255,0),-1,8,0);
        //circle(srcImage,center,radius,Scalar(155,50,255),3,8,0);
    }
    return circles;
}
