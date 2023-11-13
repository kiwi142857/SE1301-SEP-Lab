#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {l1=new mylist(); currentLineNum=0;}

Buffer::~Buffer() {delete l1;}

void Buffer::writeToFile(const string& filename) const { l1->writetofile(filename); }

void Buffer::showLines(int from, int to) const {l1->print(from,to);}

void Buffer::deleteLines(int from, int to){l1->del(from,to);}

void Buffer::insertLine(const string &text){l1->insert(text);}

void Buffer::appendLine(const string &text){l1->appendLine(text);}

const string &Buffer::moveToLine(int idx) const { 
    static string s1;
    s1= l1->movetoidx(idx);
    return s1;
}
