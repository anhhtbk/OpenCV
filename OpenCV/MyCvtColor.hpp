//
//  MyCvtColor.hpp
//  OpenCV
//
//  Created by VMio69 on 4/11/16.
//  Copyright © 2016 VMio69. All rights reserved.
//

#ifndef MyCvtColor_hpp
#define MyCvtColor_hpp

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

namespace myCv {
    enum
    {
        BGR2HSV = 0,
        BGR2HSL = 1
    };
    class MyCvtColor
    {
    public:
        MyCvtColor(void);
        
        int avg3(int a1, int a2, int a3);
        
        void cvtGray2Binary(const Mat &matGray, Mat &matBinary, int value);
        
        void cvtGrayAvg(const Mat &matFrom, Mat &matTo);
        
        void cvtColor(const Mat &matFrom, Mat &matTo, int code);
        
        void splitChannel(const Mat &matFrom, Mat &matTo, int channel);
        
        void cvtGrayChannel(const Mat &matFrom, Mat &matTo, int color);
        
        void cvtGray(const Mat &matFrom, Mat &matTo, double c1 = 1, double c2 = 1, double c3 = 1);
             
        ~MyCvtColor(void);
    };
    
}

#endif /* MyCvtColor_hpp */
