//
//  RandomPointsAndConvexHull.cpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#include "RandomPointsAndConvexHull.hpp"

#include <time.h>
#include <fstream>
using namespace std;

void RandomPointsAndConvexHull::TimeTest(){
    long lStep=1000,nStep=1000,i,nVertices;
    clock_t start, end ;
    

    
    ofstream FileBBQH("BB&QHCircularData.txt");
    lStep=10000;
    nStep=100;
    FileBBQH<<"nPoint     nVertices  BB         QH\n";
    

    
    for (i=lStep; i<=lStep*nStep; i+=lStep) {
        GeneralizeRandomPoints(i, circular);
        start = clock();
        nVertices = GeneralizeConvexHull(boundingBox);
        end = clock();
        FileBBQH.width(10);
        FileBBQH.setf(ios::left);
        FileBBQH<<i<<' ';
        FileBBQH.width(10);
        FileBBQH.setf(ios::left);
        FileBBQH<<nVertices<<' ';
        FileBBQH.width(10);
        FileBBQH.setf(ios::left);
        FileBBQH<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        nVertices = GeneralizeConvexHull(quickHull);
        end = clock();
        FileBBQH.width(10);
        FileBBQH.setf(ios::left);
        FileBBQH<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        FileBBQH<<endl;
        
    }
    
    FileBBQH.close();
    
    lStep=2000;
    ofstream FileCluster("ClusterData.txt");
    
    FileCluster<<"nPoint     nVertices  BB         QH         GS         GW\n";
    
    for (i=lStep; i<=lStep*nStep; i+=lStep) {
        GeneralizeRandomPoints(i, cluster);
        nVertices=GeneralizeConvexHull(boundingBox);
        
        start = clock();
        GeneralizeConvexHull(boundingBox);
        end = clock();
        FileCluster.width(10);
        FileCluster.setf(ios::left);
        FileCluster<<i<<' ';
        FileCluster.width(10);
        FileCluster.setf(ios::left);
        FileCluster<<nVertices<<' ';
        FileCluster.width(10);
        FileCluster.setf(ios::left);
        FileCluster<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(quickHull);
        end = clock();
        FileCluster.width(10);
        FileCluster.setf(ios::left);
        FileCluster<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        
        start = clock();
        GeneralizeConvexHull(grahamScan);
        end = clock();
        FileCluster.width(10);
        FileCluster.setf(ios::left);
        FileCluster<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(giftWrapping);
        end = clock();
        FileCluster.width(10);
        FileCluster.setf(ios::left);
        FileCluster<<(double)(end-start)/CLOCKS_PER_SEC;
        
        
        
        FileCluster<<endl;
    }
    
    FileCluster.close();
    
    ofstream FileUniform("UniformData.txt");
    
    FileUniform<<"nPoint     nVertices  BB         QH         GS         GW\n";
    
    for (i=lStep; i<=lStep*nStep; i+=lStep) {
        
        GeneralizeRandomPoints(i, uniform);
        nVertices=GeneralizeConvexHull(boundingBox);
        
        start = clock();
        GeneralizeConvexHull(boundingBox);
        end = clock();
        FileUniform.width(10);
        FileUniform.setf(ios::left);
        FileUniform<<i<<' ';
        FileUniform.width(10);
        FileUniform.setf(ios::left);
        FileUniform<<nVertices<<' ';
        FileUniform.width(10);
        FileUniform.setf(ios::left);
        FileUniform<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(quickHull);
        end = clock();
        FileUniform.width(10);
        FileUniform.setf(ios::left);
        FileUniform<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(grahamScan);
        end = clock();
        FileUniform.width(10);
        FileUniform.setf(ios::left);
        FileUniform<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(giftWrapping);
        end = clock();
        FileUniform.width(10);
        FileUniform.setf(ios::left);
        FileUniform<<(double)(end-start)/CLOCKS_PER_SEC;
        
        FileUniform<<endl;
        
    }
    
    FileUniform.close();
    
    ofstream FileCircular("CircularData.txt");
    
    FileCircular<<"nPoint     nVertices  BB         QH         GS         GW\n";
    
    for (i=lStep; i<=lStep*nStep; i+=lStep) {
        
        
        GeneralizeRandomPoints(i, circular);
        nVertices=GeneralizeConvexHull(boundingBox);
        
        start = clock();
        GeneralizeConvexHull(boundingBox);
        end = clock();
        FileCircular.width(10);
        FileCircular.setf(ios::left);
        FileCircular<<i<<' ';
        FileCircular.width(10);
        FileCircular.setf(ios::left);
        FileCircular<<nVertices<<' ';
        FileCircular.width(10);
        FileCircular.setf(ios::left);
        FileCircular<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(quickHull);
        end = clock();
        FileCircular.width(10);
        FileCircular.setf(ios::left);
        FileCircular<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(grahamScan);
        end = clock();
        FileCircular.width(10);
        FileCircular.setf(ios::left);
        FileCircular<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        start = clock();
        GeneralizeConvexHull(giftWrapping);
        end = clock();
        FileCircular.width(10);
        FileCircular.setf(ios::left);
        FileCircular<<(double)(end-start)/CLOCKS_PER_SEC<<' ';
        
        FileCircular<<endl;
    }
    
    FileCircular.close();


    
    
    

    
    
}