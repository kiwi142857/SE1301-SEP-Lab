#pragma once

#include <iostream>

using namespace std;

class Canvas {
public:
    static const int HEIGHT = 11, WIDTH = 41;
    char buffer[HEIGHT][WIDTH];
    
    void draw() const {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                cout << buffer[i][j];
            cout << endl;
        }
    }
    
    void reset() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                buffer[i][j] = ' ';
    }

    void set()
    {
        for(int j=0;j<WIDTH;++j)
        {
            buffer[10][j]='-';
        }

        for(int num=1;num<4;++num)
        {
            int j=15*(num-1)+5;
            for (int i = 0; i < HEIGHT; i++)
                buffer[i][j] = '|';
        }
    }

    void setdata(int num,int no,int plate)
    {
        int j=15*(num-1)+5-plate-1;
        int i=9-2*no;
        for(;j<15*num-15+5+plate+2;++j)
        {  
           buffer[i][j] ='*';
        }
    }
};