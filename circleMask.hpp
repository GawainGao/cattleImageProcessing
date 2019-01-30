//
//  circleMask.hpp
//  New_cattle
//
//  Created by 高源 on 2018/11/27.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#ifndef circleMask_hpp
#define circleMask_hpp

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat circleMask(int rows, int cols, Point2f center, int radius);

#endif /* circleMask_hpp */
