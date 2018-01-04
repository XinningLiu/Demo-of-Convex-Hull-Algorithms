//
//  DrawView.m
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#import "DrawView.h"

//#define nStep 128
//#define nMax 512


@implementation DrawView

- (void)drawRect:(NSRect)rect {
    [super drawRect:rect];
    
    // Drawing code here.
    
    
    heightscalor = rect.size.height/2;
    widthscalor = rect.size.width/2;

    context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
    pageRect = CGRectMake(0, 0, rect.size.width, rect.size.height);
    
    CGContextBeginPage(context, &pageRect);
    
    //  Start with black fill and stroke colors
    //    CGContextSetRGBFillColor  (context, 0, 1, 0, 1);
    
    //  The current path for the context starts out empty
    assert(CGContextIsPathEmpty(context));
    
    CGContextTranslateCTM(context, rect.size.width/2, rect.size.height/2);
    
    long i;
    
    if (showPoints) {
        CGContextSetRGBStrokeColor(context, 1, 0, 0, 1);
        for (i=0; i<nPoint; i++) {
            [self DrawPoint:pointArray[i]];
            CGContextStrokePath(context);

        }
 //       CGContextStrokePath(context);
    }
    
    if (showVertices) {
        CGContextSetRGBStrokeColor(context, 0.5, 0, 1, 1);

        [self MovePoint:verticesArray[0]];
        
        for (i=0; i<nVertices; i++) {
            [self DrawLinetoPoint:verticesArray[i]];
        }
        [self DrawLinetoPoint:verticesArray[0]];
        
        CGContextStrokePath(context);
    }
    
    if (showProcess) {
        CGContextSetRGBStrokeColor(context, 0, 0, 0.5, 1);
        
        switch (algorithmTypetype) {
            case boundingBox:
                [self DrawBB];
                break;
            case quickHull:
                [self DrawQH];
                break;
            case giftWrapping:
                [self DrawGW];
                break;
            case grahamScan:
                [self DrawGS];
                break;
            default:
                break;
        }
        
        CGContextStrokePath(context);
    }
    
    if (statusProcess) {
        CGContextSetRGBStrokeColor(context, 0, 0, 0.5, 1);
        switch (algorithmTypetype) {
            case boundingBox:
                [self BBEnd];
                break;
            case quickHull:
                [self QHEnd];
                break;
            case giftWrapping:
                [self GWEnd];
                break;
            case grahamScan:
                [self GSEnd];
                break;
            default:
                break;
        }
        
        CGContextStrokePath(context);

    }
    
    CGContextEndPage(context);
    
    CGContextFlush(context);

    
    
}

-(void) Init{
    showPoints = false;
    showVertices = false;
    nPoint = 0;
    nVertices = 0;
}
-(void) EnablePoints:(NSPoint*) pA Number:(NSInteger) n{
    showPoints = true;
    showVertices = false;
    showProcess = false;
    statusProcess = false;
    nPoint = n;
    pointArray = pA;
}
-(void) EnableVertics:(NSPoint*) vA Number:(NSInteger) n{
    showVertices = true;
    showProcess = false;
    statusProcess = false;
    nVertices = n;
    verticesArray = vA;
}
-(void) EnableProcess:(NSPoint*) vA Number:(NSInteger) n Type:(AlgorithmType) type{
    showProcess = true;
    //showPoints = false;
    showVertices = false;
    nVertices = n;
    verticesArray = vA;
    
    algorithmTypetype = type;
    
    statusProcess = false;
}
-(void) SetStatus:(long**)Status Index:(long**)VerticesIndex Group:(int*)Group Step:(int)stp{
    mapStatus = (long(*)[1024])Status;
    mapVerticesIndex = (long(*)[1024])VerticesIndex;
    mapGroup = Group;
    step = stp;
    pointer = 0;
}
-(void) DrawPoint:(NSPoint)p{
    CGRect cRect;
    cRect = CGRectMake(p.x*widthscalor, p.y*heightscalor, 1, 1);
    CGContextAddRect(context, cRect);
//    CGContextStrokePath(context);
}
-(void) MovePoint:(NSPoint) p{
    CGContextMoveToPoint ( context, p.x*widthscalor, p.y*heightscalor);
}
-(void) DrawLinetoPoint:(NSPoint)p{
    CGContextAddLineToPoint( context, p.x*widthscalor, p.y*heightscalor );
}

-(void) DrawBB{
    long i;
    long group;
    for (i=0; i<nPoint; i++) {
        if (mapStatus[pointer][i]!=-1) {
            [self DrawPoint:pointArray[i]];
        }
    }
    [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
    for (i=1; mapVerticesIndex[pointer][i]>-1; i++) {
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i]]];
    }
    [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][0]]];
    
    group = i;
    for (i = 0; i<group/2; i++) {
        [self MovePoint:pointArray[mapVerticesIndex[pointer][i]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i+group/2]]];
    }
    
    
    pointer++;
    
    if (pointer==step-1) {
        showVertices = true;
        showPoints = true;
        showProcess = false;
        statusProcess = true;
    }
}
-(void) BBEnd{
    int i;
    int group;
    pointer = step-1;
    for (i=0; i<nPoint; i++) {
        if (mapStatus[pointer][i]!=-1) {
            [self DrawPoint:pointArray[i]];
        }
    }
    [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
    for (i=1; mapVerticesIndex[pointer][i]>-1; i++) {
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i]]];
    }
    [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][0]]];
    
    group = i;
    for (i = 0; i<group/2; i++) {
        [self MovePoint:pointArray[mapVerticesIndex[pointer][i]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i+group/2]]];
    }
}
-(void) DrawQH{
    int i/*,j*/;
    for (i=0; i<nPoint; i++) {
//        for (j=pointer; j<step; j++) {
//            if (mapStatus[0][i]==mapGroup[j]) {
//                [self DrawPoint:pointArray[i]];
//            }
//        }
        if (mapStatus[pointer][i]==1) {
            [self DrawPoint:pointArray[i]];
        }

    }
    
    
    
    [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
    for (i=1; mapVerticesIndex[pointer][i]>-1; i++) {
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i]]];
    }

    
    pointer++;
    
    if (pointer==step) {
        showVertices = true;
        showPoints = true;
        showProcess = false;
        statusProcess = true;
    }

}
-(void) QHEnd{
    int i;
//    int group;
    pointer = step-1;
//    group = mapGroup[pointer];
//    for (i=0; i<nPoint; i++) {
//        if (mapStatus[0][i]==group) {
//            [self DrawPoint:pointArray[i]];
//        }
//    }

    for (i=0; i<nPoint; i++) {

        if (mapStatus[pointer][i]==1) {
            [self DrawPoint:pointArray[i]];
        }
        
    }

    
    
    [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
    for (i=1; mapVerticesIndex[pointer][i]>-1; i++) {
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i]]];
    }

}
-(void) DrawGW{
    if (mapVerticesIndex[pointer][3]<0) {
        [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][1]]];

    }else if(mapVerticesIndex[pointer][4]<0) {
        [self MovePoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][0]]];
        [self MovePoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][2]]];
        [self MovePoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][3]]];
    }
    else{
        [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][2]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][3]]];
        [self MovePoint:pointArray[mapVerticesIndex[pointer][2]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][4]]];
    }

    pointer++;
    
    if (pointer==step-1) {
        showVertices = true;
        showPoints = true;
        showProcess = false;
        statusProcess = true;
    }
}
-(void) GWEnd{
    pointer = step-1;
    if (mapVerticesIndex[pointer][4]<0) {
        [self MovePoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][0]]];
        [self MovePoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][2]]];
        [self MovePoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][3]]];
    }
    else{
        [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][1]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][2]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][3]]];
        [self MovePoint:pointArray[mapVerticesIndex[pointer][2]]];
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][4]]];
    }
}
-(void) DrawGS{
    [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
    int i;
    for (i = 1; i<mapGroup[pointer]; i++) {
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i]]];
    }
    pointer++;
    
    if (pointer==step-1) {
        showVertices = true;
        showPoints = true;
        showProcess = false;
        statusProcess = true;
    }
}
-(void)GSEnd{
    pointer = step-1;
    [self MovePoint:pointArray[mapVerticesIndex[pointer][0]]];
    int i;
    for (i = 1; i<mapGroup[pointer]; i++) {
        [self DrawLinetoPoint:pointArray[mapVerticesIndex[pointer][i]]];
    }
}
@end
