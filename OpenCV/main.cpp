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
#include "sys/time.h"

using namespace cv;
using namespace std;
using namespace myCv;

const string urlOutput = "/Users/vmio69/Desktop/OpenCV/Output/";
const string urlInput = "/Users/vmio69/Desktop/OpenCV/flower.jpg";

static MyCvtColor mCvt1 = MyCvtColor();


void cvtGrayAllChanels(const Mat &matFrom, string colorSpace)
{
    string fileName;
    string fileType = ".bmp";
    Mat image;
    clock_t c_start, c_end;
    for(int i = 0; i < 3; i++)
    {
        fileName = urlOutput + colorSpace + "/" + colorSpace.substr(i,1) + fileType;
        
        c_start = clock();
        mCvt1.splitChannel(matFrom, image, i);
        c_end = clock();
        cout << "Run time Split: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n";
        
        imwrite(fileName, image);
    }
    for(int i = 3; i < 6; i++)
    {
        fileName = urlOutput + colorSpace + "/gray" + colorSpace.substr(i-3,1) + fileType;
        
        c_start = clock();
        mCvt1.cvtGrayChannel(matFrom, image,i-3);
        c_end = clock();
        cout << "Run time Gray: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n";

        imwrite(fileName, image);
    }
    c_start = clock();
    mCvt1.cvtGray(matFrom, image);
    c_end = clock();
    cout << "Run time Gray all: " << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n";
    
    imwrite(urlOutput + colorSpace + "/grayAll.png", image);
}

int main()
{
    Mat rgb, gray, hsv, hsl, binary, grayA;
    
    MyCvtColor mCvt = MyCvtColor();
    
    rgb = imread(urlInput, CV_LOAD_IMAGE_COLOR);
    imshow("rgb", rgb);

    cvtGrayAllChanels(rgb, "BGR");
    
    mCvt.cvtColor(rgb, hsv, BGR2HSV);
    cvtGrayAllChanels(hsv, "HSV");
    imwrite(urlOutput+"HSV/hsv.bmp",hsv);
    
    cv::cvtColor(rgb, hsv, CV_BGR2HSV);
    imwrite(urlOutput+"HSV/hsv_sample.bmp",hsv);
    
    mCvt.cvtColor(rgb, hsl, BGR2HSL);
    cvtGrayAllChanels(hsl, "HLS");
    imwrite(urlOutput+"HLS/hls.bmp",hsl);
    
    cv::cvtColor(rgb, hsl, CV_BGR2HLS);
    imwrite(urlOutput+"HLS/hls_sample.bmp",hsl);
    
    cout << "done!";
    waitKey(0);
    return 0;
}