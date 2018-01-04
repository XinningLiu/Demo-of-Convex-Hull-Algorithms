//
//  GrahamScanCH.hpp
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/29/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef GrahamScanCH_hpp
#define GrahamScanCH_hpp

#include <stdio.h>
#include "Points.hpp"

class GrahamScanCH{
    Cart2DPoint* pointsArray;
    long* status;
    long nPoint;
    
    long nVertices;
    long* verticesIndex;
    
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
    GrahamScanCH();
    long Reset(long n, Cart2DPoint* p, long* s);
    long* GetVerticesIndex(){
        return verticesIndex;
    }
    ~GrahamScanCH();
    
    ///////////////////////////////////////
    //  For draw process
    long ResetWithProcess(long n, Cart2DPoint* p, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH);
    ///////////////////////////////////////
    
};



#endif /* GrahamScanCH_hpp */
