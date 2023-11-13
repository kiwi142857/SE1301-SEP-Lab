#include "board.h"
#include "canvas.h"

Board::~Board() {
    // TODO
    delete s1;
    delete s2;
    delete s3;
    delete s4;
}

void Board::draw() {
    Canvas canvas;
    canvas.reset();
    canvas.set();
    
    Stack<int> temp(disk_num);int i=0;
    while(!s1->empty())
    {   
        int m=s1->pop();
        temp.push(m);
    }

    while(!temp.empty())
    {
        int plate=temp.pop();
        canvas.setdata(1,i++,plate);
        s1->push(plate);
    }
    i=0;
    
    while(!s2->empty())
    {
        temp.push(s2->pop());
    }

    while(!temp.empty())
    {
        int plate=temp.pop();
        canvas.setdata(2,i++,plate);
        s2->push(plate);
    }
    i=0;

    while(!s3->empty())
    {
        temp.push(s3->pop());
    }

    while(!temp.empty())
    {
        int plate=temp.pop();
        canvas.setdata(3,i++,plate);
        s3->push(plate);
    }
    i=0;
    
    canvas.draw();
    // TODO
}

void Board::move(int from, int to, bool log) {
    // TODO

    //判断输入对应移动的柱子

    Stack<int>* sf=NULL;Stack<int>* st=NULL;
    int m, n;
    switch (from)
    {
        case 1:  sf=s1;break;
        case 2:  sf=s2;break;
        case 3:  sf=s3;break;
    }

    switch (to)
    {
        case 1:  st=s1;break;
        case 2:  st=s2;break;
        case 3:  st=s3;break;
    }
    try{
        m = sf->top();
    }
    catch(string error) { return; }

    try 
    { n = st->top(); }
    catch (string error) 
    { n = 5; }
    if(m>n){return;}
    try{st->push(sf->top());}
    catch(string error){
       throw error;
    }
    sf->pop();

    if(log) {s4->push(from);s4->push(to);}
}

bool Board::win() {
    // TODO
    if(s1->empty() && s3->empty()) return 1;
    return 0;
}

void Board::hanoiplay(int n,int from,int buffer,int to)
{
     if (n == 1) {                          //如果只有一个盘子，直接从from移动到to
        cout<<"Auto moving:"<<from<<"->"<<to<<endl;
        move(from,to,0);
        draw();
    } else {                                //否则，分三步进行
        hanoiplay(n-1, from, to,buffer );   //先将n-1个盘子从from移动到buffer，借助to
        cout<<"Auto moving:"<<from<<"->"<<to<<endl;
        move(from,to,0);                    //再将最大的盘子从from移动到to
        draw();
        hanoiplay(n-1, buffer, from, to);   //最后将n-1个盘子从buffer移动到to，借助from
    }
}

void Board::autoplay() {
    // TODO
    
    //回退步骤
    while(!s4->empty())
    {
        int from=s4->pop(),to=s4->pop();
        cout<<"Auto moving:"<<from<<"->"<<to<<endl;
        move(from,to,0);
        draw();
    }

    //操作步骤
    hanoiplay(disk_num,1,3,2);
}
