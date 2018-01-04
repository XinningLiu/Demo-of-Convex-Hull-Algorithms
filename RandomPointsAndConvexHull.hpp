//
//  RandomPointsAndConvexHull.hpp
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


#ifndef DATATYPE
#define DATATYPE
typedef enum DataType{
    cluster = 0,
    uniform = 1,
    circular= 2,
    input,
}DataType;
#endif



#ifndef RandomPointsAndConvexHull_hpp
#define RandomPointsAndConvexHull_hpp

#include <stdio.h>
#include "RandomPointsArray.hpp"
#include "ConvexHull.hpp"
class RandomPointsAndConvexHull {
    RandomPointsArray pointsArray;
    
    ConvexHull myCH;
    
    DataType dataType;
    AlgorithmType algorithmType;
    
    long nPoint;
    long nVertices;
    
    ///////////////////////////////////////
    //  For draw process
    static const int nStep = 256;
    static const int nMax = 1024;
    ///////////////////////////////////////

    
public:
    
    inline void GeneralizeRandomPoints(long n, DataType type){
        nPoint = n;
        pointsArray.ResetRandomPoint(n, type);
    }
    inline long GeneralizeConvexHull(AlgorithmType type){
        nVertices = myCH.ResetConvexHull(pointsArray, type);
        return nVertices;
    }
    inline long GeneralizeConvexHullBB(int type){
        nVertices = myCH.ResetConvexHullBB(pointsArray, type);
        return nVertices;
    }
    inline long GeneralizeProcess(AlgorithmType type){
        nVertices = myCH.ResetConvexHullWithProcess(pointsArray, type);
        return nVertices;
    }
    
    inline Cart2DPoint* GetPoints(){
        return pointsArray.GetPoints();
    }
    inline Cart2DPoint* GetVertices(){
        return myCH.GetVertices();
    }
    inline Cart2DPoint GetPoint(long n){
        return pointsArray.GetPoint(n);
    }
    inline Cart2DPoint GetVertex(long n){
        return myCH.GetVertex(n);
    }
    inline int CopyMap(long (*Status)[nMax], long (*VerticesIndex)[nMax], int* Group){
        return myCH.CopyMap(Status, VerticesIndex, Group);
    }
    void TimeTest();
};

#endif /* RandomPointsAndConvexHull_hpp */
