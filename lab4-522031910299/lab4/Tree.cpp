#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
ostream &operator<<(ostream &out, const TreeNode &b) {
    // TODO: Your code here
    return out;
}

int TreeNode::getX() {
    // TODO: Your code here
    return this->data[0];
}

int TreeNode::getY() {
    // TODO: Your code here
    return this->data[1];
}

TreeNode::~TreeNode() {
    // TODO: Your code here
}


istream &operator>>(istream &in, BinaryDimonTree &tree) {
    // TODO: Your code here
        int treeNum;
        in>>treeNum;
        for (int i=0;i<treeNum;i++) {
            int x, y;
            in >> x >> y;

            int ctr = -1;
          TreeNode **cur = &tree.root;
            while ((*cur) != NULL) {
                if ((*cur)->left!=NULL&&(*cur)->right!=NULL) tree.judge=0;
                if ( ctr==-1) { if ((*cur)->getX() > x)cur = &(*cur)->left; else cur = &(*cur)->right; }
                if (ctr==1) { if ((*cur)->getY() > y) cur = &(*cur)->left; else cur = &(*cur)->right; }
                ctr*=-1;
            }
            *cur = new TreeNode(x, y);
    }
    return in;
}

BinaryDimonTree::BinaryDimonTree() {
    // TODO: Your code here
    root=NULL;
    judge=1;
}


inline unsigned long long dist(long long x,long long y,long long u,long long v)
{
    return (x-u)*(x-u)+(y-v)*(y-v);
}

TreeNode *BinaryDimonTree::find_nearest_node(int  x, int y) {
    // TODO: Your code here
    if (!judge)
    {unsigned long long min_dist=dist(x,y,root->getX(),root->getY());
    TreeNode *Answer=root;
    TreeNode**answer=&Answer;
    int i=0;
    recur_search(root,x,y,min_dist,answer,i);
    return *answer;}
    
    else
    {
        TreeNode*cur=root;
        TreeNode*ans=root;
        TreeNode**guess=&ans;
        unsigned long long min_distance=(x-cur->getX())*(x-cur->getX())+(y-cur->getY())*(y-cur->getY());

        while (cur!=NULL)
        {
            unsigned long long tmp=(x-cur->getX())*(x-cur->getX())+(y-cur->getY())*(y-cur->getY());

            if (tmp==min_distance)
            {
                if ((*guess)->getX()>cur->getX()){*guess=cur;min_distance=tmp;}
                if ((*guess)->getX()==cur->getX()&&(*guess)->getY()>cur->getY()){*guess=cur;min_distance=tmp;}
            }
            if (tmp<min_distance){*guess=cur;min_distance=tmp;}

            if (cur->left!=NULL)cur=cur->left;else cur=cur->right;
        }
        return *guess;
    }
}

void BinaryDimonTree::recur_search(TreeNode *cur, long long x,long long y, unsigned long long &min_distance, TreeNode **guess,int i) {
    // TODO: Your code here

    if (cur==NULL) return;

    unsigned long long tmp=(x-cur->getX())*(x-cur->getX())+(y-cur->getY())*(y-cur->getY());
    if (tmp==min_distance)
    {
        if ((*guess)->getX()>cur->getX()){*guess=cur;min_distance=tmp;}
        if ((*guess)->getX()==cur->getX()&&(*guess)->getY()>cur->getY()){*guess=cur;min_distance=tmp;}
    }
    if (tmp<min_distance){*guess=cur;min_distance=tmp;}
    int sign=(i==0)?x:y;

    TreeNode*another=NULL;

    if (sign<cur->data[i]){recur_search(cur->left,x,y,min_distance,guess,(i+1)%2);another=cur->right;}
    else {recur_search(cur->right,x,y,min_distance,guess,(i+1)%2);another=cur->left;}
    if (min_distance>abs(cur->data[i]-sign))recur_search(another,x,y,min_distance,guess,(i+1)%2);
    return;
}

BinaryDimonTree::~BinaryDimonTree()
{
    // TODO: Your code here
    clear (root);
}

void BinaryDimonTree::clear(TreeNode*&node)
{
    if (node->left!=NULL)clear(node->left);
    if (node->right!=NULL)clear(node->right);
    if (node->left==NULL&&node->right==NULL){delete node;node=NULL;return;}
}

//int BinaryDimonTree::insert(int x,int y,TreeNode*p,int i) {
//    if (p == NULL) {
//        p = new TreeNode(x, y);
//        return 0;
//    }
//    int sign = (i == 0) ? x : y;
//    int flag = p->data[i];
//    if (sign < flag)//在左子树插入
//    {
//        insert(x,y,p->l,(i+1)%2);
//        int h1,h2;
//        if (p->l!=NULL) h1=p->l->height;else h1=0;
//        if (p->r!=NULL) h2=p->r->height;else h2=0;
//        p->height=1+(h1>h2)?h1:h2;
//        if (h1-h2==2)
//    }
//    else
//    {
//        insert(x,y,p->r,(i+1)%2);
//    }
//}