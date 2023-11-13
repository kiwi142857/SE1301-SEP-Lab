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
    return data[0];
}

int TreeNode::getY() {
    // TODO: Your code here
    return data[1];
}

TreeNode::~TreeNode() {
    // TODO: Your code here
    /*if(left!=nullptr)
    {
        delete left;
    }
    if(right!=nullptr)
    {
        delete right;
    }
    if(this!=nullptr)
    {
        delete this;
    }*/
}

istream &operator>>(istream &in, BinaryDimonTree &tree) {
    // TODO: Your code here
    int treeNum;
    in >> treeNum;
    for (int i = 0; i < treeNum; i++) {
        int x, y;
        in >> x >> y;
        
        bool num = 1;
        TreeNode **cur = &tree.root;
            while ((*cur) != NULL) {
                if ((*cur)->left!=NULL&&(*cur)->right!=NULL) tree.judge=0;
                if ( num) { if ((*cur)->getX() > x)cur = &(*cur)->left; else cur = &(*cur)->right; }
                if (!num) { if ((*cur)->getY() > y) cur = &(*cur)->left; else cur = &(*cur)->right; }
                num =!num;
            }
            *cur = new TreeNode(x, y);
    }
    
    return in;
}

BinaryDimonTree::BinaryDimonTree() {
    // TODO: Your code here
    root=nullptr;
    judge=1;
}

void BinaryDimonTree::clear(TreeNode*&node)
{
    if (node->left!=NULL)clear(node->left);
    if (node->right!=NULL)clear(node->right);
    if (node->left==NULL&&node->right==NULL){delete node;node=NULL;return;}
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y) {
    // TODO: Your code here
    
    if(root!=nullptr)
    {
        if(!judge) {
        unsigned long long int min_distance=LLONG_MAX;
        TreeNode *guess=nullptr;
        recur_search(root,x,y,min_distance,&guess,0);
        return guess;}

        else {
        unsigned long long int min_distance=LLONG_MAX;
        TreeNode*cur=root;
        TreeNode*ans=root;
        TreeNode**guess=&ans;
        while(cur!=nullptr)
        {
        unsigned long long int distance=(unsigned long long int)(cur->getX()-x)*(cur->getX()-x)+(unsigned long long int)(cur->getY()-y)*(cur->getY()-y);
        if(distance<min_distance)
        {
            min_distance=distance;
            *guess=cur;
        }
        if(distance==min_distance)
        {
            if(cur->getX()<(*guess)->getX())
            {
                min_distance=distance;
                *guess=cur;
            }
            else if(cur->getX()==(*guess)->getX())
            {
                if(cur->getY()<(*guess)->getY())
                {
                    min_distance=distance;
                    *guess=cur;
                }
            }
        }
            cur->left==nullptr? cur=cur->right:cur=cur->left;
        }
        return *guess;
        }

    }
    return nullptr;
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, unsigned long long int &min_distance, TreeNode **guess ,int num) {
    // TODO: Your code here
    

    if (cur==NULL) return;

    unsigned long long tmp=(x-cur->getX())*(x-cur->getX())+(y-cur->getY())*(y-cur->getY());
    if (tmp==min_distance)
    {
        if ((*guess)->getX()>cur->getX()){*guess=cur;min_distance=tmp;}
        if ((*guess)->getX()==cur->getX()&&(*guess)->getY()>cur->getY()){*guess=cur;min_distance=tmp;}
    }
    if (tmp<min_distance){*guess=cur;min_distance=tmp;}
    int sign=(num==0)?x:y;

    TreeNode*another=NULL;

    if (sign<cur->data[num]){recur_search(cur->left,x,y,min_distance,guess,(num+1)%2);another=cur->right;}
    else {recur_search(cur->right,x,y,min_distance,guess,(num+1)%2);another=cur->left;}
    if (min_distance>abs(cur->data[num]-sign))recur_search(another,x,y,min_distance,guess,(num+1)%2);
    return;
}


BinaryDimonTree::~BinaryDimonTree()
{
    // TODO: Your code here
    if(root!=nullptr)
    {
        clear(root);
    }
}
