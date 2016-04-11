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


void cvtGrayAllChanels(const Mat &matFrom, string colorSpace)
{
    MyCvtColor mCvt = MyCvtColor();
    string fileName;
    string fileType = ".bmp";
    Mat image;
    
    for(int i = 0; i < 3; i++)
    {
        fileName = urlOutput + colorSpace + "/" + colorSpace.substr(i,1) + fileType;
        mCvt.splitChannel(matFrom, image, i);
        imwrite(fileName, image);
    }
    for(int i = 3; i < 6; i++)
    {
        fileName = urlOutput + colorSpace + "/gray" + colorSpace.substr(i-3,1) + fileType;
        mCvt.cvtGrayChannel(matFrom, image,i-3);
        imwrite(fileName, image);
    }
}

int main()
{
    Mat rgb, gray, hsv, hsl, binary, grayA;
    
    
    rgb = imread(urlInput, CV_LOAD_IMAGE_COLOR);
    imshow("rgb", rgb);

    cvtGrayAllChanels(rgb, "BGR");
    
    cvtColor(rgb, hsv, BGR2HSV);
    cvtGrayAllChanels(hsv, "HSV");
    imwrite(urlOutput+"HSV/hsv.bmp",hsv);
    
    cv::cvtColor(rgb, hsv, CV_BGR2HSV);
    imwrite(urlOutput+"HSV/hsv_sample.bmp",hsv);
    
    cvtColor(rgb, hsl, BGR2HSL);
    cvtGrayAllChanels(hsl, "HLS");
    imwrite(urlOutput+"HLS/hls.bmp",hsl);
    
    cv::cvtColor(rgb, hsl, CV_BGR2HLS);
    imwrite(urlOutput+"HLS/hls_sample.bmp",hsl);
    
    cout << "done!";
    waitKey(0);
    return 0;
}