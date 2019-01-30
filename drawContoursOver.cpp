//
//  drawContoursOver.cpp
//  New_cattle
//
//  Created by 高源 on 2018/11/15.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "drawContoursOver.hpp"
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
/*
bool descendSort(vector<Point> a, vector<Point> b)
{
    return a.size() > b.size();
}
bool ascendSort(vector<Point> a, vector<Point> b)
{
    return a.size() < b.size();
}
*/
int drawContoursOver(Mat srcImage)
{
    
    vector<vector<Point>> contours;
    vector<vector<Point>> contours2;
    vector<Point> tempV;
    imshow("Test", srcImage);
    //cv::waitKey(100);
    findContours(srcImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    //sort(contours.begin(), contours.end(), ascendSort);
    vector<vector<Point>>::iterator itc = contours.begin();
    int i = 0;
    while (itc != contours.end()) {
        Rect rect = boundingRect(*itc);
        int x = rect.x;
        int y = rect.y;
        int w = rect.width;
        int h = rect.height;
        cv::rectangle(srcImage, rect, 255, 1);
        char str[10];
        sprintf(str, "%d.jpg",i++);
        imshow("srcImage", srcImage);
        waitKey(100);
        
        if (itc->size() < 100)
        {
            tempV.push_back(Point(x,y));
            tempV.push_back(Point(x,y+h));
            tempV.push_back(Point(x+w,y+h));
            tempV.push_back(Point(x+w,y));
            contours2.push_back(tempV);
            drawContours(srcImage, contours2, -1, 0, CV_FILLED);
        }
        imshow("dstImage", srcImage);
        tempV.clear();
        ++itc;
    }
    waitKey(100);
    return 0;
    
}
