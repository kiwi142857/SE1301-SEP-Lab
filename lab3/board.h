#pragma once

#include "stack.h"

class Board {
    // TODO
    Stack<int> *s1,*s2,*s3,*s4;
    int disk_num;

public:
    Board(int num_disk):disk_num(num_disk){

        s1=new Stack<int>(num_disk);
        s2=new Stack<int>(num_disk);
        s3=new Stack<int>(num_disk);
        s4=new Stack<int>(20);

        for (int i=num_disk-1;i>=0;--i)
        {
            s1->push(i);
        }
    };

    ~Board();
    void hanoiplay(int n,int from,int to,int buffer);
    void draw();
    void move(int from, int to, bool log = true);
    bool win();
    void autoplay();
};
