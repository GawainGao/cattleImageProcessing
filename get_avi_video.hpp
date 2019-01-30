//
//  get_avi_video.hpp
//  New_cattle
//
//  Created by 高源 on 2018/10/29.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>


using namespace cv;
using namespace std;

#ifndef get_avi_video_hpp
#define get_avi_video_hpp

#include <stdio.h>
vector<Mat> get_avi_video(string fileName, int countNumberStart, int countNumberEnd, int step);

#endif /* get_avi_video_hpp */
