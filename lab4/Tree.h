//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2];
  

public:
  /* methods */
  TreeNode *left;
  TreeNode *right;
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  TreeNode(int x, int y){data[0]=x;data[1]=y;left=right=NULL;} /* DO NOT CHANGE */;
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  int judge; //判断是否退化为链表
public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  void clear(TreeNode*&node);
  void recur_search(TreeNode *cur, int x, int y, unsigned long long int &min_distance, TreeNode **guess, int num);
  ~BinaryDimonTree();
  
};

#endif //C_BINARYDIMEN_TREE_H
