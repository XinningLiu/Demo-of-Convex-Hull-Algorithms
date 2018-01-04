//
//  GiftWrapping.hpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/22/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef GiftWrapping_hpp
#define GiftWrapping_hpp

#include <stdio.h>
#include "Points.hpp"

class GiftWrapping{
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
    GiftWrapping();
    long Reset(long n, Cart2DPoint* p, long* s);
    long* GetVerticesIndex(){
        return verticesIndex;
    }
    ~GiftWrapping();
    
    ///////////////////////////////////////
    //  For draw process
    long ResetWithProcess(long n, Cart2DPoint* p, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH);
    ///////////////////////////////////////

};
#endif /* GiftWrapping_hpp */
