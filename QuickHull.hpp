//
//  QuickHull.hpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/22/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef QuickHull_hpp
#define QuickHull_hpp

#include <stdio.h>
#include "BasicStructure.hpp"
#include "Points.hpp"

class QuickHull{
    Cart2DPoint* pointsArray;
    long* status;
    //long* indexgroup;
    long nPoint;
    
    long nVertices;
    
    long* verticesIndex;
    
    LongDC upHull;
    LongDC downHull;
    
    ///////////////////////////////////////
    //  For draw process
    static const int nStep = 256;
    static const int nMax = 1024;
    long (*mapStatus)[nMax];
    long (*mapVerticesIndex)[nMax];
    int* mapGroup;
    int step;
    bool b;
    bool isProcess;
    ///////////////////////////////////////
    
    
public:
    QuickHull();
    long Reset(long n, Cart2DPoint* pt, long* s);
    long ResetM(long n, Cart2DPoint* pt, long* s);
    inline long* GetVerticesIndex(){
        return verticesIndex;
    }
    
    ~QuickHull();
    void QHull(int &flag, long &length, LongDC* start, LongDC* end, long groupflag);
    
    void QHullM(LongDC* start, LongDC* end, long* indexG, long length);
    
    ///////////////////////////////////////
    //  For draw process
    long ResetWithProcess(long n, Cart2DPoint* pt, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH);
    long ResetWithProcessM(long n, Cart2DPoint* pt, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH);
    ///////////////////////////////////////

    
};


#endif /* QuickHull_hpp */
