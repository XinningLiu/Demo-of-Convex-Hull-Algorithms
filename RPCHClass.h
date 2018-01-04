//
//  RPCHClass.h
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#import <Foundation/Foundation.h>

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

struct ObjRPCHClass;

@interface RPCHClass : NSObject{
    
    struct ObjRPCHClass * _cppRPCH;
    
    long nPoint;
    long nVertices;
    
}

-(void) generalize:(long)n RandomPoints:(DataType)type;
-(long) generalizeConvexHull:(AlgorithmType)type;
-(long) generalizeProcess:(AlgorithmType)type;
-(void) TimeTest;


-(NSPoint) getPoint:(long) n;
-(NSPoint) getVertex:(long) n;
//-(void) getStatus:(int*[512]) mapStatus Index:(int*[512])mapVerticesIndex Group:(int*)mapGroup;
-(int) getStatus:(long**) mapStatus Index:(long**)mapVerticesIndex Group:(int*)mapGroup;


/////////////////////////////////////////
////  For draw process
//int mapStatus[128][512];
//int mapVerticesIndex[128][512];
//int mapGroup[128];
/////////////////////////////////////////


@end
