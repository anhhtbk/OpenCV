//
//  MyCvtColor.cpp
//  OpenCV
//
//  Created by VMio69 on 4/11/16.
//  Copyright © 2016 VMio69. All rights reserved.
//

#include "MyCvtColor.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace myCv;
using namespace std;

const string urlOutput = "/Users/vmio69/Desktop/OpenCV/Output/";

MyCvtColor::MyCvtColor(void){
    
}

int MyCvtColor::avg3(int a1, int a2, int a3)
{
    return (a1+a2+a3)/3;
}

void MyCvtColor::cvtGray2Binary(const Mat &matGray, Mat &matBinary, int value)
{
    CvSize s = matGray.size();
    
    matBinary = cvCreateMat(s.height, s.width, CV_8UC1);
    int w = s.width;
    int h = s.height;
    
    if(matGray.isContinuous() && matBinary.isContinuous())
    {
        int size = w*h;
        const uchar *gray = matGray.ptr(0);
        uchar *binary = matBinary.ptr(0);
        for(int i = 0; i < size; i++)
        {
            if(gray[i] > value)
            {
                binary[i] = 255;
            }
            else
            {
                binary[i] = 0;
            }
        }
    }
    else
    {
        for(int i = 0; i < h; i++)
        {
            const uchar *gray = matGray.ptr(i);
            uchar *binary = matBinary.ptr(i);
            for(int j = 0; j < w; j++)
            {
                if(gray[j] > value)
                    binary[i] = 255;
                else
                    binary[i] = 0;
            }
        }
    }
    
}

void MyCvtColor::cvtGrayAvg(const Mat &matFrom, Mat &matTo)
{
    CvSize s = matFrom.size();
    
    matTo = cvCreateMat(s.height, s.width, CV_8UC1);
    int w = s.width;
    int h = s.height;
    
    if(matFrom.isContinuous() && matTo.isContinuous())
    {
        int size = w*h;
        const uchar *from = matFrom.ptr(0);
        uchar *to = matTo.ptr(0);
        for(int i = 0; i < size; i+=3)
        {
            to[i] = avg3(from[i],from[i+1],from[i+2]);
        }
    }
    else
    {
        for(int i = 0; i < h; i++)
        {
            const uchar *from = matFrom.ptr(i);
            uchar *to = matTo.ptr(i);
            for(int j = 0; j < w; j+=3)
            {
                to[j] = avg3(from[j], from[j+1], from[j+2]);
            }
        }
    }
}

void MyCvtColor::cvtColor(const Mat &matFrom, Mat &matTo, int code)
{
    CvSize s = matFrom.size();
    
    matTo = cvCreateMat(s.height, s.width, CV_8UC3);
    int w = s.width;
    int h = s.height;
    double  S, V, L;
    double R, G, B, M, m, C, H=0;
    int channels = matFrom.channels();
    switch(code)
    {
        case BGR2HSV:
            if(matFrom.isContinuous() && matTo.isContinuous())
            {
                int size;
                uchar *to = matTo.ptr(0);
                const uchar *from = matFrom.ptr(0);
                size = w*h*channels;
                for(int i = 0; i < size; i += channels)
                {
                    B = from[i]/255.;
                    G = from[i+1]/255.;
                    R = from[i+2]/255.;
                    M = max(max(R,G),B);
                    m = min(min(R,G),B);
                    C = M - m;
                    V = M;
                    if(C == 0)
                    {
                        H = 0;
                        S = 0;
                    }
                    else
                    {
                        if(M == R) H = fmod((G-B)/C,6);
                        if(M == G) H = (B-R)/C+2;
                        if(M == B) H = (R-G)/C+4;
                        
                        S = C/V;
                    }
                    
                    H = H*255/6;
                    S = S*255;
                    V = V*255;
                    to[i] = H;
                    to[i+1] = S;
                    to[i+2] = V;
                    
                }
            }
            else
            {
                for(int i = 0; i < h; i++)
                    for(int j = 0; j < w; j ++)
                    {
                        R = matFrom.ptr<Vec3b>(i)[j][2]/255.;
                        G = matFrom.ptr<Vec3b>(i)[j][1]/255.;
                        B = matFrom.ptr<Vec3b>(i)[j][0]/255.;
                        M = max(max(R,G),B);
                        m = min(min(R,G),B);
                        C = M - m;
                        V = M;
                        if(C == 0)
                        {
                            H = 0;
                            S = 0;
                        }
                        else
                        {
                            if(M == R) H = fmod((G-B)/C,6);
                            if(M == G) H = (B-R)/C+2;
                            if(M == B) H = (R-G)/C+4;
                            
                            S = C/V;
                        }
                        
                        H = H*255/6;
                        S = S*255;
                        V = V*255;
                        matTo.ptr<Vec3b>(i)[j][0] = H;
                        matTo.ptr<Vec3b>(i)[j][1] = S;
                        matTo.ptr<Vec3b>(i)[j][2] = V;
                    }
            }
            break;
        case BGR2HSL:
            for(int i = 0; i < h; i++)
                for(int j = 0; j < w; j ++)
                {
                    R = matFrom.ptr<Vec3b>(i)[j][2]/255.;
                    G = matFrom.ptr<Vec3b>(i)[j][1]/255.;
                    B = matFrom.ptr<Vec3b>(i)[j][0]/255.;
                    M = max(max(R,G),B);
                    m = min(min(R,G),B);
                    C = M - m;
                    L = (M+m)/2;
                    if(C == 0)
                    {
                        H = 0;
                        S = 0;
                    }
                    else
                    {
                        if(M == R)
                            H = fmod((G-B)/C,6);
                        if(M == G)
                            H = (B-R)/C+2;
                        if(M == B) 
                            H = (R-G)/C+4;
                        
                        S = C/(1-abs(2*L-1));
                    }
                    H = H*255/6;
                    S = S*255;
                    L = L*255;
                    matTo.ptr<Vec3b>(i)[j][0] = H;
                    matTo.ptr<Vec3b>(i)[j][1] = L;
                    matTo.ptr<Vec3b>(i)[j][2] = S;
                }
            break;
        default:
            break;
    }
    
}

void MyCvtColor::splitChannel(const Mat &matFrom, Mat &matTo, int channel)
{
    CvSize s = matFrom.size();
    
    matTo = cvCreateMat(s.height, s.width, CV_8UC3);
    int w = s.width;
    int h = s.height;
    matTo = Mat::zeros(h,w,CV_8UC3);
    if(matFrom.isContinuous() && matTo.isContinuous())
    {
        int size;
        uchar *to = matTo.ptr(0);
        const uchar *from = matFrom.ptr(0);
        size = w*h*3;
        for(int i = channel; i < size; i+=3)
        {
            to[i] = from[i];
        }
    }
    else
    {
        for(int i = 0; i < h; i++)
        {
            const uchar *from = matFrom.ptr(i);
            uchar *to = matTo.ptr(i);
            for(int j = channel; j < w; j+=3)
            {
                to[j] = from[j]; 
            }
        }
    }
    
}

void MyCvtColor::cvtGrayChannel(const Mat &matFrom, Mat &matTo, int color)
{
    CvSize s = matFrom.size();
    
    matTo = cvCreateMat(s.height, s.width, CV_8UC1);
    int w = s.width;
    int h = s.height;
    if(matFrom.isContinuous() && matTo.isContinuous())
    {
        int size = w*h;
        uchar *to = matTo.ptr(0);
        const uchar *from = matFrom.ptr(0);
        
        for(int i = color; i < size; i++)
        {
            to[i] = from[3*i+color];
        }
    }
    else
    {
        for(int i = 0; i < h; i++)
        {
            const uchar *from = matFrom.ptr(i);
            uchar *to = matTo.ptr(i);
            for(int j = 0; j < w; j++)
            {
                to[j] = from[3*j+color]; 
            }
        }
    }
}

void MyCvtColor::cvtGray(const Mat &matFrom, Mat &matTo, double c1, double c2, double c3)
{
    CvSize s = matFrom.size();
    
    matTo = cvCreateMat(s.height, s.width, CV_8UC1);
    int w = s.width;
    int h = s.height;
    if(matFrom.isContinuous() && matTo.isContinuous())
    {
        int size = w*h;
        uchar *to = matTo.ptr(0);
        const uchar *from = matFrom.ptr(0);
        
        for(int i = 0; i < size; i++)
        {
            to[i] = (from[3*i+0]*c1 + from[3*i+1]*c2 + from[3*i+2]*c3)/(c1+c2+c3);
        }
    }
    else
    {
        for(int i = 0; i < h; i++)
        {
            const uchar *from = matFrom.ptr(i);
            uchar *to = matTo.ptr(i);
            for(int j = 0; j < w; j++)
            {
                to[j] = (from[3*j+0]*c1 + from[3*j+1]*c2 + from[3*j+2]*c3)/(c1+c2+c3);
            }
        }
    }
}

MyCvtColor::~MyCvtColor(void){
    
}