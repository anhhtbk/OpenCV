//
//  TemplateMatching.cpp
//  OpenCV
//
//  Created by VMio69 on 4/13/16.
//  Copyright © 2016 VMio69. All rights reserved.
//

//#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod( int, void* );

void rotateWarpImage(Mat &img, double angle, double scale);
/**
 * @function main
 */
int main()
{
    /// Load image and template
    img = imread( "/Users/vmio69/Desktop/OpenCV/1.jpg", 1 );
    templ = imread( "/Users/vmio69/Desktop/OpenCV/temp.jpg", 1 );
    
    
    /// Create windows
    namedWindow( image_window, CV_WINDOW_AUTOSIZE );
    namedWindow( result_window, CV_WINDOW_AUTOSIZE );
    
    /// Create Trackbar
    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
    
    MatchingMethod( 0, 0 );
    
    waitKey(0);
    return 0;
}


/**
 *  ronate image not crop
 */
void rotateWarpImage(Mat &img, double angle, double scale){
    Point center = Point(img.cols/2, img.rows/2);
    Mat rot(2,3,CV_32FC1);
    rot = getRotationMatrix2D(center, angle, scale);
    Rect bbox = RotatedRect(center, Size(img.cols*scale, img.rows*scale),angle).boundingRect();
    rot.at<double>(0,2) += bbox.width/2. - center.x;
    rot.at<double>(1,2) += bbox.height/2. - center.y;
    warpAffine(img, img, rot, bbox.size());
}


/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
    double angle = 0, scale = 1.;
    double matchAngle = 0.0, matchScale = 0.0;
    double curMinVal = INT32_MAX, curMaxVal = INT32_MIN;
    Point matchLoc;
    /// Source image to display
    Mat img_display, templCopy;
    img.copyTo( img_display );
    templ.copyTo(templCopy);
    Point center = Point(templ.cols/2,templ.rows/2);
    Mat rot_mat(2,3,CV_32FC1);

    
//    for (scale = 0.05; scale < 5.; scale += 0.05) {

        
        /// Create the result matrix
        int result_cols =  img.cols - templCopy.cols + 1;
        int result_rows = img.rows - templCopy.rows + 1;
        
//        if (result_cols < 0 || result_rows < 0) {
//            break;
//        }
    
        result.create( result_rows, result_cols, CV_32FC1 );
        
        /// Do the Matching and Normalize
        matchTemplate( img, templCopy, result, match_method );
        normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
        
        /// Localizing the best match with minMaxLoc
        double minVal; double maxVal; Point minLoc; Point maxLoc;
        
        
        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
        
        
        /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
        if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
        {
            if (minVal < curMinVal) {
                curMinVal = minVal;
                matchLoc = minLoc;
                matchAngle = angle;
                matchScale = scale;
            }
        }
        else
        {
            if (maxVal > curMaxVal) {
                curMaxVal = maxVal;
                matchLoc = maxLoc;
                matchAngle = angle;
                matchScale = scale;
            }
            
        }
//    }
   
    resize(templ, templCopy, Size(0,0),matchScale,matchScale);
    rot_mat = getRotationMatrix2D(center, matchAngle, matchScale);
//    warpAffine(templ, templCopy, rot_mat, templCopy.size());
    
    /// Show me what you got
    rectangle( img_display, matchLoc, Point( matchLoc.x + templCopy.cols , matchLoc.y + templCopy.rows ), Scalar::all(0), 2, 8, 0 );
   // rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    
    imshow( image_window, img_display );
   // imshow( result_window, result );
    
    return;
}

