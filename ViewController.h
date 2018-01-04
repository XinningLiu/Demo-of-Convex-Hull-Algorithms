//
//  ViewController.h
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/20/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DrawView.h"
#import "RPCHClass.h"

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



@interface ViewController : NSViewController{
    NSInteger nPoint;
    NSInteger nVertices;
    RPCHClass *myRPCH;
    NSTimer *timer;
    NSPoint *pointArray;
    NSPoint *verticesArray;

    
    AlgorithmType algorithmType;
    DataType dataType;
    
    ///////////////////////////////////////
    //  For draw process
    long mapStatus[256][1024];
    long mapVerticesIndex[256][1024];
    int mapGroup[256];
    int step;
    ///////////////////////////////////////
}

@property (weak) IBOutlet NSButtonCell *DataTypeCluster;
@property (weak) IBOutlet NSButtonCell *DataTypeUniform;
@property (weak) IBOutlet NSButtonCell *DataTypeCircular;

@property (weak) IBOutlet NSButtonCell *AlgorithmBoundingBox;
@property (weak) IBOutlet NSButtonCell *AlgorithmQuickHull;
@property (weak) IBOutlet NSButtonCell *AlgorithmGiftWrapping;
@property (weak) IBOutlet NSButton *AlgorithmGrahamScan;

@property (weak) IBOutlet NSTextField *PointsNumber;

@property (weak) IBOutlet DrawView *myView;

-(void) startProcess;

@end

