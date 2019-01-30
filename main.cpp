//
//  main.cpp
//  New_cattle
//
//  Created by 高源 on 2018/10/25.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cvaux.hpp>
#include <fstream>
#include <vector>
#include <time.h>

#include "bmp_read.hpp"
#include "hough_number_check.hpp"
#include "getFiles.hpp"
#include "get_avi_video.hpp"
#include "bmp_read_pl.hpp"
#include "hough_returnROI.hpp"
#include "countWhiteArea.hpp"
#include "circleMask.hpp"
#include "splitMergeRGB.hpp"
//#include "drawContoursOver.hpp"
#include "colorLevel.hpp"
using namespace std;
using namespace cv;

bool ascendSort(vector<Point> a, vector<Point> b)
{
    return a.size() < b.size();
}

bool descendSort(vector<Point> a, vector<Point> b)
{
    return a.size() > b.size();
}

int main(int argc, const char * argv[])

{
    string pathName = "/Volumes/Transcend/cattle/828/WA03_2016_1_1_16_23_37_348162";
    //string pathName = "/Volumes/Transcend/cattle/828/WA03_2016_1_1_8_49_53_218555";
    string dstPathName = pathName + "/result";
    string value = "create a new file";
    ofstream outfile;
    string csvName = pathName + "/total.csv";
    string shrinkName = dstPathName + "/shrink.csv";
    string intensityName = dstPathName + "/intensity.csv";
    string pupilName = pathName + "/pupil.csv";
    
//----------------------------------PL picture part (Pupil RGB)---------------------------
//Set the output structure
//Get plx.bmp
    outfile.open(pupilName,ios::out);
    outfile << "原画像" << "," << "LEDリング中心x" << "," << "LEDリング中心y" << "," << "LEDリング半径" << "," << "R平均" << "," << "G平均" << "," << "B平均" << endl;
    const int plnum = 10;
    Mat withPLpicturesOriginal[plnum];
    Mat withPLpictures[plnum];
    Mat PLpicturesAfterHough[plnum];
    Mat PLpicturesAfterHSV[plnum];
    
    bool pictureFlag[plnum];
    double rAverage[plnum];
    double bAverage[plnum];
    double gAverage[plnum];
    double LEDOutlineCenterX[plnum];
    double LEDOutlineCenterY[plnum];
    double LEDOutlineRadius[plnum];
    
    vector<int> roi(3);
    roi[0] = 0;
    roi[1] = 0;
    roi[2] = 0;
    for (int i = 1; i <= plnum; i++)
    {
        string windowName;
        vector<Mat> channelsHSV;  //split channels to HSV
        vector<Mat> channelsRGB;  //split channels to RGB
        vector<Vec3f> circlesInformation;
        Mat imageRChannel;
        Mat imageGChannel;
        Mat imageBChannel;
        Mat imageHChannel;
        Mat imageSChannel;
        Mat imageVChannel;        //define all the channels
        cout << "NO: " << i << endl;
        withPLpicturesOriginal[i-1] = bmp_read_pl(i, pathName);
        withPLpictures[i-1] = bmp_read_pl(i, pathName);     //read the pictures
        //cvtColor(withPLpictures[i-1], withPLpictures[i-1], CV_BGR2GRAY);
        //GaussianBlur(withPLpictures[i-1], withPLpictures[i-1], Size(9,9), 2,2);
        //PLpicturesAfterHough[i-1] = hough_number_check(withPLpictures[i-1], 1, 1, 200, 20, 0, 200);
        cvtColor(withPLpicturesOriginal[i-1], PLpicturesAfterHSV[i-1], CV_BGR2HSV);
        
        split(withPLpicturesOriginal[i-1], channelsRGB);
        split(PLpicturesAfterHSV[i-1], channelsHSV);
        imageRChannel = channelsRGB.at(0);
        imageGChannel = channelsRGB.at(1);
        imageBChannel = channelsRGB.at(2);
        imageHChannel = channelsHSV.at(0);
        imageSChannel = channelsHSV.at(1);
        imageVChannel = channelsHSV.at(2);
        windowName = "NO. " + to_string(i) + " pl picture";
        //circlesInformation = hough_returnROI(withPLpictures[i-1], 2, 1, 50, 50, 0, 20);
        //cout << "Hough circle parameters" << endl;
        //cout << "Point center x : " << circlesInformation[0][0] << " y: " << circlesInformation[0][1] << " radius: " << circlesInformation[0][2] <<endl;
        //roi[i-1] = withPLpictures[i-1](Rect(circlesInformation[0][0]-circlesInformation[0][2],circlesInformation[0][1]-circlesInformation[0][2],circlesInformation[0][2]*2,circlesInformation[0][2]*2));
        //imshow("windowname", roi[i-1]);
        //imshow(windowName, withPLpicturesOriginal[i-1]);
        roi = hough_number_check(withPLpictures[i-1],2,1,50,50,0,50,false);
        cout << "Point center x : " << roi[0] << " y: " << roi[1] << " radius: " << roi[2] << endl;
        //cout << "Check point" << endl;
        threshold(imageSChannel, imageSChannel, 55, 255, THRESH_BINARY);
        medianBlur(imageSChannel, imageSChannel, 19);
        bitwise_not(imageSChannel, imageSChannel);
        //Moments mu = moments(imageSChannel, false);
        //Point2f mc = Point2f(mu.m10/mu.m00 , mu.m01/mu.m00);

        if (roi[0])
        {
            pictureFlag[i-1] = true;
            LEDOutlineRadius[i-1] = roi[2];
            LEDOutlineCenterX[i-1] = roi[0];
            LEDOutlineCenterY[i-1] = roi[1];
            Rect rectLeft;
            Rect rectRight;
            rectLeft.x = LEDOutlineCenterX[i-1] - LEDOutlineRadius[i-1] * 1.5 - 20;
            rectLeft.y = LEDOutlineCenterY[i-1] - 15;
            rectLeft.width = 20;
            rectLeft.height = 45;
            rectRight.x = LEDOutlineCenterX[i-1] + LEDOutlineRadius[i-1] * 1.5;
            rectRight.y = LEDOutlineCenterY[i-1] - 15;
            rectRight.width = 20;
            rectRight.height = 45;
            rectangle(withPLpictures[i-1], rectLeft, Scalar(0,0,255), 2);
            rectangle(withPLpictures[i-1], rectRight, Scalar(255,0,0), 2);
            rAverage[i-1] = (colorLevel(imageRChannel, rectLeft) + colorLevel(imageRChannel, rectRight))/2.0;
            gAverage[i-1] = (colorLevel(imageGChannel, rectLeft)+ colorLevel(imageGChannel, rectRight))/2.0;
            bAverage[i-1] = (colorLevel(imageBChannel, rectLeft)+ colorLevel(imageBChannel, rectRight))/2.0;
        }
        else
        {
            pictureFlag[i-1] = false;
            LEDOutlineRadius[i-1] = 0;
            LEDOutlineCenterX[i-1] = 0;
            LEDOutlineCenterY[i-1] = 0;
            rAverage[i-1] = 0;
            gAverage[i-1] = 0;
            bAverage[i-1] = 0;
        }
        cout << "radius=" << LEDOutlineRadius[i-1] << " x=" << LEDOutlineCenterX[i-1] << " y=" << LEDOutlineCenterY[i-1] << " r_average=" << rAverage[i-1] << " g_average=" << gAverage[i-1] << " b_average=" << bAverage[i-1] << endl;
        
        char save_file[200];
        sprintf(save_file, "/%d.png", i);
        String outName;
        outName = dstPathName + save_file;
        cout << outName << endl;
        imwrite(outName, withPLpictures[i-1]);
        char outFileName[200];
        sprintf(outFileName, "PL%d.bmp", i);
        outfile << outFileName << "," << LEDOutlineCenterX[i-1] << "," << LEDOutlineCenterY[i-1] << "," << LEDOutlineRadius[i-1] << "," << rAverage[i-1] << "," << gAverage[i-1] << "," << bAverage[i-1] << endl;
        
        //circle(withPLpictures[i-1], mc, 40, Scalar(255,0,0),2,4);
        //printf("x:%f y:%f\n",mc.x,mc.y);
        
        //boxFilter(imageSChannel, imageSChannel, -3, Size(5,5));
        //GaussianBlur(imageSChannel, imageSChannel, Size(9,9), 2,2);
        //imageSChannel = hough_number_check(imageSChannel, 2, 100, 100, 50, 100, 150, true);
 
        //threshold(imageRChannel, imageRChannel, 205, 255, 0);
        //threshold(imageVChannel, imageVChannel, 205, 255, 0);
        //imshow(windowName, PLpicturesAfterHough[i-1]);

        //imshow(windowName + "R", imageRChannel);
        //imshow(windowName + "G", imageGChannel);
        //imshow(windowName + "B", imageBChannel);
        //imshow(windowName + "H", imageHChannel);
        //imshow(windowName + "S", imageSChannel);
        //imshow(windowName + "V", imageVChannel);
        //imshow(windowName, roi[i-1]);
        //imshow(windowName + "PL", withPLpictures[i-1]);
        /*
        if (waitKey(20) > 0)
        {
            break;
        }
        */
    }
    outfile.close();
    
    
//----------------------------------NO PL AVI part (Pupil area)---------------------------
//Firstly determine the eye area of the cow
//Secondly from the ROI get the area we need
//Finally calculate the two parameters
    
    
//Get .avi filename

    vector<string> fileNames;

    outfile.open(shrinkName,ios::out);
    outfile << "画像番号" << "," << "短径/長径" << endl;
    fileNames = getFiles(pathName, ".*.avi");
    //cout << "Checkpoint" << endl;
    cout << fileNames[0] << endl;

//Get the frames inside video
    vector<Mat> videoFrames;
    videoFrames = get_avi_video(fileNames[0], 0, 90, 1);
    Mat videoFramesAfterHSV[videoFrames.size()];  //Instance the HSV list
    double PupilLongDivideShort[videoFrames.size()];
    //videoFramesAfterHSV = videoFrames;//Instance the HSV list
    for (int i = 10; i<videoFrames.size(); i++)
    //for (int i = 0; i<3; i++)
    {
        vector<Mat> channelsHSV;  //split channels to HSV
        vector<Mat> channelsRGB;  //split channels to RGB
        string windowName;
        windowName = "NO." + to_string(i * 5 + 5) + " frame";
        Mat imageRChannel;
        Mat imageGChannel;
        Mat imageBChannel;
        Mat imageHChannel;
        Mat imageSChannel;
        Mat imageVChannel;

        cvtColor(videoFrames[i], videoFramesAfterHSV[i], CV_BGR2HSV);
        
        split(videoFrames[i], channelsRGB);
        split(videoFramesAfterHSV[i], channelsHSV);
        imageRChannel = channelsRGB.at(0);
        imageGChannel = channelsRGB.at(1);
        imageBChannel = channelsRGB.at(2);
        imageHChannel = channelsHSV.at(0);
        imageSChannel = channelsHSV.at(1);
        imageVChannel = channelsHSV.at(2);
        Mat imageH2Channel = imageHChannel.clone(); //Get the new one H channel
        //imshow(windowName + "R", imageRChannel);
        //imshow(windowName + "G", imageGChannel);
        threshold(imageHChannel, imageHChannel, 100, 255, 0);
        medianBlur(imageHChannel, imageHChannel, 19);

        
        
        /*
//Test the hough circle method and failed
// 2 300 100 100 0 200
        GaussianBlur(imageBChannel, imageBChannel, Size(9,9), 2,2);
        std::vector<Vec3f> circles;    //set the circle mat
        HoughCircles(imageBChannel, circles, CV_HOUGH_GRADIENT, 2 , 300 , 100 , 100 , 100 , 1000);
        for (size_t i=0;i<circles.size();i++)
        {
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            
            //cout << "Hough circle parameters" << endl;
            //cout << "Point center x : " << circles[i][0] << " y: " << circles [i][1] << " radius: " << circles [i][2] <<endl;

            circle(imageBChannel,center,3,Scalar(0,255,0),-1,8,0);
            circle(imageBChannel,center,radius,Scalar(155,50,255),3,8,0);
        }
        */
        
        bitwise_not(imageHChannel, imageHChannel); //change the inside area black to remove the small area
        vector< vector< Point> > contours;  //save all the contours
        vector< vector< Point> > contours2; //save all the contours smaller than limit
        vector<Point> tempV;                //temp contours
        findContours(imageHChannel, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

        sort(contours.begin(), contours.end(), ascendSort);//upper
        vector<vector<Point> >::iterator itc = contours.begin();
        int check = 0;
        while (itc != contours.end())
        {
            if (itc->size() < 1000)
            {
                contours2.push_back(*itc);
                cv::drawContours(imageHChannel, contours2, -1, Scalar(0,0,0), CV_FILLED);
            }
            check++;
            tempV.clear();
            ++itc;
        }
        bitwise_not(imageHChannel, imageHChannel); //change the eye area white for get the gravity
        Moments mu = moments(imageHChannel, false);
        Point2f mc = Point2f(mu.m10/mu.m00 - 5 , mu.m01/mu.m00 + 5); //Get the center point
        double radius;
        radius = countWhiteArea(imageHChannel, true);
        //circle(videoFrames[i],mc,int(radius * 1.05),Scalar(0,255,0),3,8,0); //Create a circle
        Mat maskSan;
        maskSan = circleMask(imageHChannel.size().height, imageHChannel.size().width, mc, radius); //Create the mask only for eye
        
        
//Use the merge method to get the pupil or use the multiply of the matrix
        imageH2Channel = imageH2Channel.mul(maskSan);
        imageRChannel = imageRChannel.mul(maskSan);
        imageVChannel = imageVChannel.mul(maskSan);
        threshold(imageH2Channel, imageH2Channel, 140, 255, 0);
        //GaussianBlur(imageH2Channel, imageH2Channel, Size(9,9), 2,2);
        bitwise_not(imageH2Channel, imageH2Channel);
        imageH2Channel = imageH2Channel.mul(maskSan);

        //threshold(imageGChannel, imageGChannel, 130, 255, 0);
        threshold(imageRChannel, imageRChannel, 130, 255, 0);
        threshold(imageVChannel, imageVChannel, 130, 255, 0);
        
        //vector<Mat> dstImage;
        Mat fin_img;
        //dstImage.push_back(imageGChannel);
        //dstImage.push_back(imageBChannel);
        //dstImage.push_back(imageRChannel);
        //merge(dstImage, fin_img);
        fin_img = maskSan.mul(imageRChannel).mul(imageVChannel).mul(imageH2Channel);
        medianBlur(fin_img, fin_img, 19);
        
        
//Find the biggest counter
        //bitwise_not(fin_img, fin_img);
        vector<vector<Point>> contours3;
        findContours(fin_img, contours3, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        double maxArea = 0;
        vector<Point> maxContour;
        vector<RotatedRect> minRect( contours3.size() );
        
        for (size_t k = 0; k<contours3.size(); k++) {
            double area = contourArea(contours3[k]);
            minRect[k] = minAreaRect(contours3[k]);
            if (area > maxArea) {
                maxArea = area;
                maxContour = contours3[k];
            }
        }
        

        //Mat result1, result2;
        //fin_img.copyTo(result1);
        //fin_img.copyTo(result2);
        //cout << maxContour << endl;
        if (!maxContour.empty()) {
            RotatedRect maxRect = minAreaRect(maxContour);
            Point2f vertices[4];      //定义4个点的数组
            maxRect.points(vertices);   //将四个点存储到vertices数组中
            for (int j = 0; j < 4; j++){
                line(videoFrames[i-1], vertices[j], vertices[(j+1)%4], Scalar(0,0,0));
            }
            
            char save_file[200];
            sprintf(save_file, "/rate%d.png", i);
            String outName;
            outName = dstPathName + save_file;
            cout << outName << endl;
            imwrite(outName, videoFrames[i-1]);

            double rectLong;
            double rectShort;
            rectLong = sqrt((vertices[0].x-vertices[1].x)*(vertices[0].x-vertices[1].x)+(vertices[0].y-vertices[1].y)*(vertices[0].y-vertices[1].y));
            rectShort = sqrt((vertices[2].x-vertices[1].x)*(vertices[2].x-vertices[1].x)+(vertices[2].y-vertices[1].y)*(vertices[2].y-vertices[1].y));
            PupilLongDivideShort[i-1] = rectLong / rectShort;
            cout << PupilLongDivideShort[i-1] << endl;
            outfile << i << "," << PupilLongDivideShort[i-1] << endl;
        }
        else {
            continue;
        }
    }
    outfile.close();
        /*
//The all rectangles of contours
        for (size_t k = 0;  k < contours3.size(); k++) {
            Rect r = boundingRect(contours3[k]);
            rectangle(result1, r, Scalar(255));
        }
        imshow(windowName + "all regions", result1);
        */
        //imshow(windowName + "largest region", result2);
    
//Output
        //imshow(windowName + "finish", fin_img);
        //imshow(windowName + "B", imageBChannel);
        //imshow(windowName + "G", imageGChannel);
        //imshow(windowName + "R", imageRChannel);
        //imshow(windowName, videoFrames[i]);
        //imshow(windowName + "mask", dstImage);
        //imshow(windowName + "B", imageBChannel);
        //imshow(windowName + "H", imageH2Channel);
        //imshow(windowName + "S", imageSChannel);
        //imshow(windowName + "V", imageVChannel);
        //cout << "Check Point" << endl;
        
        /*
//SplitMerge method is not good to use.
        Mat dstImage;
        dstImage = splitMergeRGB(videoFrames[i], 100, 255, 100, 255, 100, 255);
        imshow(windowName, dstImage);
        cvtColor(videoFrames[i], videoFramesAfterHSV[i], CV_BGR2HSV);
        imshow(windowName + "HSV", videoFramesAfterHSV[i]);
        
        if (waitKey(20) > 0)
        {
            break;
        }
        */
    

    
//-----------------------NOPL5--NOPL8----------------------

    
    outfile.open(csvName,ios::out);
    outfile << "ファイル名：読み込んだ時のセッション名をファイル名とする" << endl;
    outfile << " " << "," << " " << "," << "牛ビタミンA推定　変数の画像とのCSVデータ関連付け（各画像データから数値化データの取り出し） 画像読み取りソフト活用による画像からの数値データエクセルへの取込みイメージ" << endl;
    outfile << "牛番号（ID) Cattle ID" << " " << "," << " " << "," << "注）牛の個体識別タグと牛番号の対応が必要" << endl;
    outfile << "生年月日     Birth Date" << " " << "," << " " << "," << "注）牛の年齢がビタミンA濃度に影響" << endl;
    outfile << "画像撮影日  Taking picture date" << endl;
    outfile << "ビタミンA濃度  Viamain A concentration" << "," << "画像番号 Picture No" << "," << "瞳孔収縮率（短径／長径）Shrink ratio" << "," << "眼底色 短径／長径比　　　同左" << "," << "YY座標Y axis" << "," << "R" << "," << "G" << "," << "B" << "," << "瞳孔色 LEDリング中心ｘ" << "," << "LEDリング中心ｙ" << "," << "LEDリンク半径" << "," << "R平均　R mean" << "," << "G平均　G mean" << "," << "B平均　B mean" << endl;
    
    for (int i = 1; i < plnum; i++) {
        outfile << " " << "," << i << "," << PupilLongDivideShort[(i-1)*8 + 10] << "," << " " << "," << " " << "," << " " << "," << " " << "," << " " << "," << LEDOutlineCenterX[i-1] << "," << LEDOutlineCenterY[i-1] << "," << LEDOutlineRadius[i-1] << "," << rAverage[i-1] << "," << gAverage[i-1] << "," << bAverage[i-1] << endl;
    }
    outfile << " " << endl;
    outfile << "画像取込み確認         Confirmation of Input picture numerical ananysis" << endl;
    outfile << "画像でこれらのデータの有無（〇×）表示（注：左の1セルの画像に　　　　　　以下４１行の光反射のRGBデータが存在する）" << endl;
    outfile << "眼球表面の光反射の計測" << endl;
    outfile << " " << "," << "NOPL5.bmp" << "," << " " << "," << " " << "," << "NOPL6.bmp" << "," << " " << "," << " " << "," << "NOPL7.bmp" << "," << " " << "," << " " << "," << "NOPL8.bmp" << endl;
    outfile << "画素番号" << "," << "R" << "," << "G" << "," << "B" << "," << "R" << "," << "G" << "," << "B" << "," << "R" << "," << "G" << "," << "B" << "," << "R" << "," << "G" << "," << "B" << endl;
    
    //Close the file
    outfile.close();
    
/*
    outfile.open(shrinkName,ios::out);
    outfile << "画像番号" << "," << "短径/長径" << endl;
    for (int i = 0; i < 90; i++) {
        outfile << to_string(i) << "," << PupilLongDivideShort[i] << endl;
    }
    outfile.close();
*/

/*
//Get bmp image and do hough transform to get the neckband pattern
    const int num = 11;
    Mat srcImageList[num];
    for (int i = 1; i <= num; i++)
    {
        char windowName[100];
        srcImageList[i-1]= bmp_read(i, pathName);
        // 2 300 100 100 0 200
        //srcImageList[i-1] = hough_number_check(srcImageList[i-1],2,300,100,100,0,200,false);
        sprintf(windowName, "NO:%d",i);
        //cout << windowName << endl;
        imshow(windowName, srcImageList[i-1]);
    }
    //std::cout << "Hello, World!\n";
    waitKey(0);
 */
    return 0;
}
