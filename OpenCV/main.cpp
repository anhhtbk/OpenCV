//
//  main.cpp
//  OpenCV
//
//  Created by VMio69 on 4/11/16.
//  Copyright © 2016 VMio69. All rights reserved.
//

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "MyCvtColor.hpp"

using namespace cv;
using namespace std;
using namespace myCv;

const string urlOutput = "/Users/vmio69/Desktop/OpenCV/Output/";
const string urlInput = "/Users/vmio69/Desktop/OpenCV/OpenCV/flower.jpg";


int main()
{
    Mat rgb, gray, hsv, hsl, binary, grayA;
    
    MyCvtColor mCvt = MyCvtColor();
    
    rgb = imread(urlInput, CV_LOAD_IMAGE_COLOR);
    imshow("rgb", rgb);

    mCvt.cvtGrayAllChanels(rgb, "BGR");
    
    mCvt.cvtColor(rgb, hsv, BGR2HSV);
    mCvt.cvtGrayAllChanels(hsv, "HSV");
    imwrite(urlOutput+"HSV/hsv.bmp",hsv);
    
    cv::cvtColor(rgb, hsv, CV_BGR2HSV);
    imwrite(urlOutput+"HSV/hsv_sample.bmp",hsv);
    
    mCvt.cvtColor(rgb, hsl, BGR2HSL);
    mCvt.cvtGrayAllChanels(hsl, "HLS");
    imwrite(urlOutput+"HLS/hls.bmp",hsl);
    
    cv::cvtColor(rgb, hsl, CV_BGR2HLS);
    imwrite(urlOutput+"HLS/hls_sample.bmp",hsl);
    
    cout << "done!";
    waitKey(0);
    return 0;
}