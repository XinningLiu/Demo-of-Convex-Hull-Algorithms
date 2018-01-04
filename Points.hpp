//
//  Points.hpp
//  RandomPointsandConvexHull
//
//  Created by 刘昕凝 on 3/21/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef Points_hpp
#define Points_hpp

#include <stdio.h>
#include <math.h>


class Cart2DPoint{
public:
    double x;
    double y;
    inline Cart2DPoint& operator=(Cart2DPoint c2){
        this->x = c2.x;
        this->y = c2.y;
        return *this;
    }
    inline bool operator!=(Cart2DPoint c2){
        if ((this->x!=c2.x)||(this->y!=c2.y))
            return true;
        return false;
    }
    inline Cart2DPoint operator-(Cart2DPoint c2){
        Cart2DPoint p;
        p.x = this->x-c2.x;
        p.y = this->y-c2.y;
        return p;
    }
    inline bool operator <(Cart2DPoint c2){
        if (x<c2.x) {
            return true;
        }
        if ((x==c2.x)&&(y<c2.y)) {
            return true;
        }
        return false;
    }
    inline bool operator >(Cart2DPoint c2){
        if (x>c2.x) {
            return true;
        }
        if ((x==c2.x)&&(y>c2.y)) {
            return true;
        }
        return false;
    }
    int LeftTest(Cart2DPoint start, Cart2DPoint end){
        double value;
        value = Det((end-start),(*this - start));
        
        if (value == 0)
            return 0;
        else if (value >0)
            return 1;
        else
            return -1;
    }

    int IsInTriangle(Cart2DPoint a, Cart2DPoint b, Cart2DPoint c){
        int s1,s2,s3;
        s1 = this->LeftTest(a, b);
        s2 = this->LeftTest(b, c);
        s3 = this->LeftTest(c, a);
        if (s1*s2*s3==0)
            return 0;
        else if ((s1+s2+s3)==3 || (s1+s2+s3)==-3)
            return 1;
        else
            return -1;
    }

    double Distance(Cart2DPoint a, Cart2DPoint b){
        return (fabs(Det(*this, a)+Det(b, *this)+Det(a, b))/sqrt((a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x)));
    }
    static inline double Det(Cart2DPoint a, Cart2DPoint b){
         return (a.x*b.y-a.y*b.x);
    }
};

class Polar2DPoint{
public:
    double Angle;
    double Radius;
    Polar2DPoint& operator=(Polar2DPoint c2){
        this->Angle = c2.Angle;
        this->Radius = c2.Radius;
        return *this;
    }
};

struct PointNode{
    Cart2DPoint point;
    long Index;
    bool operator<(PointNode c){
        return point<c.point;
    }
    bool operator>(PointNode c){
        return point>c.point;
    }
};
#endif /* Points_hpp */
