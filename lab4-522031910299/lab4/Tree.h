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
class BinaryDimonTree;
class TreeNode
{
    friend istream &operator>>(istream &in, BinaryDimonTree &tree);
    friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2];
  TreeNode *left;
  TreeNode *right;

public:
  /* methods */
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */

  TreeNode(int X,int Y)
  {data[0]=X;data[1]=Y;left=right=NULL;}
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  void clear(TreeNode*&node);
  bool judge;

public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */

  void recur_search(TreeNode *cur,  long long x,  long long y, unsigned long long &min_distance, TreeNode **guess,int i);

  ~BinaryDimonTree();



};

#endif //C_BINARYDIMEN_TREE_H
