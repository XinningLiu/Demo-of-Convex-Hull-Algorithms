//
//  GiftWrapping.cpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/22/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#include "GiftWrapping.hpp"

GiftWrapping::GiftWrapping(){
    pointsArray = nullptr;
    status = nullptr;
    nPoint=0;
    nVertices = 0;
    
    verticesIndex = nullptr;
}

GiftWrapping::~GiftWrapping(){
    if (verticesIndex!=nullptr) {
        delete []verticesIndex;
        verticesIndex = nullptr;
    }
}

long GiftWrapping::Reset(long n, Cart2DPoint *pt, long *s){
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
    
    long i,index,l;
    Cart2DPoint t,p;
    bool b = true;
    t = pointsArray[0];
    index = 0;
    for (i=1; i<nPoint; i++)
        if (pointsArray[i].x > t.x){
            t = pointsArray[i];
            index = i;
        }else if ((pointsArray[i].x == t.x)&&(pointsArray[i].y>t.y)){
            t = pointsArray[i];
            index = i;
        }
//    status[index] = 1;
    verticesIndex[nVertices] = index;
    nVertices ++;
    
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    p = t;
    
    i = (index+1)%nPoint;
    t = pointsArray[i];
    index = i;
    while (b) {
        for (l=1; l<nPoint; l++) {
            i = (i+1)%nPoint;
            if (status[i]==0) {
                if (t.LeftTest(p, pointsArray[i])>0) {
                    t = pointsArray[i];
                    index = i;
                }
            }
        }
        
        if (status[index]!=1) {
            
            status[index] = 1;
            
            if (index==verticesIndex[0]) {
                b = false;
            }else{
                
                verticesIndex[nVertices] = index;
                nVertices++;
                
                p = t;
                i = (index+1)%nPoint;
                t = pointsArray[i];
                index = i;
            }


            
         }
        else
            b = false;
    }
    return nVertices;
}
///////////////////////////////////////
//  For draw process
long GiftWrapping::ResetWithProcess(long n, Cart2DPoint *pt, long *s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH){
    
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
    
    long i,index,l;
    Cart2DPoint t,p;
    bool b = true;
    t = pointsArray[0];
    index = 0;
    for (i=1; i<nPoint; i++)
        if (pointsArray[i].x > t.x){
            t = pointsArray[i];
            index = i;
        }else if ((pointsArray[i].x == t.x)&&(pointsArray[i].y>t.y)){
            t = pointsArray[i];
            index = i;
        }
//    status[index] = 1;
    verticesIndex[nVertices] = index;
    nVertices ++;
    
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    p = t;
    
    i = (index+1)%nPoint;
    t = pointsArray[i];
    index = i;
    while (b) {
        for (l=1; l<nPoint; l++) {
            i = (i+1)%nPoint;

            ///////////////////////////////////////
            //  For draw process
            if (isProcess) {
                if (nVertices==2) {
                    mapVerticesIndex[step][0] = verticesIndex[0];
                    mapVerticesIndex[step][1] = verticesIndex[1];
                    mapVerticesIndex[step][2] = index;
                    mapVerticesIndex[step][3] = i;
                    step++;
                    if (step>=nStep) {
                        isProcess = false;
                    }
                }
                if (nVertices==3) {
                    mapVerticesIndex[step][0] = verticesIndex[0];
                    mapVerticesIndex[step][1] = verticesIndex[1];
                    mapVerticesIndex[step][2] = verticesIndex[2];
                    mapVerticesIndex[step][3] = index;
                    mapVerticesIndex[step][4] = i;
                    step++;
                    if (step>=nStep) {
                        isProcess = false;
                    }
                    
                }
            }
            ///////////////////////////////////////

            
            
            if (status[i]==0) {
                
                if (t.LeftTest(p, pointsArray[i])>0) {
                    t = pointsArray[i];
                    index = i;
                }
            }

        }
        

        
        if (status[index]!=1) {
            
            status[index] = 1;
            
            if (index==verticesIndex[0]) {
                b = false;
            }else{
                
                verticesIndex[nVertices] = index;
                nVertices++;
                
                p = t;
                i = (index+1)%nPoint;
                t = pointsArray[i];
                index = i;
            }
            

        }
        else
            b = false;
    }
    
    stepCH = step;
    return nVertices;
}
///////////////////////////////////////
