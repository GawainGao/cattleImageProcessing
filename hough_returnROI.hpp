//
//  hough_returnROI.hpp
//  New_cattle
//
//  Created by 高源 on 2018/11/14.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

#ifndef hough_returnROI_hpp
#define hough_returnROI_hpp


vector<Vec3f> hough_returnROI(Mat srcImage, int resolution, int distance, int canny, int center, int smallest, int biggest);


#endif /* hough_returnROI_hpp */

