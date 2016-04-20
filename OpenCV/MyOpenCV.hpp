//
//  MyCvtColor.hpp
//  OpenCV
//
//  Created by VMio69 on 4/11/16.
//  Copyright © 2016 VMio69. All rights reserved.
//

#ifndef MyOpenCV_hpp
#define MyOpenCV_hpp

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

namespace myCv {
    enum
    {
        BGR2HSV = 0,
        BGR2HSL = 1,
        MCV_SQDIFF = 2,
        MCV_SQDIFF_NORMED = 3
    };
    class MyOpenCV
    {
    public:
        MyOpenCV(void);
        
        int avg3(int a1, int a2, int a3);
        
        void cvtGray2Binary(const Mat &matGray, Mat &matBinary, int value);
        
        void cvtGrayAvg(const Mat &matFrom, Mat &matTo);
        
        void cvtColor(const Mat &matFrom, Mat &matTo, int code);
        
        void splitChannel(const Mat &matFrom, Mat &matTo, int channel);
        
        void cvtGrayChannel(const Mat &matFrom, Mat &matTo, int color);
        
        void cvtGray(const Mat &matFrom, Mat &matTo, double c1 = 1, double c2 = 1, double c3 = 1);
        
        void cvtContrast(const Mat &matFrom, Mat &matTo, double alpha, double beta);
        
        void matchTemplate(const Mat &workImage, const Mat &pattern, int method, double &score, Point &position);
        
        void drawResultMatching(const Mat &workImage, const Mat &pattern, int method);
        
        void getResultMatching(const Mat &resultMat, bool isMin, double &score, Point &position);
        
        ~MyOpenCV(void);
    };
    
}

#endif /* MyCvtColor_hpp */
