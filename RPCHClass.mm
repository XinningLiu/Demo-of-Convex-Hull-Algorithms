//
//  RPCHClass.m
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#import "RPCHClass.h"
#import "RandomPointsAndConvexHull.hpp"

struct ObjRPCHClass{
    RandomPointsAndConvexHull RPCH;
};


@implementation RPCHClass
- (id)init
{
    self = [super init];
    if (self) {
        //Allocate storage for members
        _cppRPCH = new ObjRPCHClass;
    }

    return self;
}

-(void) generalize:(long)n RandomPoints:(DataType)type{
    nPoint = n;
    _cppRPCH->RPCH.GeneralizeRandomPoints(n, type);
}
-(long) generalizeConvexHull:(AlgorithmType)type{
    nVertices = _cppRPCH->RPCH.GeneralizeConvexHull(type);
    return nVertices;
}
-(long) generalizeProcess:(AlgorithmType)type{
    nVertices = _cppRPCH->RPCH.GeneralizeProcess(type);
    return nVertices;
}


-(NSPoint) getPoint:(long) n{
    NSPoint p;
    Cart2DPoint pt = _cppRPCH->RPCH.GetPoint(n);
    p.x =  pt.x;
    p.y =  pt.y;
    return p;
}
-(NSPoint) getVertex:(long) n{
    NSPoint p;
    Cart2DPoint pt = _cppRPCH->RPCH.GetVertex(n);
    p.x =  pt.x;
    p.y =  pt.y;
    return p;
}

//-(void) getStatus:(int(*)[512]) mapStatus Index:(int(*)[512])mapVerticesIndex Group:(int*)mapGroup{
//    _cppRPCH->RPCH.CopyMap(mapStatus, mapVerticesIndex, mapGroup);
//}
-(int) getStatus:(long**) mapStatus Index:(long**)mapVerticesIndex Group:(int*)mapGroup{
    return _cppRPCH->RPCH.CopyMap((long(*)[1024])mapStatus, (long(*)[1024])mapVerticesIndex, mapGroup);
}


-(void) TimeTest{
    _cppRPCH->RPCH.TimeTest();
}
@end
