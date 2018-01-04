//
//  ConvexHull.hpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef ALGORITHMTYPE
#define ALGORITHMTYPE
typedef enum AlgorithmType{
    boundingBox     = 0,
    quickHull       = 1,
    giftWrapping    = 2,
    grahamScan      = 3,
}AlgorithmType;
#endif

#ifndef ConvexHull_hpp
#define ConvexHull_hpp

#include <stdio.h>
#include "RandomPointsArray.hpp"
#include "BoundingBoxHull.hpp"
#include "GiftWrapping.hpp"
#include "QuickHull.hpp"
#include "GrahamScanCH.hpp"

class ConvexHull {
    Cart2DPoint* pointsArray;
    long nPoint;
    long* status;
    
    Cart2DPoint* verticesArray;
    long* verticesIndex;
    long nVertices;
    
    BBConvexHull bbCH;
    GiftWrapping gwCH;
    QuickHull qhCH;
    GrahamScanCH gsCH;
    
///////////////////////////////////////
//  For draw process
    static const int nStep = 256;
    static const int nMax = 1024;
    long mapStatus[nStep][nMax];
    long mapVerticesIndex[nStep][nMax];
    int mapGroup[nStep];
    int step;
///////////////////////////////////////
    
public:
    long ResetConvexHull(RandomPointsArray& pA, AlgorithmType type);
    long ResetConvexHullBB(RandomPointsArray& pA, int type);
    Cart2DPoint* GetVertices(){
        return verticesArray;
    }
    Cart2DPoint GetVertex(long n){
        return verticesArray[n];
    }
    ConvexHull();
    ~ConvexHull();
    long ResetConvexHullWithProcess(RandomPointsArray& pA, AlgorithmType type);
    
    int CopyMap(long (*Status)[nMax], long (*VerticesIndex)[nMax], int* Group);

};

#endif /* ConvexHull_hpp */
