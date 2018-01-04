//
//  BasicStructure.cpp
//  RondomPoints
//
//  Created by 刘昕凝 on 2/28/16.
//  Copyright © 2016 Dolly. All rights reserved.
//

#include "BasicStructure.hpp"



Chain::Chain(){
    Length = 0;
    Head = new NodeChain;
}

Chain::Chain(long l, Node* n){
    Length = l;
    long i;
    Head = new NodeChain;
    NodeChain *p = Head;

    for(i=0;i<l;i++)
    {
        p->son = new NodeChain(n[i]);
        p = p->son;
    }
}
Chain::~Chain(){
    while (Head->son) {
        Delete(0);
    }
    delete Head;
}

void Chain::Insert(Node n, long position){
    long i;
    NodeChain *p,*qf;
    p = new NodeChain(n);

    qf = Head;
    if (position>Length) {
        position = Length;
    }
    for (i=0; i<position; i++) {
        qf=qf->son;
    }
    p->son = qf->son;
    if(qf->son!=nullptr)
        qf->son->father = p;
    p->father = qf;
    qf->son = p;
    Length++;
}
void Chain::Delete(long position){
    long i;
    NodeChain *p,*q;
    p = Head;
    for (i=0; i<position; i++) {
        p=p->son;
    }
    q=p->son;
    p->son = q->son;
    if(q->son!=nullptr)
        q->son->father = p;
    Length--;
    delete q;
}
Node Chain::GetSucNode(long position){
    long i;
    NodeChain *p=Head;
    for (i=0; i<position; i++) {
        p=p->son;
    }
    Node c;
    c = p->son->son->key;

    return c;
}
Node Chain::GetPreNode(long position){
    long i;
    NodeChain *p=Head;
    for (i=0; i<position; i++) {
        p=p->son;
    }
    Node c;
    c = p->key;

    return c;
}
Node Chain::GetCurNode(long position){
    long i;
    NodeChain *p=Head;
    for (i=0; i<position; i++) {
        p=p->son;
    }
    Node c;
    c = p->son->key;
    return c;
}

long Chain::FindPosition(Node n){
    NodeChain *p=Head;
    long i=0;
    while (p->son->key<n) {
        i++;
        p=p->son;
        if (i>=Length) {
            break;
        }
    }
    return i;
}
void Chain::SetValue(long position, double x){
    NodeChain *p=Head;
    long i=0;
    for (i=0; i<position; i++) {
        p=p->son;
    }
    p->son->key.Value = x;
}