#pragma once

#include <cassert>
#include<iostream>

template <typename T> class Stack {
    // TODO

    T  *stack;
    int maxsize;
    int top_p;

    void doublespace()
    {
        T *temp=stack;
        stack=new T(2*maxsize);
        for(int i=0;i<maxsize;++i)
        stack[i]=temp[i];

        maxsize*=2;
        delete []temp;
    }
 public:
    Stack(int size=5):maxsize(size),top_p(0) {
        // TODO
        stack=new T[size];
    }
    
    ~Stack() {
        // TODO
        delete []stack;
    }
    
    int size() const {
        // TODO
        return top_p;
    }
    
    bool empty() const {
        return size() == 0;
    }
    
    void push(T t) {
        // TODO
        if(top_p==maxsize) doublespace();
        stack[++top_p]=t;
    }
    
    T pop() {
        // TODO
        if(empty()) 
        {   std::string error="The stack is empty!";
            throw error;  
        }
        T temp=stack[top_p--];
        return temp;
    }
    
    T& top() const {
        // TODO
        if(empty()) 
        {   std::string error="The stack is empty!";
            throw error;  
        }
        return stack[top_p];
    }
};
