//
//  splitMergeRGB.hpp
//  New_cattle
//
//  Created by 高源 on 2018/11/27.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#ifndef splitMergeRGB_hpp
#define splitMergeRGB_hpp

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat splitMergeRGB(Mat srcImage, int r_start, int r_end, int g_start, int g_end, int b_start, int b_end);
#endif /* splitMergeRGB_hpp */
