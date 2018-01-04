//
//  AVLTree.hpp
//  RondomPoints
//
//  The code is modified from http://kukuruku.co/hub/cpp/avl-trees, which is
//  written by Nikolai Ershov
//
//  Created by 刘昕凝 on 4/2/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.


#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <stdio.h>

template<typename T>
class avlNode
{
public:
    T key;
    unsigned long height;
    avlNode* left;
    avlNode* right;
    avlNode(T k) { key = k; left = right = 0; height = 1; }
    avlNode(){
        left = right = 0; height = 1;
    }
    
    unsigned long getHeight(){
        return height;
    }
    
    long bfactor()
    {
        return (right?right->height:0)-(left?left->height:0);
    }
    
    void fixheight()
    {
        unsigned long hl = left?left->height:0;
        unsigned long hr = right?right->height:0;
        height = (hl>hr?hl:hr)+1;
    }
    
    avlNode* rotateright()
    {
        avlNode* q = left;
        left = q->right;
        q->right = this;
        fixheight();
        q->fixheight();
        return q;
    }
    
    avlNode* rotateleft()
    {
        avlNode* p = right;
        right = p->left;
        p->left = this;
        this->fixheight();
        p->fixheight();
        return p;
    }
    
    avlNode* balance() // balancing the p avlNode
    {
        fixheight();
        if( bfactor()==2 )
        {
            if( right->bfactor() < 0 )
                right = right->rotateright();
            return rotateleft();
        }
        if( bfactor()==-2 )
        {
            if( left->bfactor() > 0  )
                left = left->rotateleft();
            return rotateright();
        }
        return this; // balancing is not required
    }
    avlNode* insert(T k) // insert k key in a tree with p root
    {
        if( k<key ){
            left = left? left->insert(k) : new avlNode(k);
        }
        else{
            right = right? right->insert(k): new avlNode(k);
            
        }
        return balance();
    }
    avlNode* findmin() // find a avlNode with minimal key in a p tree
    {
        return left?left->findmin():this;
    }
    avlNode* findmax()
    {
        return right? right->findmax():this;
    }
    avlNode* removemin() // deleting a avlNode with minimal key from a p tree
    {
        if( !left )
            return right;
        left = left -> removemin();
        return balance();
    }
    void Iterate(long* array, long &l){
        if (left) {
            left->Iterate(array,l);
        }
        array[l] = key.Index;
        l++;
        if (right) {
            right->Iterate(array,l);
        }
    }
    void Iterate(T *array, long &l){
        if (left) {
            left->Iterate(array,l);
        }
        array[l] = key;
        l++;
        if (right) {
            right->Iterate(array,l);
        }
    }
};

template<typename TS>
class avlTree{
    avlNode<TS>* Head;
    long length;
public:
    avlTree(TS k){
        Head=new avlNode<TS>( k);
        length = 1;
    }
    avlTree(){
        length = 0;
        Head = nullptr;
    }
    avlNode<TS>* FindPosition(TS k, avlNode<TS>** pfloor,avlNode<TS>** pceiling){
        avlNode<TS> *p=Head;
        *pfloor = nullptr;
        *pceiling = nullptr;
        while (p!=nullptr) {
            if (p->key ==k) {
                if (p->left) {
                    *pfloor = p->left->findmax();
                }
                if (p->right) {
                    *pceiling =p->right->findmin();
                }
                
                return p;
            }
            if (k < p->key) {
                *pceiling = p;
                p = p->left;
            }
            else {
                *pfloor = p;
                p = p->right;
            }
        }
        return p;
    }
    void Insert(TS k){
        if (!Head) {
            Head = new avlNode<TS>(k);
            length++;
            return;
        }
        Head = Head->insert(k);
        length ++;
    }
    void remove(avlNode<TS>* p){
        avlNode<TS>** qx=nullptr;;
        avlNode<TS> *q,*r;
        q = Head;
        
        do{
            if (q->left) {
                if (p->key<q->key) {
                    qx = & q->left;
                    q = q->left;
                }
            }
            if (q->right) {
                if (p->key>q->key) {
                    qx = &q->right;
                    q =q->right;
                }
                
            }
        }while (p!=q);
        if (qx==nullptr) {
            qx = &Head;
        }
        
        q = p->left;
        r = p->right;
        delete p;
        
        
        if( !r ){
            *qx = q;
        }
        else{
            avlNode<TS>* min = r->findmin();
            min->right = r->removemin();
            min->left = q;
            *qx = min->balance();
        }
        length--;
    }
    long Iterate(long *array){
        long l = 0;
        Head->Iterate(array,l);
        return l;
    }
    long Iterate(TS *array){
        long l = 0;
        Head->Iterate(array,l);
        return l;
    }
    avlNode<TS>* getMax(){
        return Head->findmax();
    }
    avlNode<TS>* getMin(){
        return Head->findmin();
    }
    ~avlTree(){
        while (Head!=nullptr) {
            remove(Head);
        }
    }
    long GetLength(){
        return length;
    }
};




#endif /* AVLTree_hpp */
