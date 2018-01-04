//
//  BasicStructure.hpp
//  RondomPoints
//
//  Created by 刘昕凝 on 2/28/16.
//  Copyright © 2016 Dolly. All rights reserved.
//

#ifndef BasicStructure_hpp
#define BasicStructure_hpp

#include <stdio.h>

class Node {
public:
    double Value;
    long Index;
    Node& operator=(Node c2){
        this->Value = c2.Value;
        this->Index = c2.Index;
        return *this;
    }
    bool operator>(Node c2){
        return (Value>c2.Value);
    }
    bool operator<(Node c2){
        return (Value<c2.Value);
    }
    bool operator==(Node c2){
        return (Value==c2.Value);
    }
    bool operator!=(Node c2){
        return (Value!=c2.Value);
    }
};

class NodeChain{
public:
    Node key;
    NodeChain* father;
    NodeChain* son;
    NodeChain(){
        key.Value = -1;
        key.Index = -1;
        father = nullptr;
        son = nullptr;
    }
    NodeChain(Node k){
        key = k;
        father = nullptr;
        son = nullptr;
    }
};

class Chain{
    NodeChain* Head;
    long Length;
public:
    Chain();
    Chain(long l, Node* n);
    ~Chain();
    void Insert(Node n, long position);
    void Delete(long position);
    Node GetPreNode(long position);
    Node GetSucNode(long Position);
    Node GetCurNode(long Position);
    void SetValue(long Position, double Value);
    long FindPosition(Node n);
    long GetLength(){return Length;}
};

class LongDC{
public:
    long index;
    LongDC* father;
    LongDC* son;
    
    LongDC* AddPoint(long p){
        LongDC *pointer = new LongDC(p);
        LongDC *pt = this->son;
        this->son = pointer;
        pointer->father = this;
        if(pt!=nullptr){
            pt->father = pointer;
            pointer->son = pt;
        }
        return pointer;
    }
    LongDC* RemovePoint(LongDC* p){
        LongDC *q = p->father,
        *r = p->son;
        p->father = nullptr;
        p->son = nullptr;
        delete p;
        if (q) {
            q->son = r;
        }
        if (r) {
            r->father = q;
        }
        return r;
    }
    
    
    LongDC(){
        father = nullptr;
        son = nullptr;
        index = -1;
    }
    LongDC(long p){
        father = nullptr;
        son = nullptr;
        index = p;
    }
    ~LongDC(){
        
        while (son) {
            RemovePoint(son);
        }

    }
};


#endif /* BasicStructure_hpp */
