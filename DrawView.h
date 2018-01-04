//
//  DrawView.h
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef ALGORITHMTYPE
#define ALGORITHMTYPE
typedef enum AlgorithmType{
    boundingBox     = 0,
    quickHull       = 1,
    giftWrapping    = 2,
    grahamScan      = 3,
}AlgorithmType;
#endif

#import <Cocoa/Cocoa.h>

@interface DrawView : NSImageView{
    NSPoint *pointArray;
    NSPoint *verticesArray;
    
    NSInteger nPoint;
    NSInteger nVertices;

    bool showPoints;
    bool showVertices;
    bool showProcess;
    bool statusProcess;
    
    CGRect pageRect;
    CGContextRef context;
    
    double widthscalor,heightscalor;
    
    
    long (*mapStatus)[1024];
    long (*mapVerticesIndex)[1024];
    int *mapGroup;
    int step;
    int pointer;

    
    AlgorithmType algorithmTypetype;
    
}
-(void) Init;
-(void) EnablePoints:(NSPoint*) pA Number:(NSInteger) n;
-(void) EnableVertics:(NSPoint*) vA Number:(NSInteger) n;

-(void) EnableProcess:(NSPoint*) vA Number:(NSInteger) n Type:(AlgorithmType) type;
-(void) SetStatus:(long**)Status Index:(long**)VerticesIndex Group:(int*)Group Step:(int)step;

-(void) DrawPoint:(NSPoint) p;
-(void) MovePoint:(NSPoint) p;
-(void) DrawLinetoPoint:(NSPoint) p;

-(void) DrawBB;
-(void) DrawQH;
-(void) DrawGW;
-(void) DrawGS;
-(void) BBEnd;
-(void) QHEnd;
-(void) GWEnd;
-(void) GSEnd;
@end
