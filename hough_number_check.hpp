//
//  hough_number_check.hpp
//  New_cattle
//
//  Created by 高源 on 2018/10/26.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;
#ifndef hough_number_check_hpp
#define hough_number_check_hpp

#include <stdio.h>

vector<int> hough_number_check(Mat srcImage, int resolution, int distance, int canny, int center, int smallest, int biggest, bool gray);

#endif /* hough_number_check_hpp */

