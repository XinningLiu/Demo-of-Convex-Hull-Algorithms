//
//  BoundingBoxHull.hpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef BoundingBoxHull_hpp
#define BoundingBoxHull_hpp

#include <stdio.h>

#include "Points.hpp"
#include "BasicStructure.hpp"

#include "AVLTree.hpp"
#include "AVLMTree.hpp"

class BBConvexHull{
    Cart2DPoint* pointsArray;
    long* status;
    
    long* Index;
    int* IndexS;
    int* IndexF;
    bool bg,ed;

 
    Chain* ChainArray;
    
    long* VerticesIndex;
    
    
    Cart2DPoint Center;
    int kLevel;         // Partition cirumferense to 2k parts;
    long nPoint;
    int IndexLength;
    long VerticesLength;
    
    avlTree<Node> *TreeArray;
    
    avlMTree<Node> *MTreeArray;
    
    
    long * lengthArr;
    long * startArr;
    ///////////////////////////////////////
    //  For draw process
    static const int nStep = 256;
    static const int nMax = 1024;
    long (*mapStatus)[nMax];
    long (*mapVerticesIndex)[nMax];
    int *mapGroup;
    int step;
    bool b;
    bool isProcess;
    ///////////////////////////////////////

    
    
protected:
    void BuildIndexArray();
    void BuildChainArray();
    void TestOtherVertices();
    void BuildVerticesArray();
    
    
    void BuildAVLArray();
    void TestOtherVerticesAVL();
    void BuildVerticesArrayAVL();
    
    void BuildAVLMArray();
    void TestOtherVerticesAVLM();
    void BuildVerticesArrayAVLM();

    
    
    
    void BuildIndexArrayM();
    void BuildAVLMArrayM();
    void TestOtherVerticesAVLMM();
    
    
public:
    
    BBConvexHull();
    long Reset(long l, Cart2DPoint* p, long* s);
    
    long ResetChain(long l, Cart2DPoint* p, long* s);
    long ResetAVL(long l, Cart2DPoint* p, long* s);
    long ResetAVLM(long l, Cart2DPoint* p, long* s);

    
    long ResetM(long l, Cart2DPoint* p, long* s);
    
    long* GetVerticesIndex(){
        return VerticesIndex;
    }
    
    long GetNVertices();
    int GetKLevel(){    return kLevel;}
    ~BBConvexHull();

    ///////////////////////////////////////
    //  For draw process
    long ResetWithProcess(long l, Cart2DPoint* p, long* s, long (*mapStatus)[nMax],long (*mapVerticesIndex)[nMax],int* mapGroup, int& step);
    ///////////////////////////////////////

    
};


#endif /* BoundingBoxHull_hpp */
