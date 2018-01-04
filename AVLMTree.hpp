//
//  AVLMTree.hpp
//  ShowConvexHull
//
//  Created by 刘昕凝 on 4/2/16.
//  Copyright © 2016 Xinning Liu. All rights reserved.
//

#ifndef AVLMTree_hpp
#define AVLMTree_hpp

#include <stdio.h>
template<typename T>
class avlMNode
{
public:
    T key;
    unsigned long height;
    avlMNode* left;
    avlMNode* right;
    avlMNode* pre;
    avlMNode* suc;
    avlMNode(T k) {
        key = k;
        left = right = 0;
        pre = suc = 0;
        height = 1;
    }
    avlMNode(){
        left = right = 0;
        pre = suc = 0;
        height = 1;
        key.Index = -1;
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
    
    avlMNode* rotateright()
    {
        avlMNode* q = left;
        left = q->right;
        q->right = this;
        fixheight();
        q->fixheight();
        return q;
    }
    
    avlMNode* rotateleft()
    {
        avlMNode* p = right;
        right = p->left;
        p->left = this;
        this->fixheight();
        p->fixheight();
        return p;
    }
    
    avlMNode* balance() // balancing the p avlMNode
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
    avlMNode* insert(T k, avlMNode<T>** p) // insert k key in a tree with p root
    {
        if( k<key ){
            if (!left) {
                left = new avlMNode(k);
                (*p) = left;
                left->suc = this;
                left->pre = pre;
                
                if (pre) {
                    pre->suc  = left;
                }
                pre = left;

            }
            else left = left->insert(k,p);
        }
        else{
            if (!right) {
                right = new avlMNode(k);
                (*p) = right;
                right->pre = this;
                right->suc = suc;
                
                if (suc) {
                    suc->pre = right;
                }
                suc = right;
            }
            else right = right->insert(k,p);
        }
        return balance();
    }
    avlMNode* findmin() // find a avlMNode with minimal key in a p tree
    {
        return left?left->findmin():this;
    }
    avlMNode* findmax()
    {
        return right? right->findmax():this;
    }
    avlMNode* removemin() // deleting a avlMNode with minimal key from a p tree
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
class avlMTree{
    avlMNode<TS>* Head;
    long length;
public:
    avlMTree(TS k){
        Head=new avlMNode<TS>( k);
        length = 1;
    }
    avlMTree(){
        length = 0;
        Head = nullptr;
    }
    avlMNode<TS>* FindPosition(TS k, avlMNode<TS>** pfloor,avlMNode<TS>** pceiling){
        avlMNode<TS> *p=Head;
        *pfloor = nullptr;
        *pceiling = nullptr;
        while (p!=nullptr) {
            if (p->key ==k) {
                //if (p->left) {
                    *pfloor = p->pre;
                //}
                //if (p->right) {
                    *pceiling =p->suc;
                //}
                
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
    void init(TS sleft, TS sright){
        Head = new avlMNode<TS>;
        Head->left = new avlMNode<TS>(sleft);
        Head->right = new avlMNode<TS>(sright);
        Head->pre = Head->left;
        Head->suc = Head->right;
        Head->left->suc = Head;
        Head->right->pre = Head;
//        Head->key.Index = -1;
        Head->height = 2;
        length = 2;
    }
    void setHead(TS s){
        Head->key = s;
        Head->height = 2;
        length = 3;
    }
    
    avlMNode<TS>* Insert(TS k){
        avlMNode<TS>* p = nullptr;
        
        if (!Head) {
            Head = new avlMNode<TS>(k);
            length++;
            return Head;
        }
        Head = Head->insert(k,&p);
        length ++;
        return p;
    }
    void remove(avlMNode<TS>* p){
        avlMNode<TS>** qx=nullptr;
        avlMNode<TS> *q,*r, *ppre,*psuc;
        
        
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
        
        ppre = p->pre;
        psuc = p->suc;
        
        delete p;
        
        if (ppre) {
            ppre->suc = psuc;
        }
        if (psuc) {
            psuc->pre = ppre;
        }
        
        if( !r ){
            (*qx) = q;
        }
        else{
            avlMNode<TS>* min = r->findmin();
            min->right = r->removemin();
            min->left = q;
            (*qx) = min->balance();
        }
        length--;
    }
    long Iterate(long *array){
        long l = 0;
        if (length == 2) {
            array[0] = Head->left->key.Index;
            array[1] = Head->right->key.Index;
            return 2;
        }

        Head->Iterate(array,l);
        return l;
    }
    long Iterate(TS *array){
        long l = 0;
        if (length == -1) {
            array[0] = Head->left->key;
            array[1] = Head->right->key;
            return 2;
        }
        
        Head->Iterate(array,l);
        return l;
    }
    avlMNode<TS>* getMax(){
        if (length==2) {
            return Head->right;
        }
        return Head->findmax();
    }
    avlMNode<TS>* getMin(){
        if (length==2) {
            return Head->left;
        }
        return Head->findmin();
    }
    ~avlMTree(){
        while (Head!=nullptr) {
            remove(Head);
        }
    }
    long GetLength(){
        return length;
    }
    bool GetStatus(){
        if (Head->key.Index==-1) {
            return true;
        }
        return false;
    }
};

#endif /* AVLMTree_hpp */
