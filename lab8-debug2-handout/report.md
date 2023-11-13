# Bug Report

## Test Method:
   To test the project, which lacked explanatory note I initially skimmed through the entire codebase to understand its fundamental data structure - a ``Bplus-tree``.  
   I then compiled and ran the project using ``g++``, which resulted in a segmentation fault. Utilizing ``GDB``, I traced the issue to the ``find_leaf`` function. After reviewing and rectifying the error in this function, I re-ran the project and encountered no further errors. To ensure comprehensive testing, I modified the ``main`` function to test additional scenarios, such as splitting the tree, to uncover any potential issues.

## Problem 1:
   Type: logic bug / Run Time error.  
   Line 146: ``while (node->is_leaf) ``    
   Fix method: ``while (!node->is_leaf) ``    
   Reason: To get the leaf node, it should go to its child node until it becomes leaf node.

## Problem 2:
   Type: Run Time error.  
   Line 114: ``node_t *left = new node_t(up, true,left, this); ``    
   Fix method: ``node_t *left = new node_t(up, true, this->left, this); ``    
   Reason: The ``left`` should be referred to ``this`` 's own left.  

## Problem 3:
   Type: use‑after‑free  
   Line 303: ``delete next;``  
   Fix method: add ``next->down.erase(next->down.begin(), next->down.end());`` before ``delete next; ``
   Reason: The ``down`` in ``next`` refers to the same address of ``this->down``, we need to erase it before delete ``down``, or the data in ``this->down`` will be deleted too.

## Problem 4:
   Type: use‑after‑free    
   Line 303: ``delete node;``    
   Fix method: add ``node->down.erase(node->down.begin(), node->down.end());`` before ``delete node; ``
   Reason: The ``down`` in ``node`` refers to the same address of ``next->down``, we need to erase it before delete ``down``, or the data in ``next->down`` will be deleted too.

## Problem 5:
   Type: Memory leak.  
   Line 239: ``next->down.erase(next->down.begin(), next->down.end()); delete next;``  
   Fix method: add ``next->down.erase(next->down.begin(), next->down.end()); delete next;``   before ``for (int i = 0; i < next->up->down.size(); i++) {``  
   Reason: Memory leak of deleted node.  

## Problem 6:
   Type: Memory leak.  
   Line 239: ``node->down.erase(node->down.begin(), node->down.end()); delete node;``  
   Fix method: add ``node->down.erase(node->down.begin(), node->down.end()); delete node;``   before ``for (int i = 0; i < next->up->down.size(); i++) {``  
   Reason: Memory leak of deleted node.  