#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack(int size){
        this->size = size;
        this->index = 0;
        ptr = new int[size];
}

Stack::Stack(const Stack &s){
        size = s.size;
        this->index = s.index;
        ptr = new int[size];
        for (int i = 0; i < size; i++){
                ptr[i] = s.ptr[i];
        }
}

Stack::Stack(Stack &&s){
        size = s.size;
        this->index = s.index;
        ptr = s.ptr;
        // delete [] a nullptr is safe
        s.ptr = nullptr;
}

Stack::~Stack(){
        delete [] ptr;
}

Stack &Stack::operator=(const Stack &s){
        if (this == &s)
                return *this;

        ptr = new int[s.size];
        size = s.size;
        index = s.index;
        for (int i = 0; i < size; i++){
                ptr[i] = s.ptr[i];
        }

        return *this;
}

Stack &Stack::operator=(Stack &&s){
        *this = s;

        return *this;
}

void Stack::push(int val){
        if (index < size-1)
                ptr[index++] = val;
}

int Stack::pop(){
        if (!index)
                return -1;

        return ptr[--index];
}

int Stack::top(){
        if (!index)
                return -1;

        return ptr[index - 1];
}

bool Stack::empty(){
        return !index;
}