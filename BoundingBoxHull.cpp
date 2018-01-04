    //
//  BoundingBoxHull.cpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#include "BoundingBoxHull.hpp"
#include <math.h>
#include <string.h>




#ifndef PI
#define PI 3.141592653589793
#endif

//#include <iostream>
//using namespace std;

BBConvexHull::BBConvexHull(){
    pointsArray = nullptr;
    status = nullptr;
    
    
    Index = nullptr;
    IndexS = nullptr;
    IndexF = nullptr;
    
    ChainArray = nullptr;
    VerticesIndex = nullptr;
    
    
    
    TreeArray = nullptr;
    MTreeArray = nullptr;
    
    lengthArr = nullptr;
    startArr = nullptr;
    
    
    nPoint = -1;
    kLevel = -1;
    IndexLength = -1;
    VerticesLength = -1;
}

BBConvexHull::~BBConvexHull(){
    
    if (Index!=nullptr) {
        delete [] Index;
        IndexF = nullptr;
    }
    if (IndexS!=nullptr) {
        delete []IndexS;
        IndexS = nullptr;
    }
    if (IndexF!=nullptr) {
        delete []IndexF;
        IndexF = nullptr;
    }
    
    if (ChainArray!=nullptr) {
        delete [] ChainArray;
        ChainArray = nullptr;
    }
    
    
    
    
    if (TreeArray!=nullptr) {
        delete []TreeArray;
        TreeArray = nullptr;
    }
    
    if (MTreeArray!=nullptr) {
        delete []MTreeArray;
        MTreeArray = nullptr;
    }
    
    if (lengthArr) {
        delete []lengthArr;
        lengthArr = nullptr;
    }
    if (startArr) {
        delete []startArr;
        startArr = nullptr;
    }
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
        VerticesIndex = nullptr;
    }
}

long BBConvexHull::Reset(long l, Cart2DPoint* p, long* s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    nPoint = l;
    pointsArray = p;
    long layer=0,t=nPoint;
    while (t>0){
        t=t>>1;
        layer++;
    }
    kLevel = (int)fmax(3,layer);
    status = s;
    
    if (Index!=nullptr) {
        delete []Index;
    }
    Index = new long [kLevel*2];
    memset(Index, 0, sizeof(long)*kLevel*2);
    if (IndexS!=nullptr) {
        delete []IndexS;
    }
    IndexS = new int[kLevel*2];
    memset(IndexS, 0, sizeof(int)*kLevel*2);
    if (IndexF!=nullptr) {
        delete []IndexF;
    }
    IndexF = new int[kLevel*2];
    memset(IndexF, 0, sizeof(int)*kLevel*2);
    
    if (lengthArr) {
        delete []lengthArr;
    }
    lengthArr = new long[kLevel*2];
    memset(lengthArr, 0, sizeof(long)*kLevel*2);
    
    if (startArr) {
        delete []startArr;
    }
    startArr = new long[kLevel*2];
    memset(startArr, 0, sizeof(long)*kLevel*2);
    
    
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
    }
    VerticesIndex = new long[nPoint+1];
    memset(VerticesIndex, 0, sizeof(long)*(nPoint+1));
    
    
    
    IndexLength = 0;
    VerticesLength = 0;
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////


    BuildIndexArray();
    
//    BuildChainArray();
//    TestOtherVertices();
//    BuildVerticesArray();
    
//        BuildAVLArray();
//        TestOtherVerticesAVL();
//        BuildVerticesArrayAVL();
    
    BuildAVLMArray();
    TestOtherVerticesAVLM();
    BuildVerticesArrayAVLM();
    
    return VerticesLength;
}


long BBConvexHull::ResetChain(long l, Cart2DPoint* p, long* s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    nPoint = l;
    pointsArray = p;
    long layer=0,t=nPoint;
    while (t>0){
        t=t>>1;
        layer++;
    }
    kLevel = (int)fmax(3,layer);
    status = s;
    
    if (Index!=nullptr) {
        delete []Index;
    }
    Index = new long [kLevel*2];
    memset(Index, 0, sizeof(long)*kLevel*2);
    if (IndexS!=nullptr) {
        delete []IndexS;
    }
    IndexS = new int[kLevel*2];
    memset(IndexS, 0, sizeof(int)*kLevel*2);
    if (IndexF!=nullptr) {
        delete []IndexF;
    }
    IndexF = new int[kLevel*2];
    memset(IndexF, 0, sizeof(int)*kLevel*2);
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
    }
    VerticesIndex = new long[nPoint+1];
    memset(VerticesIndex, 0, sizeof(long)*(nPoint+1));
    
    
    
    IndexLength = 0;
    VerticesLength = 0;
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    BuildIndexArray();
    
        BuildChainArray();
        TestOtherVertices();
        BuildVerticesArray();
    
    //        BuildAVLArray();
    //        TestOtherVerticesAVL();
    //        BuildVerticesArrayAVL();
    
//    BuildAVLMArray();
//    TestOtherVerticesAVLM();
//    BuildVerticesArrayAVLM();
    
    return VerticesLength;
}
long BBConvexHull::ResetAVL(long l, Cart2DPoint* p, long* s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    nPoint = l;
    pointsArray = p;
    long layer=0,t=nPoint;
    while (t>0){
        t=t>>1;
        layer++;
    }
    kLevel = (int)fmax(3,layer);
    status = s;
    
    if (Index!=nullptr) {
        delete []Index;
    }
    Index = new long [kLevel*2];
    memset(Index, 0, sizeof(long)*kLevel*2);
    if (IndexS!=nullptr) {
        delete []IndexS;
    }
    IndexS = new int[kLevel*2];
    memset(IndexS, 0, sizeof(int)*kLevel*2);
    if (IndexF!=nullptr) {
        delete []IndexF;
    }
    IndexF = new int[kLevel*2];
    memset(IndexF, 0, sizeof(int)*kLevel*2);
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
    }
    VerticesIndex = new long[nPoint+1];
    memset(VerticesIndex, 0, sizeof(long)*(nPoint+1));
    
    
    
    IndexLength = 0;
    VerticesLength = 0;
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    BuildIndexArray();
    
    //    BuildChainArray();
    //    TestOtherVertices();
    //    BuildVerticesArray();
    
            BuildAVLArray();
            TestOtherVerticesAVL();
            BuildVerticesArrayAVL();
    
    //    BuildAVLMArray();
    //    TestOtherVerticesAVLM();
    //    BuildVerticesArrayAVLM();
    
     return VerticesLength;
}
long BBConvexHull::ResetAVLM(long l, Cart2DPoint* p, long* s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    nPoint = l;
    pointsArray = p;
    long layer=0,t=nPoint;
    while (t>0){
        t=t>>1;
        layer++;
    }
    kLevel = (int)fmax(3,layer);
    status = s;
    
    if (Index!=nullptr) {
        delete []Index;
    }
    Index = new long [kLevel*2];
    memset(Index, 0, sizeof(long)*kLevel*2);
    if (IndexS!=nullptr) {
        delete []IndexS;
    }
    IndexS = new int[kLevel*2];
    memset(IndexS, 0, sizeof(int)*kLevel*2);
    if (IndexF!=nullptr) {
        delete []IndexF;
    }
    IndexF = new int[kLevel*2];
    memset(IndexF, 0, sizeof(int)*kLevel*2);
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
    }
    VerticesIndex = new long[nPoint+1];
    memset(VerticesIndex, 0, sizeof(long)*(nPoint+1));
    
    
    
    IndexLength = 0;
    VerticesLength = 0;
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    BuildIndexArray();
    
    //    BuildChainArray();
    //    TestOtherVertices();
    //    BuildVerticesArray();
    
    //        BuildAVLArray();
    //        TestOtherVerticesAVL();
    //        BuildVerticesArrayAVL();
    
        BuildAVLMArray();
        TestOtherVerticesAVLM();
        BuildVerticesArrayAVLM();
    
     return VerticesLength;
}

///////////////////////////////////////
//  For draw process
long BBConvexHull::ResetWithProcess(long l, Cart2DPoint* p, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& stepCH){
    
    isProcess = true;
    
    this->mapGroup = mapGroup;
    this->mapStatus = mapStatus;
    this->mapVerticesIndex = mapVerticesIndex;
    
    nPoint = l;
    pointsArray = p;
    long layer=0,t=nPoint;
    while (t>0){
        t=t>>1;
        layer++;
    }
    kLevel = (int)fmax(3,layer);
    status = s;
    
    if (Index!=nullptr) {
        delete []Index;
    }
    Index = new long [kLevel*2];
    memset(Index, 0, sizeof(long)*kLevel*2);
    if (IndexS!=nullptr) {
        delete []IndexS;
    }
    IndexS = new int[kLevel*2];
    memset(IndexS, 0, sizeof(int)*kLevel*2);
    if (IndexF!=nullptr) {
        delete []IndexF;
    }
    IndexF = new int[kLevel*2];
    memset(IndexF, 0, sizeof(int)*kLevel*2);
    
    
    if (lengthArr) {
        delete []lengthArr;
    }
    lengthArr = new long[kLevel*2];
    memset(lengthArr, 0, sizeof(long)*kLevel*2);
    
    if (startArr) {
        delete []startArr;
    }
    startArr = new long[kLevel*2];
    memset(startArr, 0, sizeof(long)*kLevel*2);

    
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
    }
    VerticesIndex = new long[nPoint+1];
    memset(VerticesIndex, 0, sizeof(long)*(nPoint+1));
    
    
    
    IndexLength = 0;
    VerticesLength = 0;
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    BuildIndexArray();
    //    BuildChainArray();
    //    TestOtherVertices();
    //    BuildVerticesArray();
    
    //    BuildAVLArray();
    //    TestOtherVerticesAVL();
    //    BuildVerticesArrayAVL();
    
    BuildAVLMArray();
    TestOtherVerticesAVLM();
    BuildVerticesArrayAVLM();
    
    
    stepCH=step;
    
    return VerticesLength;
    
}
///////////////////////////////////////


void BBConvexHull::BuildIndexArray(){
    long j;
    int i,c;
    double angleInternvel = PI / kLevel;
    double angle=0;
    double diff = 0.0000000000001;
    Node pMin, pMax, ptemp;
    double tt,tm;
    
    Center.x = 0;
    Center.y = 0;
    
    // when I built index, I can discard inside points
    IndexS[0] = 0;
    IndexS[kLevel] = kLevel;
    
    for (i=0; i<kLevel; i++) {
        pMin.Value = pointsArray[0].x * cos(angle) + pointsArray[0].y * sin(angle);
        pMax.Value = pMin.Value;
        pMax.Index = 0;
        pMin.Index = 0;
        for (j=0; j<nPoint; j++) {
            
            if ((i==1)&&(status[j]>=0)) {
                c = pointsArray[j].LeftTest(pointsArray[Index[kLevel]], pointsArray[Index[0]]);
                
                switch (c) {
                    case 0:
                        status[j] = -1;
                        break;
                    case -1:
                        status[j] = IndexS[kLevel];
                        break;
                    case 1:
                        status[j] = IndexS[0];
                        break;
                    default:
                        break;
                }
            }
            
            if (i>1) {
                if ((Index[i-2]!=Index[i-1])&&(Index[kLevel]!=Index[i-1])) {
                    if (status[j]==IndexS[i-2]){
                        c = pointsArray[j].LeftTest(pointsArray[Index[kLevel]], pointsArray[Index[i-1]]);
                        switch (c) {
                            case 0:
                                status[j] = -1;
                                break;
                            case 1:
                                status[j] = IndexS[i-1];
                                break;
                            case -1:
                                if (pointsArray[j].LeftTest(pointsArray[Index[i-2]], pointsArray[Index[i-1]])>=0) {
                                    status[j] = -1;;
                                }
                                break;
                            default:
                                break;
                        }
                        
                        
                    }
                }
                if ((Index[i-2+kLevel]!=Index[i-1+kLevel])&&(Index[0]!=Index[i-1+kLevel])) {
                    if (status[j] == IndexS[i-2+kLevel]) {
                        c = pointsArray[j].LeftTest(pointsArray[Index[0]], pointsArray[Index[i-1+kLevel]]);
                        switch (c) {
                            case 0:
                                status[j] = -1;
                                break;
                            case 1:
                                status[j] = IndexS[i-1+kLevel];
                                break;
                            case -1:
                                if (pointsArray[j].LeftTest(pointsArray[Index[i-2+kLevel]], pointsArray[Index[i-1+kLevel]])>=0) {
                                    status[j] = -1;
                                }
                                break;
                            default:
                                break;
                        }
                        
                    }
                }
            }
            
            
            if ((j!=0)&&((status[j]==IndexS[i-1])||(status[j]==IndexS[i-1+kLevel])||(status[j]==-2))) {
                ptemp.Value = pointsArray[j].x * cos(angle) + pointsArray[j].y * sin(angle);
                ptemp.Index = j;
                if (ptemp.Value >= pMax.Value) {
                    if (ptemp.Value == pMax.Value) {
                        tt = pointsArray[j].x * cos(angle + diff) + pointsArray[j].y * sin(angle + diff);
                        tm = pointsArray[pMax.Index].x * cos(angle + diff) + pointsArray[pMax.Index].y * sin(angle + diff);
                        if ( tt > tm) {
                            pMax.Value = ptemp.Value;
                            pMax.Index = ptemp.Index;
                        }
                    }
                    else{
                        pMax.Value = ptemp.Value;
                        pMax.Index = ptemp.Index;
                    }
                }
                
                if (ptemp.Value <= pMin.Value) {
                    if (ptemp.Value == pMin.Value) {
                        tt = pointsArray[j].x * cos(angle + diff) + pointsArray[j].y * sin(angle + diff);
                        tm = pointsArray[pMin.Index].x * cos(angle + diff) + pointsArray[pMin.Index].y * sin(angle + diff);
                        if ( tt < tm) {
                            pMin.Value = ptemp.Value;
                            pMin.Index = ptemp.Index;
                        }
                    }
                    else{
                        pMin.Value = ptemp.Value;
                        pMin.Index = ptemp.Index;
                    }
                }

            }
        }

        
        Index[i] = pMax.Index;
        Index[i+kLevel] = pMin.Index;
        status[pMax.Index] = -2;
        status[pMin.Index] = -2;
        
        

        if (i>0) {
            if (Index[i-1]!=Index[i]) {
                IndexS[i] = i;
            }
            else{
                IndexS[i] = IndexS[i-1];
            }
            if (Index[i+kLevel-1]!=Index[i+kLevel]) {
                IndexS[i+kLevel] = i+kLevel;
            }
            else{
                IndexS[i+kLevel] = IndexS[i+kLevel-1];
            }
        }
        
        angle += angleInternvel;
        Center.x += pointsArray[pMax.Index].x + pointsArray[pMax.Index].x;
        Center.y += pointsArray[pMin.Index].y + pointsArray[pMin.Index].y;
        
        ///////////////////////////////////////
        //  For draw process
        if (isProcess) {

            memcpy(mapStatus[step], status, sizeof(long)*nPoint);
           
            
            
//            mapGroup[step] = IndexS[i];
            
            if (i>0) {
                for (j=0; j<i; j++) {
                    mapVerticesIndex[step][j] = Index[j];
                    mapVerticesIndex[step][j+i] = Index[j+kLevel];
                }
                step++;
            }

            if (step>=nStep) {
                isProcess = false;
            }

            
        }
        ///////////////////////////////////////

    }
    Center.x /= (2*kLevel);
    Center.y /= (2*kLevel);

    
    
    if ((Index[i-2]!=Index[i-1])&&(Index[kLevel]!=Index[i-1])) {
        for (j=0; j<nPoint; j++)
            
            if (status[j]==IndexS[i-2]){
                c = pointsArray[j].LeftTest(pointsArray[Index[kLevel]], pointsArray[Index[i-1]]);
                if (c==0) {
                    status[j] = -1;
                }
                if (c>0) {
                    status[j] = IndexS[i-1];
                }
                if (c<0) {
                    if (pointsArray[j].LeftTest(pointsArray[Index[i-2]], pointsArray[Index[i-1]])>=0) {
                        status[j] = -1;;
                    }
                }
            }
    }
    if ((Index[i-2+kLevel]!=Index[i-1+kLevel])&&(Index[0]!=Index[i-1+kLevel])) {
        for (j=0; j<nPoint; j++)
            if (status[j] == IndexS[i-2+kLevel]) {
                c = pointsArray[j].LeftTest(pointsArray[Index[0]], pointsArray[Index[i-1+kLevel]]);
                if (c==0) {
                    status[j] = -1;
                }
                if (c>0) {
                    status[j] = IndexS[i-1+kLevel];
                }
                if (c<0) {
                    if (pointsArray[j].LeftTest(pointsArray[Index[i-2+kLevel]], pointsArray[Index[i-1+kLevel]])>=0) {
                        status[j] = -1;
                    }
                }
            }
    }

    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        memcpy(mapStatus[step], status, sizeof(long)*nPoint);
        step++;
        if (step>=nStep) {
            isProcess = false;
        }
        
        mapGroup[step] = IndexS[i];
        
        for (j=0; j<i; j++) {
            mapVerticesIndex[step][j] = Index[j];
            mapVerticesIndex[step][j+i] = Index[j+kLevel];
        }
        memcpy(mapStatus[step], status, sizeof(long)*nPoint);
        step++;
        if (step>=nStep) {
            isProcess = false;
        }   
        
    }
    ///////////////////////////////////////

    
    if (Index[kLevel-1]==Index[kLevel])
        ed = true;
    else
        ed = false;
    
    if (Index[2*kLevel-1]==Index[0])
        bg = true;
    else
        bg = false;
    
}


void BBConvexHull::BuildChainArray(){
    int i,j;
    long t = Index[0];
    IndexLength = 1;
    IndexF[0]=0;
    for (i=1; i<2*kLevel; i++) {
        if (t!=Index[i]) {
            t = Index[i];
            IndexLength++;
        }
        IndexF[i] = IndexLength-1;
    }
    if (Index[0] == Index[2*kLevel-1]) {
        IndexLength--;
        t = IndexF[2*kLevel-1];
        i = 2*kLevel-1;
        while (IndexF[i]==t) {
            IndexF[i] = 0;
            i--;
        }
    }
    if (ChainArray!=nullptr) {
        delete [] ChainArray;
    }
    ChainArray = new Chain[IndexLength];

    i = 0;
    j = 0;
    
    t = Index[i];
    
    Cart2DPoint p;
    double angle;
    p = pointsArray[t]-Center;
    angle = atan2(p.y, p.x);
    Node tNode;
    tNode.Value = angle;
    tNode.Index = t;
    
    ChainArray[0].Insert(tNode, 0);
    ChainArray[IndexLength-1].Insert(tNode, 0);
    for (j=0; j<IndexLength-1; j++) {
        do{
            i++;
        }while ((t==Index[i])&&(i<2*kLevel));
        t = Index[i];
        p = pointsArray[t]-Center;
        angle = atan2(p.y, p.x);
        tNode.Value = angle;
        tNode.Index = t;
        
        ChainArray[j].Insert(tNode, 1);
        ChainArray[j+1].Insert(tNode, 0);
    }

    for (j=0; j<IndexLength; j++) {
        if (ChainArray[j].GetCurNode(0).Value > ChainArray[j].GetCurNode(1).Value) {
            ChainArray[j].SetValue(1, ChainArray[j].GetCurNode(1).Value + 2*PI);
            break;
        }
    }
}

void BBConvexHull::TestOtherVertices(){
    
    long i;
    Cart2DPoint p;
    double angle;
    Node tNode;
    long position;
    long group,flag;
    int b,bt;
    long l,k;
    
    for (i=0; i<nPoint; i++) {
        group = status[i];
        if (group>=0) {
            if ((group == 0)&&(bg)) {
                group = IndexS[2*kLevel-1];
            }
            if ((group == kLevel)&&(ed)) {
                group = IndexS[kLevel-1];
            }
            p = pointsArray[i]-Center;
            angle = atan2(p.y, p.x);
            
            flag = IndexF[group];
            
            
            if (angle<ChainArray[flag].GetCurNode(0).Value) {
                angle += 2 * PI;
            }
            if (angle>ChainArray[flag].GetCurNode(ChainArray[flag].GetLength()-1).Value) {
                angle -= 2 * PI;
            }
            
            tNode.Value = angle;
            tNode.Index = i;
            
            if (ChainArray[flag].GetLength()==2) {
                ChainArray[flag].Insert(tNode, 1);
            }
            else{
                position = ChainArray[flag].FindPosition(tNode);
                b = pointsArray[ChainArray[flag].GetCurNode(position).Index].LeftTest(pointsArray[ChainArray[flag].GetPreNode(position).Index], pointsArray[i]);
                if (b>0) {
                    ChainArray[flag].Insert(tNode, position);
                    l = ChainArray[flag].GetLength();
                    k = position - 1;
                    while (k>0){
                        bt = pointsArray[i].LeftTest(pointsArray[ChainArray[flag].GetPreNode(k).Index], pointsArray[ChainArray[flag].GetCurNode(k).Index]);
                        if (bt<=0) {
                            ChainArray[flag].Delete(k);
                            k=k-1;
                            position --;
                            l--;
                        }else
                            break;
                    }
                    k=position+1;
                    while (k<l-1) {
                        bt = pointsArray[ChainArray[flag].GetSucNode(k).Index].LeftTest(pointsArray[i], pointsArray[ChainArray[flag].GetCurNode(k).Index]);
                        if (bt<=0) {
                            ChainArray[flag].Delete(k);
                            l--;
                        }else
                            break;
                    }
                }
            }
        }
    }
    
}



void BBConvexHull::BuildVerticesArray(){
    long i,p,l,j;
    p=0;
    VerticesIndex[p] = ChainArray[0].GetCurNode(0).Index;
    for(i=0;i<IndexLength;i++){
        l = ChainArray[i].GetLength();
        for (j=1;j<l;j++){
            p++;
            VerticesIndex[p] = ChainArray[i].GetCurNode(j).Index;
        }
    }
    
    VerticesLength = p;
}

long BBConvexHull::GetNVertices(){
    return VerticesLength;
}


void BBConvexHull::BuildAVLArray(){
    int i,j;
    long t = Index[0];
    IndexLength = 1;
    IndexF[0]=0;
    for (i=1; i<2*kLevel; i++) {
        if (t!=Index[i]) {
            t = Index[i];
            IndexLength++;
        }
        IndexF[i] = IndexLength-1;
    }
    if (Index[0] == Index[2*kLevel-1]) {
        IndexLength--;
        t = IndexF[2*kLevel-1];
        i = 2*kLevel-1;
        while (IndexF[i]==t) {
            IndexF[i] = 0;
            i--;
        }
    }
    
    if (TreeArray!=nullptr) {
        delete []TreeArray;
    }
    TreeArray = new avlTree<Node>[IndexLength];
    
    i = 0;
    j = 0;
    
    t = Index[i];
    
    Cart2DPoint p;
    double angle;
    p = pointsArray[t]-Center;
    angle = atan2(p.y, p.x);
    Node tNode, t1,t0;
    tNode.Value = angle;
    tNode.Index = t;
    
    TreeArray[0].Insert(tNode);
//    TreeArray[IndexLength-1].Insert(tNode);
    t1 = tNode;
    t0 = tNode;
    
    for (j=0; j<IndexLength-1; j++) {
        do{
            i++;
        }while ((t==Index[i])&&(i<2*kLevel));
        t = Index[i];
        p = pointsArray[t]-Center;
        angle = atan2(p.y, p.x);
        tNode.Value = angle;
        tNode.Index = t;
        
        if (tNode<t1) {
            tNode.Value+=2*PI;
        }
        
        TreeArray[j].Insert(tNode);
        TreeArray[j+1].Insert(tNode);
        t1 = tNode;
    }
    if (t0<tNode) {
        t0.Value+=2*PI;
    }
    TreeArray[j].Insert(tNode);
    TreeArray[j].Insert(t0);
}
void BBConvexHull::TestOtherVerticesAVL(){
    
    long i;
    Cart2DPoint p;
    double angle;
    Node tNode;
//    long position;
    long group,flag;
    int b,bt;
    
    avlNode<Node> *ps,*floor,*ceiling;
    
    for (i=0; i<nPoint; i++) {
        group = status[i];
        if (group>=0) {
            if ((group == 0)&&(bg)) {
                group = IndexS[2*kLevel-1];
            }
            if ((group == kLevel)&&(ed)) {
                group = IndexS[kLevel-1];
            }
            p = pointsArray[i]-Center;
            angle = atan2(p.y, p.x);
            
            flag = IndexF[group];
            
            
            if (angle<TreeArray[flag].getMin()->key.Value) {
                angle += 2 * PI;
            }
            if (angle>TreeArray[flag].getMax()->key.Value) {
                angle -= 2 * PI;
            }
            
            tNode.Value = angle;
            tNode.Index = i;
            
            if (TreeArray[flag].GetLength()==2) {
                TreeArray[flag].Insert(tNode);
            }
            else{
                ps = TreeArray[flag].FindPosition(tNode, &floor, &ceiling);
                if (ps) {
                    floor = ps;
                }
                b = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[i]);
          //      b = pointsArray[ChainArray[flag].GetCurNode(position).Index].LeftTest(pointsArray[ChainArray[flag].GetPreNode(position).Index], pointsArray[i]);
                if (b>0) {

                    TreeArray[flag].Insert(tNode);
                    do{
                        ps = TreeArray[flag].FindPosition(tNode, &floor, &ceiling);
                        ps = TreeArray[flag].FindPosition(floor->key, &floor, &ceiling);
                        if (floor) {
                            bt = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[ps->key.Index]);
                        }
                        else break;
                        if (bt<=0) {
                            TreeArray[flag].remove(ps);
                        }
                    }while (bt<=0);
                    
                    do{
                        ps = TreeArray[flag].FindPosition(tNode, &floor, &ceiling);
                        ps = TreeArray[flag].FindPosition(ceiling->key, &floor, &ceiling);
                        if (ceiling) {
                            bt = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[ps->key.Index]);
                        }
                        else break;
                        if (bt<=0) {
                            TreeArray[flag].remove(ps);
                        }
                    }while (bt<=0);
                }
            }
        }
    }
}
void BBConvexHull::BuildVerticesArrayAVL(){
    long i,l;
    long* p = VerticesIndex;
    VerticesLength = 0;
    for (i = 0; i<IndexLength; i++) {
        l = TreeArray[i].Iterate(p);
        VerticesLength+=l-1;
        p=p+(l-1);
    }
}


void BBConvexHull::BuildAVLMArray(){
    int i,j;
    long t = Index[0];
    IndexLength = 1;
    IndexF[0]=0;
    for (i=1; i<2*kLevel; i++) {
        if (t!=Index[i]) {
            t = Index[i];
            IndexLength++;
        }
        IndexF[i] = IndexLength-1;
    }
    if (Index[0] == Index[2*kLevel-1]) {
        IndexLength--;
        t = IndexF[2*kLevel-1];
        i = 2*kLevel-1;
        while (IndexF[i]==t) {
            IndexF[i] = 0;
            i--;
        }
    }
    
    if (MTreeArray!=nullptr) {
        delete []MTreeArray;
    }
    MTreeArray = new avlMTree<Node>[IndexLength];
    
    i = 0;
    j = 0;
    
    t = Index[i];
    
    Cart2DPoint p;
    double angle;
    p = pointsArray[t]-Center;
    angle = atan2(p.y, p.x);
    Node tNode, t1,t0;
    tNode.Value = angle;
    tNode.Index = t;
    
    t1 = tNode;
    t0 = tNode;
    
    for (j=0; j<IndexLength-1; j++) {
        do{
            i++;
        }while ((t==Index[i])&&(i<2*kLevel));
        t = Index[i];
        p = pointsArray[t]-Center;
        angle = atan2(p.y, p.x);
        tNode.Value = angle;
        tNode.Index = t;
        
        if (tNode<t1) {
            tNode.Value+=2*PI;
        }
        
        MTreeArray[j].init(t1, tNode);
        
        t1 = tNode;
    }
    if (t0<tNode) {
        
        tNode.Value-=2*PI;
    }
    MTreeArray[j].init(tNode, t0);

}
void BBConvexHull::TestOtherVerticesAVLM(){
    long i;
    Cart2DPoint p;
    double angle;
    Node tNode;
    //    long position;
    long group,flag;
    int b,bt;
    
    avlMNode<Node> *ps,*pk,*floor,*ceiling;
    
    for (i=0; i<nPoint; i++) {
        group = status[i];
        if (group>=0) {
            if ((group == 0)&&(bg)) {
                group = IndexS[2*kLevel-1];
            }
            if ((group == kLevel)&&(ed)) {
                group = IndexS[kLevel-1];
            }
            p = pointsArray[i]-Center;
            angle = atan2(p.y, p.x);
            
            flag = IndexF[group];
            
            
            if (angle<MTreeArray[flag].getMin()->key.Value) {
                angle += 2 * PI;
            }
            if (angle>MTreeArray[flag].getMax()->key.Value) {
                angle -= 2 * PI;
            }
            
            tNode.Value = angle;
            tNode.Index = i;
            
            if (MTreeArray[flag].GetLength()==2) {
                MTreeArray[flag].setHead(tNode);
            }
            else{
                ps = MTreeArray[flag].FindPosition(tNode, &floor, &ceiling);
                if (ps) {
                    floor = ps;
                }
                b = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[i]);
                //      b = pointsArray[ChainArray[flag].GetCurNode(position).Index].LeftTest(pointsArray[ChainArray[flag].GetPreNode(position).Index], pointsArray[i]);
                if (b>0) {
                    
                    ps = MTreeArray[flag].Insert(tNode);
                    do{
                        pk = ps->pre;
                        floor = pk->pre;
                        ceiling = ps;
                        
                        if (floor) {
                            bt = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[pk->key.Index]);
                        }
                        else break;
                        if (bt<=0) {
                            MTreeArray[flag].remove(pk);
                        }
                    }while (bt<=0);
                    
                    do{
                        pk = ps->suc;
                        floor = ps;
                        ceiling = pk->suc;
                        if (ceiling) {
                            bt = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[pk->key.Index]);
                        }
                        else break;
                        if (bt<=0) {
                            MTreeArray[flag].remove(pk);
                        }
                    }while (bt<=0);
                }
            }
        }
    }

}
void BBConvexHull::BuildVerticesArrayAVLM(){
    long i,l;
    long* p = VerticesIndex;
    VerticesLength = 0;
    for (i = 0; i<IndexLength; i++) {
        l = MTreeArray[i].Iterate(p);
        VerticesLength+=l-1;
        p=p+(l-1);
    }
}


long BBConvexHull::ResetM(long l, Cart2DPoint* p, long* s){
    ///////////////////////////////////////
    //  For draw process
    isProcess = false;
    ///////////////////////////////////////
    
    nPoint = l;
    pointsArray = p;
    long layer=0,t=nPoint;
    while (t>0){
        t=t>>1;
        layer++;
    }
    kLevel = (int)fmax(3,layer);
    status = s;
    
    if (Index!=nullptr) {
        delete []Index;
    }
    Index = new long [kLevel*2];
    memset(Index, 0, sizeof(long)*kLevel*2);
    
    if (lengthArr) {
        delete []lengthArr;
    }
    lengthArr = new long[kLevel*2];
    memset(lengthArr, 0, sizeof(long)*kLevel*2);
    
    if (startArr) {
        delete []startArr;
    }
    startArr = new long[kLevel*2];
    memset(startArr, 0, sizeof(long)*kLevel*2);
    
    if (IndexS!=nullptr) {
        delete []IndexS;
    }
    IndexS = new int[kLevel*2];

    
    if (IndexF!=nullptr) {
        delete []IndexF;
    }
    IndexF = new int[kLevel*2];
    memset(IndexF, -1, sizeof(int)*kLevel*2);
    
    if (VerticesIndex!=nullptr) {
        delete []VerticesIndex;
    }
    VerticesIndex = new long[nPoint+1];
    memset(VerticesIndex, 0, sizeof(long)*(nPoint+1));
    
    
    
    IndexLength = 0;
    VerticesLength = 0;
    
    ///////////////////////////////////////
    //  For draw process
    if (isProcess) {
        step = 0;
    }
    ///////////////////////////////////////
    
    
    BuildIndexArrayM();
    
    //    BuildChainArray();
    //    TestOtherVertices();
    //    BuildVerticesArray();
    
    //        BuildAVLArray();
    //        TestOtherVerticesAVL();
    //        BuildVerticesArrayAVL();
    
    BuildAVLMArrayM();
    TestOtherVerticesAVLMM();
    BuildVerticesArrayAVLM();
    
    return VerticesLength;
}



void BBConvexHull::BuildIndexArrayM(){
    long j,tl,tp,tx,u,d,l;
    int i,c,b,k;
    double angleInternvel = PI / kLevel;
    double angle=0;
    double diff = 0.0000000000001;
    Node pMin, pMax, ptemp;
    double tt,tm;
    bool bmax = true,bmin = true;
    
    Center.x = 0;
    Center.y = 0;
    
    i = 0;
    pMin.Value = pointsArray[0].x * cos(angle) + pointsArray[0].y * sin(angle);
    pMax.Value = pMin.Value;
    pMax.Index = 0;
    pMin.Index = 0;

    for (j = 1; j<nPoint; j++) {
        ptemp.Value = pointsArray[j].x * cos(angle) + pointsArray[j].y * sin(angle);
        ptemp.Index = j;
        if (ptemp.Value >= pMax.Value) {
            if (ptemp.Value == pMax.Value) {
                tt = pointsArray[j].x * cos(angle + diff) + pointsArray[j].y * sin(angle + diff);
                tm = pointsArray[pMax.Index].x * cos(angle + diff) + pointsArray[pMax.Index].y * sin(angle + diff);
                if ( tt > tm) {
                    pMax.Value = ptemp.Value;
                    pMax.Index = ptemp.Index;
                }
            }
            else{
                pMax.Value = ptemp.Value;
                pMax.Index = ptemp.Index;
            }
        }
        
        if (ptemp.Value <= pMin.Value) {
            if (ptemp.Value == pMin.Value) {
                tt = pointsArray[j].x * cos(angle + diff) + pointsArray[j].y * sin(angle + diff);
                tm = pointsArray[pMin.Index].x * cos(angle + diff) + pointsArray[pMin.Index].y * sin(angle + diff);
                if ( tt < tm) {
                    pMin.Value = ptemp.Value;
                    pMin.Index = ptemp.Index;
                }
            }
            else{
                pMin.Value = ptemp.Value;
                pMin.Index = ptemp.Index;
            }
        }
    }
    
    
    Index[0] = pMax.Index;
    Index[kLevel] = pMin.Index;
    
    IndexS[0] = 0;
    IndexS[kLevel] = kLevel;
    
    angle += angleInternvel;
    Center.x += pointsArray[pMax.Index].x + pointsArray[pMax.Index].x;
    Center.y += pointsArray[pMin.Index].y + pointsArray[pMin.Index].y;

    
    startArr[kLevel] = nPoint;
    startArr[0] = 0;
    for (j = 0; j<nPoint; j++) {
        if (j == Index[0]) {
            startArr[kLevel]--;
            status[startArr[kLevel]] = j;
            lengthArr[kLevel] ++;
            continue;
        }
        if (j == Index[kLevel]) {
            status[lengthArr[0]] = j;
            lengthArr[0]++;
            continue;
        }
        c = pointsArray[j].LeftTest(pointsArray[pMin.Index], pointsArray[pMax.Index]);
        if (c>0) {
            status[lengthArr[0]] = j;
            lengthArr[0]++;
            continue;
        }
        if (c<0) {
            startArr[kLevel]--;
            status[startArr[kLevel]] = j;
            lengthArr[kLevel] ++;
        }
    }
    
    for (i = 1; i<kLevel; i++) {
        if (bmax) {
            pMax.Value = pointsArray[Index[i-1]].x * cos(angle) + pointsArray[Index[i-1]].y * sin(angle);
            tl = lengthArr[IndexS[i-1]];
            for (j = startArr[IndexS[i-1]]; j<startArr[IndexS[i-1]]+tl; j++) {
                ptemp.Value = pointsArray[status[j]].x * cos(angle) + pointsArray[status[j]].y * sin(angle);
                ptemp.Index = status[j];
                
                if (ptemp.Value >= pMax.Value) {
                    if (ptemp.Value == pMax.Value) {
                        tt = pointsArray[status[j]].x * cos(angle + diff) + pointsArray[status[j]].y * sin(angle + diff);
                        tm = pointsArray[pMax.Index].x * cos(angle + diff) + pointsArray[pMax.Index].y * sin(angle + diff);
                        if ( tt > tm) {
                            pMax.Value = ptemp.Value;
                            pMax.Index = ptemp.Index;
                        }
                    }
                    else{
                        pMax.Value = ptemp.Value;
                        pMax.Index = ptemp.Index;
                    }
                }
            }
            Index[i] = pMax.Index;
            
            
            if (Index[i]==Index[i-1]) {
                IndexS[i] = IndexS[i-1];
            }else
            {
                IndexS[i] = i;
                if (Index[i] == Index[kLevel]) {
                    for (k = i+1; k<kLevel; k++) {
                        Index[k] = Index[i];
                        IndexS[k] = i;
                    }
                    startArr[i] = startArr[kLevel];
                    lengthArr[i] = lengthArr[kLevel];
                    startArr[kLevel] = 0;
                    lengthArr[kLevel] = 0;
                    bmax = false;
                    
                    for (l = startArr[IndexS[i-1]]; l<startArr[IndexS[i-1]]+lengthArr[IndexS[i-1]]; l++) {
                        if (status[l] == Index[kLevel]) {
                            lengthArr[IndexS[i-1]]--;
                            memcpy((status+l), (status+l+1), (startArr[IndexS[i-1]]+lengthArr[IndexS[i-1]]-l)*sizeof(long));
                            break;
                        }
                    }
                    
                }
                else{
                    
                    tp = status[startArr[IndexS[i-1]]];
                    startArr[i] = tl + startArr[IndexS[i-1]];
                    u = startArr[IndexS[i-1]]+1;
                    d = startArr[i]-1;
                    lengthArr[IndexS[i-1]] = 0;
                    for (j = 0; j<tl; j++) {
                        if (tp == Index[kLevel]) {
                            tx = status[d];
                            startArr[i]--;
                            status[startArr[i]] = tp;
                            lengthArr[i]++;
                            tp = tx;
                            d--;
                            continue;
                        }
                        
                        c = pointsArray[tp].LeftTest(pointsArray[Index[kLevel]], pointsArray[Index[i]]);
                        if (c>0) {
                            tx = status[d];
                            startArr[i]--;
                            status[startArr[i]] = tp;
                            lengthArr[i]++;
                            tp = tx;
                            d--;
                            continue;
                        }
                        if (c<0) {
                            b = pointsArray[tp].LeftTest(pointsArray[Index[i]],pointsArray[Index[IndexS[i-1]]]);
                            if (b>0) {
                                tx = status[u];
                                status[startArr[IndexS[i-1]]+lengthArr[IndexS[i-1]]] = tp;
                                lengthArr[IndexS[i-1]]++;
                                tp = tx;
                                u++;
                                continue;
                            }
                        }
                        tp = status[u];
                        u++;
                    }
                }
            }
        }

        

        if (bmin) {
            tl = lengthArr[IndexS[ i-1+kLevel]];
            pMin.Value = pointsArray[Index[i-1+kLevel]].x * cos(angle) + pointsArray[Index[i-1+kLevel]].y * sin(angle);
            for (j = startArr[IndexS[ i-1+kLevel]]; j<startArr[IndexS[ i-1+kLevel]]+tl; j++) {
                ptemp.Value = pointsArray[status[j]].x * cos(angle) + pointsArray[status[j]].y * sin(angle);
                ptemp.Index = status[j];
                
                if (ptemp.Value <= pMin.Value) {
                    if (ptemp.Value == pMin.Value) {
                        tt = pointsArray[status[j]].x * cos(angle + diff) + pointsArray[status[j]].y * sin(angle + diff);
                        tm = pointsArray[pMin.Index].x * cos(angle + diff) + pointsArray[pMin.Index].y * sin(angle + diff);
                        if ( tt < tm) {
                            pMin.Value = ptemp.Value;
                            pMin.Index = ptemp.Index;
                        }
                    }
                    else{
                        pMin.Value = ptemp.Value;
                        pMin.Index = ptemp.Index;
                    }
                }
            }
            Index[i+kLevel] = pMin.Index;
            
            if (Index[i+kLevel]==Index[i-1+kLevel]) {
                IndexS[i+kLevel] = IndexS[i-1+kLevel];
            }
            else
            {
                IndexS[i+kLevel] = i+kLevel;
                if (Index[i+kLevel] == Index[0]) {
                    for (k = i+1; k<kLevel; k++) {
                        Index[k+kLevel] = Index[i+kLevel];
                        IndexS[k+kLevel] = i+kLevel;
                    }
                    startArr[i+kLevel] = startArr[0];
                    lengthArr[i+kLevel] = lengthArr[0];
                    startArr[0] = 0;
                    lengthArr[0] = 0;
                    bmin = false;
                    
                    for (l = startArr[IndexS[i-1+kLevel]]; l<startArr[IndexS[i-1+kLevel]]+lengthArr[IndexS[i-1+kLevel]]; l++) {
                        if (status[l] == Index[0]) {
                            lengthArr[IndexS[i-1+kLevel]]--;
                            memcpy((status+l), (status+l+1), (startArr[IndexS[i-1+kLevel]]+lengthArr[IndexS[i-1+kLevel]]-l)*sizeof(long));
                            break;
                        }
                    }
                    
                }
                else{
                    tp = status[startArr[IndexS[ i-1+kLevel]]];
                    startArr[i+kLevel] = tl+startArr[IndexS[ i-1+kLevel]];
                    u = startArr[IndexS[ i-1+kLevel]]+1;
                    d = startArr[i+kLevel]-1;
                    lengthArr[IndexS[ i-1+kLevel]] = 0;
                    for (j = 0; j<tl; j++) {
                        if (tp == Index[0]) {
                            tx = status[d];
                            startArr[i+kLevel]--;
                            status[startArr[i+kLevel]] = tp;
                            lengthArr[i+kLevel]++;
                            tp = tx;
                            d--;
                            continue;
                        }
                        c = pointsArray[tp].LeftTest(pointsArray[Index[0]], pointsArray[Index[i+kLevel]]);
                        if (c>0) {
                            tx = status[d];
                            startArr[i+kLevel]--;
                            status[startArr[i+kLevel]] = tp;
                            lengthArr[i+kLevel]++;
                            tp = tx;
                            d--;
                            continue;
                        }
                        if (c<0) {
                            b = pointsArray[tp].LeftTest(pointsArray[Index[i+kLevel]],pointsArray[Index[i-1+kLevel]]);
                            if (b>0) {
                                tx = status[u];
                                status[startArr[IndexS[ i-1+kLevel]]+lengthArr[IndexS[ i-1+kLevel]]] = tp;
                                lengthArr[IndexS[ i-1+kLevel]]++;
                                tp = tx;
                                u++;
                                continue;
                            }
                        }
                        tp = status[u];
                        u++;
                    }
                }
            }
        }
        
        angle += angleInternvel;
        Center.x += pointsArray[pMax.Index].x + pointsArray[pMax.Index].x;
        Center.y += pointsArray[pMin.Index].y + pointsArray[pMin.Index].y;
    }
    
    Center.x /= (2*kLevel);
    Center.y /= (2*kLevel);

    for (l = startArr[IndexS[i-1]]; l<startArr[IndexS[i-1]]+lengthArr[IndexS[i-1]]; l++) {
        if (status[l] == Index[kLevel]) {
            lengthArr[IndexS[i-1]]--;
            memcpy((status+l), (status+l+1), (startArr[IndexS[i-1]]+lengthArr[IndexS[i-1]]-l)*sizeof(long));
            break;
        }
    }
    for (l = startArr[IndexS[i-1+kLevel]]; l<startArr[IndexS[i-1+kLevel]]+lengthArr[IndexS[i-1+kLevel]]; l++) {
        if (status[l] == Index[0]) {
            lengthArr[IndexS[i-1+kLevel]]--;
            memcpy((status+l), (status+l+1), (startArr[IndexS[i-1+kLevel]]+lengthArr[IndexS[i-1+kLevel]]-l)*sizeof(long));
            break;
        }
    }
    
}


void BBConvexHull::BuildAVLMArrayM(){
    int i,j;
    long t = Index[0];
    IndexLength = 1;
    for (i=1; i<2*kLevel; i++) {
        if (t!=Index[i]) {
            t = Index[i];
            IndexLength++;
        }
    }
    if (Index[0] == Index[2*kLevel-1]) {
        IndexLength--;
    }
    
    if (MTreeArray!=nullptr) {
        delete []MTreeArray;
    }
    MTreeArray = new avlMTree<Node>[IndexLength];
    
    
    
    i = 0;
    j = 0;
    
    t = Index[0];
    i = 2*kLevel-1;
    while (Index[i]==t) {
        i--;
    }
    IndexF[(i+1)%(2*kLevel)] = 0;
    i = 0;
    
    Cart2DPoint p;
    double angle;
    p = pointsArray[t]-Center;
    angle = atan2(p.y, p.x);
    Node tNode, t1,t0;
    tNode.Value = angle;
    tNode.Index = t;
    
    t1 = tNode;
    t0 = tNode;
    
    for (j=0; j<IndexLength-1; j++) {
        do{
            i++;
        }while (t==Index[i]);
        t = Index[i];
        p = pointsArray[t]-Center;
        angle = atan2(p.y, p.x);
        tNode.Value = angle;
        tNode.Index = t;
        
        if (tNode<t1) {
            tNode.Value+=2*PI;
        }
        
        MTreeArray[j].init(t1, tNode);
        
        t1 = tNode;
        IndexF[i] = j+1;
    }
    if (t0<tNode) {
        
        tNode.Value-=2*PI;
    }
    MTreeArray[j].init(tNode, t0);

}
void BBConvexHull::TestOtherVerticesAVLMM(){
    long i,j;
    Cart2DPoint p;
    double angle;
    Node tNode;
    //    long position;
    long flag;
    int b,bt;
    
    avlMNode<Node> *ps,*pk,*floor,*ceiling;
    
    for (i = 0; i<2*kLevel; i++) {
        if (lengthArr[i]>0) {
            flag = IndexF[i];
            for (j = startArr[i]; j<startArr[i]+lengthArr[i]; j++) {
                p = pointsArray[status[j]]-Center;
                angle = atan2(p.y, p.x);
                
                if (angle<MTreeArray[flag].getMin()->key.Value) {
                    angle += 2 * PI;
                }else if (angle>MTreeArray[flag].getMax()->key.Value) {
                    angle -= 2 * PI;
                }
                tNode.Value = angle;
                tNode.Index = status[j];

                
                if (MTreeArray[flag].GetLength()==2) {
                    MTreeArray[flag].setHead(tNode);
                }
                else{
                    ps = MTreeArray[flag].FindPosition(tNode, &floor, &ceiling);
                    if (ps) {
                        floor = ps;
                    }
                    b = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[tNode.Index]);

                    if (b>0) {
                        
                        ps = MTreeArray[flag].Insert(tNode);
                        do{
                            pk = ps->pre;
                            floor = pk->pre;
                            ceiling = ps;
                            
                            if (floor) {
                                bt = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[pk->key.Index]);
                            }
                            else break;
                            if (bt<=0) {
                                MTreeArray[flag].remove(pk);
                            }
                        }while (bt<=0);
                        
                        do{
                            pk = ps->suc;
                            floor = ps;
                            ceiling = pk->suc;
                            if (ceiling) {
                                bt = pointsArray[ceiling->key.Index].LeftTest(pointsArray[floor->key.Index], pointsArray[pk->key.Index]);
                            }
                            else break;
                            if (bt<=0) {
                                MTreeArray[flag].remove(pk);
                            }
                        }while (bt<=0);
                    }
                }

            }
        }
    }
}

