//
//  QuickHull.cpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/22/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//


////////////
//  http://www.qhull.org/html/index.htm
//  need to modify
//  On a 600 MHz Pentium 3, Qhull computes the 2-d convex hull of 300,000 cocircular points in 11 seconds.



#include "QuickHull.hpp"

///////////////////////////////////////
//  For draw process
#include <string.h>
///////////////////////////////////////


QuickHull::QuickHull(){
    pointsArray = nullptr;
    status = nullptr;
    
    nPoint = 0;
    nVertices = 0;
    verticesIndex = nullptr;
}
QuickHull::~QuickHull(){
    if (verticesIndex!=nullptr) {
        delete []verticesIndex;
        verticesIndex = nullptr;
    }
    if (upHull.son!=nullptr) {
        delete upHull.son;
        upHull.son = nullptr;
    }
    
    if (downHull.son !=nullptr) {
        delete downHull.son;
        downHull.son = nullptr;
    }
}

long QuickHull::Reset(long n, Cart2DPoint *pt, long *s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    if (upHull.son!=nullptr) {
        delete upHull.son;
        upHull.son = nullptr;
    }
    
    if (downHull.son !=nullptr) {
        delete downHull.son;
        downHull.son = nullptr;
    }
    
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
    
    long i;
    Cart2DPoint rm,lm;
    long rmI = 0, lmI = 0;
    rm = pointsArray[0];
    lm = pointsArray[0];
    
    for (i=1; i<nPoint; i++) {
        if ((pointsArray[i].x>rm.x)||((pointsArray[i].x==rm.x)&&(pointsArray[i].y>rm.y))){
            rm = pointsArray[i];
            rmI = i;
        }
        if ((pointsArray[i].x<lm.x)||((pointsArray[i].x==lm.x)&&(pointsArray[i].y<lm.y))){
            lm = pointsArray[i];
            lmI = i;
        }
    }
    LongDC *u1,*u2,*d1,*d2;

    u2=upHull.AddPoint(rmI);
    u1=upHull.AddPoint(lmI);
    d2=downHull.AddPoint(lmI);
    d1=downHull.AddPoint(rmI);
    
    
    
    for (i=0; i<nPoint; i++) {
        if (pointsArray[i].LeftTest(lm, rm)>0) {
            status[i] = 1;
        }
        if (pointsArray[i].LeftTest(rm, lm)>0) {
            status[i] = 2;
        }
    }
    int flag = 2;
    long ul = 1, dl = 1;
    
    QHull(flag, ul, u1, u2, 1);
    
    
    
    QHull(flag, dl, d1, d2, 2);
    
    for (i=0; i<ul; i++) {
        verticesIndex[nVertices] = u2->index;
        u2 = u2->father;
        nVertices++;
    }
    for (i=0; i<dl; i++) {
        verticesIndex[nVertices] = d2->index;
        d2 = d2->father;
        nVertices++;
    }
    
    return nVertices;
}
void QuickHull::QHull(int &flag, long &length, LongDC* start, LongDC* end, long groupflag){
    long i,index=-1;
    double dist=-1,t;
    LongDC* p;
    int s2,s3;
    int flagD;
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        mapGroup[step] = (int)groupflag;
//        memcpy(mapStatus[step], status, sizeof(int)*nPoint);
        i=0;
        p = upHull.son;
        do{
            mapVerticesIndex[step][i] = p->index;
            i++;
            p = p->son;
        }while(p!=nullptr);
        p = downHull.son;
        do{
            mapVerticesIndex[step][i] = p->index;
            i++;
            p = p->son;
        }while(p!=nullptr);
        step++;
        if (step>=nStep) {
            isProcess = false;
        }
    }

    ///////////////////////////////////////
    
    
    
    
    for (i=0; i<nPoint; i++) {
        if (status[i]==groupflag) {
            t = pointsArray[i].Distance(pointsArray[start->index],pointsArray[end->index]);
            if (t >dist) {
                dist = t;
                index = i;
            }
        }
    }
    if (index == -1) {
        return;
    }
    p=start->AddPoint(index);
    length ++;
    flagD = flag;
    for (i=0; i<nPoint; i++) {
        if (status[i]==groupflag) {
            s2 = pointsArray[i].LeftTest(pointsArray[start->index], pointsArray[p->index]);
            s3 = pointsArray[i].LeftTest(pointsArray[p->index], pointsArray[end->index]);
            if (s2>0) {
                status[i] = flagD + 1;
            }
            if (s3>0) {
                status[i] = flagD + 2;
            }
        }
    }
    flag +=2;
    
    QHull(flag, length, start, p, flagD+1);
    QHull(flag, length, p, end, flagD+2);
}


///////////////////////////////////////
//  For draw process
long QuickHull::ResetWithProcess(long n, Cart2DPoint* pt, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH){
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
    
    if (upHull.son!=nullptr) {
        delete upHull.son;
        upHull.son = nullptr;
    }
    
    if (downHull.son !=nullptr) {
        delete downHull.son;
        downHull.son = nullptr;
    }
    
    pointsArray = pt;
    status = s;
    
    nVertices = 0;
    
    long i;
    Cart2DPoint rm,lm;
    long rmI = 0, lmI = 0;
    rm = pointsArray[0];
    lm = pointsArray[0];
    
    for (i=1; i<nPoint; i++) {
        if ((pointsArray[i].x>rm.x)||((pointsArray[i].x==rm.x)&&(pointsArray[i].y>rm.y))){
            rm = pointsArray[i];
            rmI = i;
        }
        if ((pointsArray[i].x<lm.x)||((pointsArray[i].x==lm.x)&&(pointsArray[i].y<lm.y))){
            lm = pointsArray[i];
            lmI = i;
        }
    }
    LongDC *u1,*u2,*d1,*d2;
    
    u2=upHull.AddPoint(rmI);
    u1=upHull.AddPoint(lmI);
    d2=downHull.AddPoint(lmI);
    d1=downHull.AddPoint(rmI);
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
        b = true;
    }
    ///////////////////////////////////////
    
    
    for (i=0; i<nPoint; i++) {
        if (pointsArray[i].LeftTest(lm, rm)>0) {
            status[i] = 1;
        }
        if (pointsArray[i].LeftTest(rm, lm)>0) {
            status[i] = 2;
        }
    }
    int flag = 2;
    long ul = 1, dl = 1;
    
    QHull(flag, ul, u1, u2, 1);
    
//    ///////////////////////////////////////
//    //  For draw process
//    if (isProcess) {
//        b = false;
//        isProcess = false;
//    }
//    ///////////////////////////////////////
    
    
    QHull(flag, dl, d1, d2, 2);
    
    for (i=0; i<ul; i++) {
        verticesIndex[nVertices] = u2->index;
        u2 = u2->father;
        nVertices++;
    }
    for (i=0; i<dl; i++) {
        verticesIndex[nVertices] = d2->index;
        d2 = d2->father;
        nVertices++;
    }
    
    memcpy(mapStatus[0], status, sizeof(long)*nPoint);
    stepCH = step;
    return nVertices;
}
///////////////////////////////////////


long QuickHull::ResetM(long n, Cart2DPoint* pt, long* s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    if (upHull.son!=nullptr) {
        delete upHull.son;
        upHull.son = nullptr;
    }
    
    if (downHull.son !=nullptr) {
        delete downHull.son;
        downHull.son = nullptr;
    }
    
    
    nPoint = n;
    if (verticesIndex!=nullptr) {
        delete []verticesIndex;
    }
    verticesIndex = new long[nPoint];
    
//    if (indexgroup) {
//        delete []indexgroup;
//    }
//    indexgroup = new long[nPoint];
    
    pointsArray = pt;
    status = s;
    
    

    long i;
    Cart2DPoint rm,lm;
    long rmI = 0, lmI = 0;
    rm = pointsArray[0];
    lm = pointsArray[0];
    
    for (i=1; i<nPoint; i++) {
        if ((pointsArray[i].x>rm.x)||((pointsArray[i].x==rm.x)&&(pointsArray[i].y>rm.y))){
            rm = pointsArray[i];
            rmI = i;
            continue;
        }
        if ((pointsArray[i].x<lm.x)||((pointsArray[i].x==lm.x)&&(pointsArray[i].y<lm.y))){
            lm = pointsArray[i];
            lmI = i;
            continue;
        }
    }
    LongDC *u1,*u2,*d1,*d2;
    
    u2=upHull.AddPoint(rmI);
    u1=upHull.AddPoint(lmI);
    d2=downHull.AddPoint(lmI);
    d1=downHull.AddPoint(rmI);
    
    long ul = 0, dl = 0, dp = nPoint;
    
    
    for (i=0; i<nPoint; i++) {
        if (pointsArray[i].LeftTest(lm, rm)>0) {
            status[ul] = i;
            ul++;
            continue;
        }
        if (pointsArray[i].LeftTest(rm, lm)>0) {
            dp--;
            status[dp] = i;
            dl++;
            continue;
        }
    }
    if (ul>0) {
        QHullM(u1, u2, status, ul);
    }
    if (dl>0) {
        QHullM(d1, d2, status+dp, dl);
    }
    
    nVertices = 0;
    LongDC *p;
    p = u2;
    while (p!=u1) {
        verticesIndex[nVertices] = p->index;
        nVertices++;
        p = p->father;
    }
    
    p = d2;
    while (p!=d1) {
        verticesIndex[nVertices] = p->index;
        nVertices++;
        p = p->father;
    }

    
    return nVertices;
}

void QuickHull::QHullM(LongDC* start, LongDC* end, long* indexG, long length){
    long i,index=-1;

    double dist=-1,t;
    LongDC* p,*q;


    
    
    
    for (i=0; i<length; i++) {
        t = pointsArray[indexG[i]].Distance(pointsArray[start->index],pointsArray[end->index]);
        if (t >dist) {
            dist = t;
            index = indexG[i];
        }
    }
    if (index == -1) {
        return;
    }
    p=start->AddPoint(index);
    
    long rl = 0, ll = 0, rp = length, tp = indexG[0], u = 1, d = length-1, x;
    
    for (i=0; i<length; i++) {
        if (pointsArray[tp].LeftTest(pointsArray[start->index], pointsArray[p->index])>0) {
            x = indexG[u];
            indexG[ll] = tp;
            ll++;
            tp = x;
            u++;
            continue;
        }
        if (pointsArray[tp].LeftTest(pointsArray[p->index], pointsArray[end->index])>0) {
            rp--;
            x = indexG[d];
            indexG[rp] = tp;
            rl++;
            tp = x;
            d--;
            continue;
        }
        if (u<length) {
            tp = indexG[u];
            u++;
        }

    }
    ///////////////////////////////////////
    //  For draw process
   
    if (isProcess) {
        for (i = ll; i<rp; i++) {
            indexG[i] = -1;
        }
        
        for (i = 0; i<nPoint; i++) {
            if (status[i]!=-1) {
                mapStatus[step][status[i]] = 1;
            }
        }
        
        i=0;
        q = upHull.son;
        do{
            mapVerticesIndex[step][i] = q->index;
            i++;
            q = q->son;
        }while(q!=nullptr);
        q = downHull.son;
        do{
            mapVerticesIndex[step][i] = q->index;
            i++;
            q = q->son;
        }while(q!=nullptr);
        
        
        step++;
        if (step>=nStep) {
            isProcess = false;
        }
        
    }
    ////////////////////////////////////
    
    
    if (ll>0) {
        QHullM(start, p, indexG, ll);
    }
    if (rl>0) {
        QHullM(p, end, indexG+rp, rl);
    }
}






long QuickHull::ResetWithProcessM(long n, Cart2DPoint* pt, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH){
    ///////////////////////////////////////
    //  For draw process
    isProcess = true;
    step = 0;
    
    this->mapGroup = mapGroup;
    this->mapStatus = mapStatus;
    this->mapVerticesIndex = mapVerticesIndex;

    ///////////////////////////////////////

    
    if (upHull.son!=nullptr) {
        delete upHull.son;
        upHull.son = nullptr;
    }
    
    if (downHull.son !=nullptr) {
        delete downHull.son;
        downHull.son = nullptr;
    }
    
    
    nPoint = n;
    if (verticesIndex!=nullptr) {
        delete []verticesIndex;
    }
    verticesIndex = new long[nPoint];
    
//    if (indexgroup) {
//        delete []indexgroup;
//    }
//    indexgroup = new long[nPoint];
    
    pointsArray = pt;
    status = s;
    
    
    
    long i;
    Cart2DPoint rm,lm;
    long rmI = 0, lmI = 0;
    rm = pointsArray[0];
    lm = pointsArray[0];
    
    for (i=1; i<nPoint; i++) {
        if ((pointsArray[i].x>rm.x)||((pointsArray[i].x==rm.x)&&(pointsArray[i].y>rm.y))){
            rm = pointsArray[i];
            rmI = i;
        }
        if ((pointsArray[i].x<lm.x)||((pointsArray[i].x==lm.x)&&(pointsArray[i].y<lm.y))){
            lm = pointsArray[i];
            lmI = i;
        }
    }
    LongDC *u1,*u2,*d1,*d2;
    
    u2=upHull.AddPoint(rmI);
    u1=upHull.AddPoint(lmI);
    d2=downHull.AddPoint(lmI);
    d1=downHull.AddPoint(rmI);
    
    long ul = 0, dl = 0, dp = nPoint;
    
    
    for (i=0; i<nPoint; i++) {
        if (pointsArray[i].LeftTest(lm, rm)>0) {
            status[ul] = i;
            ul++;
        }
        if (pointsArray[i].LeftTest(rm, lm)>0) {
            dp--;
            status[dp] = i;
            dl++;
        }
    }
    
    
    LongDC *p;
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        for (i = ul; i<dp; i++) {
            status[i] = -1;
        }
        
        memset(mapStatus, 0, sizeof(long)*nMax*nStep);
        for (i = 0; i<nPoint; i++) {
            if (status[i]!=-1) {
                mapStatus[step][status[i]] = 1;
            }
        }
        
        i=0;
        
        
        p = upHull.son;
        do{
            mapVerticesIndex[step][i] = p->index;
            i++;
            p = p->son;
        }while(p!=nullptr);
        p = downHull.son;
        do{
            mapVerticesIndex[step][i] = p->index;
            i++;
            p = p->son;
        }while(p!=nullptr);
        
        
        step++;
        if (step>=nStep) {
            isProcess = false;
        }
    }
    ////////////////////////////////////
    if (ul>0) {
        QHullM(u1, u2, status, ul);
    }
    if (dl>0) {
        QHullM(d1, d2, status+dp, dl);
    }
    
    nVertices = 0;
    
    p = u2;
    while (p!=u1) {
        verticesIndex[nVertices] = p->index;
        nVertices++;
        p = p->father;
    }
    
    p = d2;
    while (p!=d1) {
        verticesIndex[nVertices] = p->index;
        nVertices++;
        p = p->father;
    }
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        
        
        stepCH = step;

    }
    
    ///////////////////////////////////////
    
    return nVertices;
}