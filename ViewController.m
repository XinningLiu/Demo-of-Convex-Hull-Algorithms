//
//  ViewController.m
//  ShowConvexHull
//
//  Created by 刘昕凝 on 3/20/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#import "ViewController.h"

//#define nStep 256
//#define nMax 512

@implementation ViewController
- (IBAction)SetDataTypeCluster:(id)sender {
    [_DataTypeCluster setState:NSOnState];
    dataType = cluster;
    [_DataTypeUniform setState:NSOffState];
    [_DataTypeCircular setState:NSOffState];
}
- (IBAction)SetDataTypeUniform:(id)sender {
    [_DataTypeCluster setState:NSOffState];
    [_DataTypeUniform setState:NSOnState];
    dataType = uniform;
    [_DataTypeCircular setState:NSOffState];
}
- (IBAction)SetDataTypeCircular:(id)sender {
    [_DataTypeCluster setState:NSOffState];
    [_DataTypeUniform setState:NSOffState];
    [_DataTypeCircular setState:NSOnState];
    dataType = circular;
}
- (IBAction)SetAlgorithmBoundingBox:(id)sender {
    [_AlgorithmBoundingBox setState:NSOnState];
    algorithmType = boundingBox;
    [_AlgorithmQuickHull setState:NSOffState];
    [_AlgorithmGiftWrapping setState:NSOffState];
    [_AlgorithmGrahamScan setState:NSOffState];
}
- (IBAction)SetAlgorithmQuickHull:(id)sender {
    [_AlgorithmBoundingBox setState:NSOffState];
    [_AlgorithmQuickHull setState:NSOnState];
    algorithmType = quickHull;
    [_AlgorithmGiftWrapping setState:NSOffState];
    [_AlgorithmGrahamScan setState:NSOffState];
}
- (IBAction)SetAlgorithmGiftWrapping:(id)sender {
    [_AlgorithmBoundingBox setState:NSOffState];
    [_AlgorithmQuickHull setState:NSOffState];
    [_AlgorithmGiftWrapping setState:NSOnState];
    algorithmType = giftWrapping;
    [_AlgorithmGrahamScan setState:NSOffState];
}
- (IBAction)SetAlgorithmGrahamScan:(id)sender {
    [_AlgorithmBoundingBox setState:NSOffState];
    [_AlgorithmQuickHull setState:NSOffState];
    [_AlgorithmGiftWrapping setState:NSOffState];
    [_AlgorithmGrahamScan setState:NSOnState];
    algorithmType = grahamScan;
}
- (IBAction)TimeTest:(id)sender {
    [myRPCH TimeTest];
}

- (IBAction)ShowPoints:(id)sender {
    nPoint = [_PointsNumber integerValue];
    
    if ((nPoint<=0)||(nPoint>=2147483648)) {
        
        
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"Input number of points. Number of points should less than 2147483649.";
        //        NSAlert *alert = [NSAlert alertWithMessageText:@"Input number of points."
        //                                         defaultButton:@"OK"
        //                                       alternateButton:nil
        //                                           otherButton:nil
        //                             informativeTextWithFormat:@""];
        [alert runModal];
        
        
        return;
    }
    
    [myRPCH generalize: nPoint RandomPoints: dataType];
    
    long i;
    
    if (pointArray!=nil) {
        free(pointArray);
    }
    pointArray = (NSPoint*)malloc(sizeof(NSPoint) * nPoint);
    
    for (i = 0; i<nPoint; i++) {
        pointArray[i] = [myRPCH getPoint:i];
    }
    
//    pointArray = [myRPCH getRandomPoints];
    [_myView EnablePoints:pointArray Number: nPoint];
    [_myView setNeedsDisplay:YES];

}
- (IBAction)ShowConvexHull:(id)sender {
    if (pointArray!=nil) {
        nVertices = [myRPCH generalizeConvexHull:algorithmType];
        
        long i;
        if (verticesArray!=nil) {
            free(verticesArray);
        }
        verticesArray = (NSPoint*)malloc(sizeof(NSPoint) * nVertices);
        
        for (i=0; i<nVertices; i++) {
            verticesArray[i] = [myRPCH getVertex:i];
        }
        
        [_myView EnableVertics:verticesArray Number:nVertices];
        [_myView setNeedsDisplay:YES];
    }
    
}
- (IBAction)ShowProcess:(id)sender {
    if (pointArray!=nil) {
        if (nPoint>1022) {
            
            NSAlert *alert = [[NSAlert alloc] init];
            alert.messageText = @"In order to process the algorithm, Number of points should less than 1024.";

            [alert runModal];
            
            
            return;

        }
        
        
        nVertices = [myRPCH generalizeProcess:algorithmType];

        long i;
        if (verticesArray!=nil) {
            free(verticesArray);
        }
        verticesArray = (NSPoint*)malloc(sizeof(NSPoint) * nVertices);
        
        for (i=0; i<nVertices; i++) {
            verticesArray[i] = [myRPCH getVertex:i];
        }
        
        step = [myRPCH getStatus:(long**)mapStatus Index:(long**)mapVerticesIndex Group:mapGroup];
        [_myView EnableProcess:verticesArray Number:nVertices Type:algorithmType];
        [_myView SetStatus:(long**)mapStatus Index:(long**)mapVerticesIndex Group:mapGroup Step:step];
        timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(startProcess) userInfo:nil repeats: YES];
    }
}

-(void) startProcess{
    step --;
    if (step<0) {
        [timer invalidate];
    }
    [_myView setNeedsDisplay:YES];
//    long k;
//    k = [_myDrawView count];
//    
//    if (k<1) {
//        [timer invalidate];
//        [_myDrawView setFlag:3];
//        [_ShowConvexHull setEnabled:YES];
//    }
//    [_myDrawView setNeedsDisplay:YES];

}



- (void)viewDidLoad {
    [super viewDidLoad];
    myRPCH = [[RPCHClass alloc]init];
    [_DataTypeCluster setState:NSOnState];
    dataType = cluster;
    [_AlgorithmBoundingBox setState:NSOnState];
    algorithmType = boundingBox;


        pointArray = nil;
        verticesArray = nil;

    [_myView Init];
    // Do any additional setup after loading the view.
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end
