//
//  countWhiteArea.hpp
//  New_cattle
//
//  Created by 高源 on 2018/11/27.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#ifndef countWhiteArea_hpp
#define countWhiteArea_hpp

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

double countWhiteArea(Mat srcImage, bool white);

#endif /* countWhiteArea_hpp */
