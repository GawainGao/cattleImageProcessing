//
//  colorLevel.hpp
//  New_cattle
//
//  Created by 高源 on 2018/11/19.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#ifndef colorLevel_hpp
#define colorLevel_hpp

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


double colorLevel(Mat srcImage, Rect rect);

#endif /* colorLevel_hpp */
