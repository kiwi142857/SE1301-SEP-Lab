#include <iostream>
#include <string>
#include <climits>
#include<sstream>
#include "board.h"

using namespace std;

void districmd(Board & b,bool &flag)
{
    string input;
    while(1){
        cout<<"Move a disk. Format: x y"<<endl;
        getline(cin,input);
        if(input=="Q") {flag=1;break;}
        if(input[0]<4+'0' && input[1]==' ' && input[0]>='0' && input[2]<4+'0' && input[2]>='0' && input.size()<=3)
        {
          if(input[0]=='0' && input[2]=='0') {b.autoplay();cout<<"Congratulations! You win!"<<endl;break;}
          else 
          {
            int m = input[0] - '0', n = input[2] - '0';
            b.move(m,n,1); b.draw();
            if(b.win()) {cout<<"Congratulations! You win!"<<endl;break;}
          }
        }
        else{
            b.draw();
        }
    }
}

int main() {
    while (true) {
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        string input;
        getline(cin, input);
        if (input == "Q") {
            break;
        }
        // TODO
        else{
            stringstream cmd;
            cmd << input; //将字符串写入cmd
            int num_disk; 
            cmd >> num_disk; 
            if(num_disk>0 && num_disk<6) 
            {
               bool flag=0;
               Board board(num_disk);
               board.draw();
               
               districmd(board,flag);
               if(flag) break;
            }
            else continue;        
        }

    }
    return 0;
}
