//
//  GrahamScanCH.cpp
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/29/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#include "GrahamScanCH.hpp"
#include "AVLTree.hpp"
#include <string>



GrahamScanCH::GrahamScanCH(){
    pointsArray = nullptr;
    status = nullptr;
    nPoint=0;
    nVertices = 0;
    
    verticesIndex = nullptr;
}

GrahamScanCH::~GrahamScanCH(){
    if (verticesIndex!=nullptr) {
        delete []verticesIndex;
        verticesIndex = nullptr;
    }
}

long GrahamScanCH::Reset(long n, Cart2DPoint *pt, long *s){
    isProcess = false;
    
//    if (nPoint!=n) {
        nPoint = n;
        if (verticesIndex!=nullptr) {
            delete []verticesIndex;
        }
        verticesIndex = new long[nPoint];
//    }
    
    pointsArray = pt;
    status = s;
    
    nVertices = 0;
    
    avlTree<PointNode> myTree;
    long i,j;
    PointNode p;
    for (i = 0; i<nPoint; i++) {
        p.point = pointsArray[i];
        p.Index = i;
        myTree.Insert(p);
    }
    
    myTree.Iterate(verticesIndex);
    nVertices = nPoint;
    
    long* verBack = new long[nPoint];
    for (i = 0; i<nPoint; i++) {
        verBack[i] = verticesIndex[nPoint-i-1];
    }
    
    i = 2;
    while (i<nVertices) {
        while ((i>1)&&(pointsArray[verticesIndex[i]].LeftTest(pointsArray[verticesIndex[i-2]], pointsArray[verticesIndex[i-1]])<0)) {
            status[verticesIndex[i-1]]=-1;

            memcpy(verticesIndex+i-1, verticesIndex+i, sizeof(long)*(nVertices-i));
            nVertices--;

            i--;
        }
        i++;
    }
    j = nPoint;
    i = 2;
    while (i<j) {
        while ((i > 1? status[verBack[i-1]]==0 :false)||((i>1)&&(pointsArray[verBack[i]].LeftTest(pointsArray[verBack[i-2]], pointsArray[verBack[i-1]])<0))) {

            memcpy(verBack+i-1, verBack+i, sizeof(long)*(j-i));
            j--;
            i--;
        }
        i++;
    }
    
    for (i=1; i<j-1; i++) {
        verticesIndex[nVertices] = verBack[i];
        nVertices++;
    }
    
    return nVertices;
}



///////////////////////////////////////
//  For draw process
long GrahamScanCH::ResetWithProcess(long n, Cart2DPoint *pt, long *s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH){
    
    isProcess = true;
    this->mapGroup = mapGroup;
    this->mapStatus = mapStatus;
    this->mapVerticesIndex = mapVerticesIndex;
    
    
//    if (nPoint!=n) {
        nPoint = n;
        if (verticesIndex!=nullptr) {
            delete []verticesIndex;
        }
        verticesIndex = new long[nPoint];
//    }
    
    pointsArray = pt;
    status = s;
    
    nVertices = 0;
    
    avlTree<PointNode> myTree;
    long i,j;
    PointNode p;
    for (i = 0; i<nPoint; i++) {
        p.point = pointsArray[i];
        p.Index = i;
        myTree.Insert(p);
    }
    
    myTree.Iterate(verticesIndex);
    nVertices = nPoint;
    
    
    
    long* verBack = new long[nPoint];
    for (i = 0; i<nPoint; i++) {
        verBack[i] = verticesIndex[nPoint-i-1];
    }
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
        memcpy(mapVerticesIndex[step], verticesIndex, sizeof(long)*nPoint);
        mapGroup[step] = (int)nPoint;
        step++;
    }
    ///////////////////////////////////////

    
    i = 2;
    while (i<nVertices) {
        while ((i>1)&&(pointsArray[verticesIndex[i]].LeftTest(pointsArray[verticesIndex[i-2]], pointsArray[verticesIndex[i-1]])<0)) {
            status[verticesIndex[i-1]]=-1;
            
            memcpy(verticesIndex+i-1, verticesIndex+i, sizeof(long)*(nVertices-i));
            nVertices--;
            
            i--;
            ///////////////////////////////////////
            //  For draw process
            if (isProcess) {
                memcpy(mapVerticesIndex[step], verticesIndex, sizeof(long)*nVertices);
                mapGroup[step] = (int)nVertices;
                step++;
                if (step>=nStep) {
                    isProcess = false;
                }
            }
            ///////////////////////////////////////
        }
        i++;
    }
    j = nPoint;
    i = 2;
    while (i<j) {
        while ((i > 1? status[verBack[i-1]]==0 :false)||((i>1)&&(pointsArray[verBack[i]].LeftTest(pointsArray[verBack[i-2]], pointsArray[verBack[i-1]])<0))) {
            
            memcpy(verBack+i-1, verBack+i, sizeof(long)*(j-i));
            j--;
            i--;
            ///////////////////////////////////////
            //  For draw process
            if (isProcess) {

                memcpy(mapVerticesIndex[step], verticesIndex, sizeof(long)*nVertices);
                memcpy(mapVerticesIndex[step]+nVertices, verBack, sizeof(long)*j);
                mapGroup[step] = (int)(nVertices+j);
                step++;
                if (step>=nStep) {
                    isProcess = false;
                }
            }
            ///////////////////////////////////////

        }
        i++;
    }
    
    for (i=1; i<j; i++) {
        verticesIndex[nVertices] = verBack[i];
        nVertices++;
    }


    stepCH = step;
    return nVertices;
}
///////////////////////////////////////
