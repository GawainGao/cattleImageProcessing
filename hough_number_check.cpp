//
//  hough_number_check.cpp
//  New_cattle
//
//  Created by 高源 on 2018/10/26.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "hough_number_check.hpp"
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// 2 300 100 100 0 200


vector<int> hough_number_check(Mat srcImage, int resolution, int distance, int canny, int center, int smallest, int biggest, bool gray)
{
    Mat roi;                       //select the roi area "near the linngu"
    int cols = srcImage.cols;
    int rows = srcImage.rows;
    
    Mat midImage, dstImage;
    if (!gray)                     //gray picture for 1 tunnel or not
    {
        cvtColor(srcImage, midImage, CV_BGR2GRAY);
        GaussianBlur(midImage, midImage, Size(9,9), 2,2);
    }
    else
    {
        GaussianBlur(srcImage, midImage, Size(9,9), 2,2);
    }
    std::vector<Vec3f> circles;    //set the circle mat
    HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, resolution, distance , canny , center , smallest , biggest);
    size_t flag = 0;
    int min_y = 0;
    int min_x = 0;
    int min_radius = 0;
    for (size_t i=0;i<circles.size();i++)
    {
        Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        
        //cout << "Hough circle parameters" << endl;
        //cout << "Point center x : " << circles[i][0] << " y: " << circles [i][1] << " radius: " << circles [i][2] <<endl;
        
        min_y = max(min_y, int(circles[i][1]));
        if (min_y == int(circles[i][1]))
        {
            flag = i;
            min_radius = radius;
            min_x = center.x;
        }
        //circle(srcImage,center,3,Scalar(0,255,0),-1,8,0);
        //circle(srcImage,center,radius,Scalar(155,50,255),3,8,0);
    }
    Point center_dst(cvRound(min_x),cvRound(min_y));
    circle(srcImage,center_dst,min_radius,Scalar(155,50,255),3,8,0);
    vector<int> dstData(3);
    Rect rect;
    rect.x = min_x - min_radius * 1.5 - 20;
    rect.y = min_y - min_radius * 1.5;
    rect.width = min_radius * 3 + 40;
    rect.height = min_radius * 3;
    if (cols-1-rect.x<rect.width||rows-1-rect.y<rect.height) {
        cout << "Out of bound" << endl;
        //roi = srcImage(Rect(1,1,rect.width,rect.height));
        circles[0][0] = 0;
    }
    else
    {
        roi = srcImage(Rect(rect.x, rect.y, rect.width, rect.height));
        rectangle(srcImage, rect, Scalar(0,0,255), 2);
        //imshow("SignROI", roi);
        cout << "Inside boundary" << endl;
    }
    dstData[0] = min_x;
    dstData[1] = min_y;
    dstData[2] = min_radius;
    return dstData;
}
