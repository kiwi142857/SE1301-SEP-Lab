# Bug Report

[Test Method](#test-method)  
[Problem 1](#problem-1)  
[Problem 2](#problem-2)  
[Problem 3](#problem-3)  
[Problem 4](#problem-4)  
[Problem 5](#problem-5)  
[Problem 6](#problem-6)  
[Problem 7](#problem-7)  

## Test Method

   To test the project, which lacked explanatory note I initially skimmed through the entire codebase to understand its fundamental data structure - a ``Bplus-tree``.  
   I then compiled and ran the project using ``g++``, which resulted in a segmentation fault. Utilizing ``GDB``, I traced the issue to the ``find_leaf`` function. After reviewing and rectifying the error in this function, I re-ran the project and encountered no further errors. To ensure comprehensive testing, I modified the ``main`` function to test additional scenarios, such as splitting the tree, to uncover any potential issues.

## Problem 1

   Type: logic bug / Run Time error.  
   Line 146: ``while (node->is_leaf)``
   Fix method: ``while (!node->is_leaf)``
   Reason: To get the leaf node, it should go to its child node until it becomes leaf node.

## Problem 2

   Type: Run Time error.  
   Line 114: ``node_t *left = new node_t(up, true,left, this);``
   Fix method: ``node_t *left = new node_t(up, true, this->left, this);``
   Reason: The ``left`` should be referred to ``this`` 's own left.  

## Problem 3

   Type: use‑after‑free  
   Line 303: ``delete next;``  
   Fix method: add ``next->down.erase(next->down.begin(), next->down.end());`` before ``delete next;``
   Reason: The ``down`` in ``next`` refers to the same address of ``this->down``, we need to erase it before delete ``down``, or the data in ``this->down`` will be deleted too.

## Problem 4

   Type: use‑after‑free
   Line 303: ``delete node;``
   Fix method: add ``node->down.erase(node->down.begin(), node->down.end());`` before ``delete node;``
   Reason: The ``down`` in ``node`` refers to the same address of ``next->down``, we need to erase it before delete ``down``, or the data in ``next->down`` will be deleted too.

## Problem 5

   Type: Memory leak.  
   Line 239: ``next->down.erase(next->down.begin(), next->down.end()); delete next;``  
   Fix method: add ``next->down.erase(next->down.begin(), next->down.end()); delete next;``   after

   ``` C
   for (node_t *child : node->down) {
      child->up = node;
    } 
   ```

   Reason: Memory leak of deleted node.  

## Problem 6

   Type: Memory leak.  
   Line 239: ``node->down.erase(node->down.begin(), node->down.end()); delete node;``  
   Fix method: add ``node->down.erase(node->down.begin(), node->down.end()); delete node;``   after

   ``` C
   for (node_t *child : node->down) {
      child->up = node;
    } 
   ```

   Reason: Memory leak of deleted node.  

## Problem 7

   Type: Memory leak.
   Line 338: ``root->up = nullptr``;
   Fix method: add ``root->up->down.erase(root->up->down.begin(), root->up->down.end());delete root->up;`` before ``root->up = nullptr;`` .
   Reason: Memory leak of deleted node.

## Problem8

   Type: Run Time error & Use after free.
   Line:364 ``merge_node_with_left_leaf(node, prev);``
   Fix method: add ``node = prev`` after ``merge_node_with_left_leaf(node, prev);`` .
   Reason: The ``node`` should be ``prev`` after merge, or the recursive function will use the deleted node.

## Problem9

   Type: Run Time error & Use after free.
   Line:408 ``merge_node_with_left_internal (node, prev);``
   Fix method: add ``node = prev`` after ``merge_node_with_left_internal (node, prev);`` .
   Reason: The ``node`` should be ``prev`` after merge, or the recursive function will use the deleted node.

## Test Main Function

```C++
#include "tree.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>

void test_tree() {
  std::vector<int> numbers;
  for (int i = 0; i < 100; ++i) {
    // generate random numbers between 1 and 10000
    // require different numbers
    int number = std::rand() % 10000 + 1;
    while (std::find(numbers.begin(), numbers.end(), number) != numbers.end()) {
      number = std::rand() % 10000 + 1;
    }
    numbers.push_back(number);
  }

  std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});

  tree_t tree(100);
  for (const auto& number : numbers) {
    tree.set(number, number*10);
    assert(tree.get(number) == number*10);
  }

  std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});

  for (const auto& number : numbers) {
    assert(tree.get(number) == number*10);
  }

  std::shuffle(numbers.begin(), numbers.end(), std::mt19937{std::random_device{}()});

  // remove half of the numbers
  for (int i = 0; i < 50; ++i) {
    tree.remove(numbers[i]);
  }

  // test the remaining numbers
  for (int i = 50; i < 100; ++i) {
    assert(tree.get(numbers[i]) == numbers[i]*10);
  }
}

int main() {
  test_tree();
  return 0;
}
```
