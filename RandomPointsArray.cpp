//
//  RandomPointsArray.cpp
//  RondomPoints
//
//  Created by 刘昕凝 on 2/27/16.
//  Copyright © 2016 Dolly. All rights reserved.
//


#include <stdlib.h>
#include <math.h>
#include "RandomPointsArray.hpp"

#include <iostream>
using namespace std;
//
//#ifndef MAX_RANGE
//#define MAX_RANGE 100
//#endif

#ifndef PI
#define PI 3.141592653589793
#endif

RandomPointsArray::RandomPointsArray(){
    pArray = nullptr;
    nPoints = -1;
//    GeneralizePointBase();
}

RandomPointsArray::~RandomPointsArray(){
    if (pArray!=nullptr) {
        delete []pArray;
        pArray = nullptr;
    }
}

void RandomPointsArray::ResetRandomPoint(long n, DataType type){
    nPoints = n;
    if (pArray!=nullptr) {
        delete []pArray;
    }
    pArray = new Cart2DPoint[nPoints];
    
    long i;
    switch (type) {
        case cluster:
            GeneralizeClusterPoints();
            break;
        case uniform:
            GeneralizeUniformPoints();
            break;
        case circular:
            GeneralizeCircularPoints();
            break;
        default:
            cout<<"input data:"<<endl;
            for (i=0; i<nPoints; i++) {
                cin>>pArray[i].x>>pArray[i].y;
            }
            break;
    }
}

void RandomPointsArray::GeneralizeClusterPoints(){
    long i;
    double u,v,x,y;
    
    for (i=0; i<nPoints; i++) {
        u =  ((double)arc4random())/UINT32_MAX ;
        v =  ((double)arc4random())/UINT32_MAX ;
        x = sqrt(-2* log(u))* cos(2*PI*v)/5;
        y = sqrt(-2* log(u))* sin(2*PI*v)/5;
        if (fabs(x)>1) {
            pArray[i].x = 1;
        }else
            pArray[i].x = x;
        if (fabs(y)>1) {
            pArray[i].y = 1;
        }else
            pArray[i].y = y;
        
    }
    
    
    
//    long i, j;
//    for (i=0; i<nPoints; i++) {
//        pArray[i].x = 0;
//        pArray[i].y = 0;
//        GeneralizeNormalizedParameter();
//        for (j=0; j<nBase; j++) {
//            pArray[i].x += pBase[j].x * NormalizedParameter[j];
//            pArray[i].y += pBase[j].y * NormalizedParameter[j];
//        }
//    }
//    double xmax,xmin,ymax,ymin;
//    
//    xmax = pArray[0].x;
//    xmin = pArray[0].x;
//    ymax = pArray[0].y;
//    ymin = pArray[0].y;
//    
//    for (i=1; i<nPoints; i++) {
//        if (pArray[i].x>xmax)
//            xmax = pArray[i].x;
//        if (pArray[i].x<xmin)
//            xmin = pArray[i].x;
//        if (pArray[i].y>ymax)
//            ymax = pArray[i].y;
//        if (pArray[i].y<ymin)
//            ymin = pArray[i].y;
//    }
//    for (i=0; i<nPoints; i++) {
//        pArray[i].x = (pArray[i].x-xmin)/(xmax-xmin)*2-1;
//        pArray[i].y = (pArray[i].y-ymin)/(ymax-ymin)*2-1;
//    }
    
    
    
//    long i;
//    double r,a;
//    for (i=0; i<nPoints; i++) {
//        r = ((double)arc4random())/UINT32_MAX ;
//        a = ((double)arc4random())/UINT32_MAX * 2 * PI;
//        pArray[i].x = r * cos(a);
//        pArray[i].y = r * sin(a);
//    }
    
//    long i;
//    for (i=0; i<nPoints; i++) {
//        pArray[i].x =((double)arc4random())/UINT32_MAX*2-1 ;
//        pArray[i].y =((double)arc4random())/UINT32_MAX*2-1 ;
//    }
    
    
}

//void RandomPointsArray::GeneralizePointBase(){
//    int i, halfBase = nBase/2;
//    double t=0, interval = PI/halfBase;
//    for (i = 0; i<halfBase; i++) {
//        pBase[i].x = cos(t);
//        pBase[i].y = sin(t);
//        pBase[i+halfBase].x = - pBase[i].x;
//        pBase[i+halfBase].y = - pBase[i].y;
//        t += interval;
//    }
//    
//    
//    
//}
//
//void RandomPointsArray::GeneralizeNormalizedParameter(){
//    double total=0;
//    int i;
//    for (i=0; i<nBase; i++){
//        NormalizedParameter[i]=((double)arc4random())/UINT32_MAX;
//        total+=NormalizedParameter[i];
//    }
//    for (i=0; i<nBase; i++) {
//        NormalizedParameter[i] /= total;
//    }
//}

void RandomPointsArray::GeneralizeUniformPoints(){
    double u, t, r;
    long i;
    for (i=0; i<nPoints; i++) {
        u = ((double)arc4random())/UINT32_MAX + ((double)arc4random())/UINT32_MAX;
        t = ((double)arc4random())/UINT32_MAX * 2*PI;
        if (u>1) {
            r = 2-u;
        }
        else
            r = u;
        pArray[i].x = r*cos(t);
        pArray[i].y = r*sin(t);
    }
}

void RandomPointsArray::GeneralizeCircularPoints(){
    double t;
    long i;
    for (i=0; i<nPoints; i++) {
        t = ((double)arc4random())/UINT32_MAX * 2*PI;
        //t = ((double)arc4random())/UINT32_MAX ;
        pArray[i].x = cos(t);
        pArray[i].y = sin(t);
    }
}