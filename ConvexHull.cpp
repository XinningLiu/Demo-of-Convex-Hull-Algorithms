//
//  ConvexHull.cpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#include "ConvexHull.hpp"
#include <string.h>

ConvexHull::ConvexHull(){
    pointsArray = nullptr;
    nPoint = -1;
    status = nullptr;
    
    verticesArray = nullptr;
    verticesIndex = nullptr;
    nVertices = -1;
}

ConvexHull::~ConvexHull(){
    if (pointsArray!=nullptr) {
        pointsArray=nullptr;
    }
    if (status!=nullptr) {
        delete []status;
        status = nullptr;
    }
    if (verticesArray!=nullptr) {
        verticesArray = nullptr;
    }
    
}

long ConvexHull::ResetConvexHull(RandomPointsArray& pA, AlgorithmType type){
    
    pointsArray = pA.GetPoints();
    nPoint = pA.GetNPoints();
    if (status!=nullptr) {
        delete []status;
        status = nullptr;
    }
    status = new long[nPoint];
    memset(status, 0, sizeof(long)*nPoint);
    
    switch (type) {
        case boundingBox:
            nVertices=bbCH.ResetM(nPoint, pointsArray, status);
            verticesIndex = bbCH.GetVerticesIndex();
            break;
        case quickHull:
            //nVertices=qhCH.Reset(nPoint, pointsArray, status);
            nVertices=qhCH.ResetM(nPoint, pointsArray, status);
            verticesIndex = qhCH.GetVerticesIndex();
            break;
        case giftWrapping:
            nVertices=gwCH.Reset(nPoint, pointsArray, status);
            verticesIndex = gwCH.GetVerticesIndex();
            break;
        case grahamScan:
            nVertices=gsCH.Reset(nPoint, pointsArray, status);
            verticesIndex = gsCH.GetVerticesIndex();
            break;
        default:
            break;
    }
    long i;
    if (verticesArray!=nullptr) {
        delete []verticesArray;
        verticesArray=nullptr;
    }
    verticesArray = new Cart2DPoint[nVertices];
    for (i=0; i<nVertices; i++) {
        verticesArray[i] = pointsArray[verticesIndex[i]];
    }
    return nVertices;
}
///////////////////////////////////////
//  For draw process
long ConvexHull::ResetConvexHullWithProcess(RandomPointsArray& pA, AlgorithmType type){
        
    pointsArray = pA.GetPoints();
    nPoint = pA.GetNPoints();
    if (status!=nullptr) {
        delete []status;
        status = nullptr;
    }
    status = new long[nPoint];
    memset(status, 0, sizeof(long)*nPoint);
    
    
    memset(mapStatus, -10, sizeof(long)*nStep*nMax);
    memset(mapVerticesIndex, -1, sizeof(long)*nStep*nMax);
    memset(mapGroup, -1, sizeof(int)*nStep);
    
    switch (type) {
        case boundingBox:
            nVertices = bbCH.ResetWithProcess(nPoint, pointsArray, status, mapStatus, mapVerticesIndex, mapGroup, step);
            verticesIndex = bbCH.GetVerticesIndex();
            break;
        case quickHull:
            nVertices=qhCH.ResetWithProcessM(nPoint, pointsArray, status, mapStatus, mapVerticesIndex, mapGroup, step);
            verticesIndex = qhCH.GetVerticesIndex();
            break;
        case giftWrapping:
            nVertices=gwCH.ResetWithProcess(nPoint, pointsArray, status, mapStatus, mapVerticesIndex, mapGroup, step);
            verticesIndex = gwCH.GetVerticesIndex();
            break;
        case grahamScan:
            nVertices=gsCH.ResetWithProcess(nPoint, pointsArray, status, mapStatus, mapVerticesIndex, mapGroup, step);
            verticesIndex = gsCH.GetVerticesIndex();
            break;
        default:
            break;
    }
    long i;
    if (verticesArray!=nullptr) {
        delete []verticesArray;
    }
    verticesArray = new Cart2DPoint[nVertices];
    for (i=0; i<nVertices; i++) {
        verticesArray[i] = pointsArray[verticesIndex[i]];
    }
    return nVertices;
}
int ConvexHull::CopyMap(long (*Status)[nMax], long (*VerticesIndex)[nMax], int* Group){
    memcpy(Status, mapStatus, sizeof(long)*nStep*nMax);
    memcpy(VerticesIndex, mapVerticesIndex, sizeof(long)*nStep*nMax);
    memcpy(Group, mapGroup, sizeof(int)*nStep);
    return step;
}
///////////////////////////////////////




long ConvexHull::ResetConvexHullBB(RandomPointsArray& pA, int type){
    pointsArray = pA.GetPoints();
    nPoint = pA.GetNPoints();
    if (status!=nullptr) {
        delete []status;
        status = nullptr;
    }
    status = new long[nPoint];
    memset(status, 0, sizeof(long)*nPoint);
    
    switch (type) {
        case 1:
            nVertices=bbCH.ResetChain(nPoint, pointsArray, status);
            verticesIndex = bbCH.GetVerticesIndex();
            break;
        case 2:
            nVertices=bbCH.ResetAVL(nPoint, pointsArray, status);
            verticesIndex = bbCH.GetVerticesIndex();
            break;
        case 3:
            nVertices=bbCH.ResetAVLM(nPoint, pointsArray, status);
            verticesIndex = bbCH.GetVerticesIndex();
            break;
        default:
            break;
    }
    long i;
    if (verticesArray!=nullptr) {
        delete []verticesArray;
        verticesArray=nullptr;
    }
    verticesArray = new Cart2DPoint[nVertices];
    for (i=0; i<nVertices; i++) {
        verticesArray[i] = pointsArray[verticesIndex[i]];
    }
    return nVertices;
}