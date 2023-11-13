#pragma once

#include <string>
#include<iostream>
#include<fstream>
#include<sstream>

using std::string;
using std::cout;
using std::endl;

class list{
private:
    string s1;
public:
    list* next;
    list (string s=0,list *n=NULL):s1(s),next(n){}
    string printlist(){return s1;}
};

class mylist{
private:
    list *head;
    list *p;
    
    int currentlineNum;
public:
    mylist() :p(NULL), currentlineNum(0) { head = new list("0"); };

    void writetofile(const string& filename)
    {
        int num=0;
        std::ofstream file;
        file.open(filename);
        if (!file) 
        {
            cout << "open error"<<endl;
            return;
        }

        list* temp = head->next;
        
        for (int i = 0; i < currentlineNum; ++i)
        {
            std::stringstream content;
            content << temp->printlist() << endl;
            
            file << content.str();
            string s1 = content.str();
            num += s1.size();
            temp = temp->next;
        }
        cout << num <<" byte(s) written"<< endl;
        file.close();
    }

    int getnum() { return currentlineNum; }
    void insert(const string &text){
         
        //寻找当前地址前一个结点


        if (!head->next) {
            list* temp = new list(text);
            ++currentlineNum;
            p = temp;
            head->next = p;
        }

        else
        {
            list* temp = head;
            while (temp->next != p) temp = temp->next;
            p = temp;

            temp = new list(text, p->next);
            p->next = temp;
            ++currentlineNum;
            p = p->next;
        }

    };

    void del(int &from, int &to){
        if (from > to) { cout << "? Delete range error" << endl; return; }
        if (to>currentlineNum) {cout<<"? Line number out of range"<<endl;return;}
        p = head;
        for(int i=0;i<from-1;++i)
        {
            p=p->next;
        }

        list* temp0 = p; p = p->next;
        for(int i=0;i<to-from+1;++i)
        {
            list* temp=p->next;
            delete p;
            p = temp;
            --currentlineNum;
        }
        temp0->next = p;
        if (p == NULL) 
        {
            if (head->next == NULL)
            {
                p = head->next;
                return;
            }

            p = head->next;
            while (p->next != NULL) p = p->next;

            return;
        }
        
    };
    
    void print(int &from,int &to) {
        
        if(from>to) {cout<<"? Number range error"<<endl;return;}
        if (to>currentlineNum) {cout<<"? Line number out of range"<<endl;return;}
        int line = from;
        p = head;
        for(int i=0;i<from-1;++i)
        {
            p=p->next;
        }

        for(int i=0;i<to-from+1;++i)
        {   
            p=p->next;
            cout<<line<<'\t'<<p->printlist() << endl;
            ++line;
        }
    };

    
    void appendLine(const string& text) {

        if (p == NULL)
        {
            insert(text); return;
        }

        list* temp = new list(text);
        temp->next = p->next;
        p->next = temp;
        ++currentlineNum;
        p = p->next;
    }

    string  movetoidx(int &idx){

        if (idx > currentlineNum) { return "? Line number out of range"; }
        p=head;
        
        for(int i=0;i<idx;++i)
        p=p->next;
        
        return p->printlist();
    }
    ~mylist(){
        
        if(head==NULL) return;

        list *p=head,*temp;
        while(p!=NULL)
        {
            temp=p->next;
            delete p;
            p=temp;
        }
    }
};

class Buffer {
private:
    int currentLineNum;
    // TODO: add a List here for storing the input lines
    mylist *l1;
public:
    Buffer();
    ~Buffer();
    int getnum() { return l1->getnum(); }

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx) const;

    void showLines(int from, int to) const;

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
