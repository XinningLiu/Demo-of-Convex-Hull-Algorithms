//
//  RandomPointsArray.hpp
//  RondomPoints
//
//  Created by 刘昕凝 on 2/27/16.
//  Copyright © 2016 Dolly. All rights reserved.
//


#ifndef DATATYPE
#define DATATYPE
typedef enum DataType{
    cluster = 0,
    uniform = 1,
    circular= 2,
    input,
}DataType;
#endif

#ifndef RandomPointsArray_hpp
#define RandomPointsArray_hpp

#include <stdio.h>
#include "Points.hpp"


class RandomPointsArray{
    const int nBase=30;          // number of base points
    Cart2DPoint pBase[30];       // array of boase points
    double NormalizedParameter[30];
    
    long nPoints;        // number of random points
    Cart2DPoint* pArray;      // array of random points
    
//    void GeneralizePointBase();
//    void GeneralizeNormalizedParameter();
    void GeneralizeClusterPoints();
    
    void GeneralizeUniformPoints();
    
    void GeneralizeCircularPoints();
    
public:
    RandomPointsArray();
    void ResetRandomPoint(long n, DataType type);    // reset points
    inline long GetNPoints(){
        return nPoints;
    }
    ~RandomPointsArray();
    inline Cart2DPoint* GetPoints(){
        return pArray;
    }
    inline Cart2DPoint GetPoint(long n){
        return pArray[n];
    }
};

#endif /* RandomPointsArray_hpp */