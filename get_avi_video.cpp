//
//  get_avi_video.cpp
//  New_cattle
//
//  Created by 高源 on 2018/10/29.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "get_avi_video.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

vector<Mat> get_avi_video(string fileName, int countNumberStart, int countNumberEnd, int step)
{
    VideoCapture cap;
    cap.open(fileName);
    if (!cap.isOpened())
        cout << "No video" << endl;
    
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int framerate = cap.get(CV_CAP_PROP_FPS);
    int totalframes = cap.get(CV_CAP_PROP_FRAME_COUNT);
    
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Frame rate: " << framerate << endl;
    cout << "Total frames: " << totalframes << endl;
    
    vector<Mat> estVideoList;
    Mat estVideoMat;
    string estName;
    int countNumber;
    string windowName = "";
    int flag = 1;
    for (int i = 0; i < cap.get(CV_CAP_PROP_FRAME_COUNT); i++)
    {
        countNumber = i;
        if ( countNumber >= countNumberStart && countNumber < countNumberEnd && (countNumber % step == 0))
        {
            flag++;
            cap >> estVideoMat;
            estName = to_string(countNumber) + ".jpg";
            cout << "NO." << countNumber << " frame" << endl;
            windowName = "NO:" + to_string(countNumber) + "frame";
            estVideoList.push_back(estVideoMat.clone());
/*
            imshow(windowName, estVideoMat);
            if (waitKey(20)>0)
                break;
*/
        }
        else
        {
            cap >> estVideoMat;
            continue;
        }
    }    
    cap.release();
    return estVideoList;
}
    
/*
//Read all the frames
    while(1){
        cap.read(estVideoMat);
        if (estVideoMat.empty())
            break;
        imshow("Video",estVideoMat);
        if (waitKey(20)>0)
            break;
    }
    cap.release();
    return estVideoMat;
*/


