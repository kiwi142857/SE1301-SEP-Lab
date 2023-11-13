#include "lexicon.h"
#include <iostream>
#include <list>
using namespace std;

class Boggle {

private:
  int rows;
  int cols;
  Lexicon lex;
  char board[5][5];
  bool boardVisited[5][5];
  list<string> words;
  bool findWord(string word, int x, int y);
  bool findWord(string word);
  bool findOtherWord(int x, int y, string word);
public:
  Boggle();
  Boggle(int rows, int cols);
  Lexicon computerWords;
  int computerScore;
  int score;
  void readBoard();
  void printBoard();
  bool getOperations();
  void findOtherWord();
};

Boggle::Boggle() {
  // TODO
  lex.addWordsFromFile("./EnglishWords.txt");
  score=0;
}

Boggle::Boggle(int rows, int cols) {
  // TODO
  lex.addWordsFromFile("./EnglishWords.txt");
  score=0;
}

void Boggle::printBoard() {
  // TODO
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      cout<<board[i][j];
    }
    cout<<endl;
  }
  cout<<"Your Score: "<<score<<endl;
  cout<<"Your Words: ";
  for(string word: words) {
    cout<<word<<" ";
  }
}

bool Boggle::getOperations() {
  // TODO
  string word;
  while(true) {
    cin>>word;
    //判断是否结束输入
    if(word=="???") return false;
    //判断是否有四个字母长
    if(word.length()<4) {
      cout<<word<<" is too short."<<endl;
      continue;
    }
    //判断是否在字典中
    if(!lex.contains(word)) {
      cout<<word<<" is not a word."<<endl;
    }
    //判断是否在棋盘上存在一条路径
    if(!findWord(word)){
      cout<<word<<" is not on board."<<endl;
    }
    //判断单词是否已经出现过
    bool flag=false;
    for(string w: words) {
      if(w==word) {
        flag=true;
        break;
      }
    }
    if(flag) {
      cout<<word<<"is already found."<<endl;
    }
    else {
      words.push_back(word);
      score+=word.length()-3;
    }
    printBoard();
  }
}

bool Boggle::findWord(string word) {
  // TODO
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      if(findWord(word, i, j)) return true;
    }
  }
  return false;
}

bool Boggle::findWord(string word, int x, int y) {
  // TODO
  if(word.length()==0) return true;
  if(x<0||x>=rows||y<0||y>=cols) return false;
  if(boardVisited[x][y]) return false;
  if(board[x][y]!=word[0]) return false;
  boardVisited[x][y]=true;
  if(findWord(word.substr(1), x-1, y-1)) return true;
  if(findWord(word.substr(1), x-1, y)) return true;
  if(findWord(word.substr(1), x-1, y+1)) return true;
  if(findWord(word.substr(1), x, y-1)) return true;
  if(findWord(word.substr(1), x, y+1)) return true;
  if(findWord(word.substr(1), x+1, y-1)) return true;
  if(findWord(word.substr(1), x+1, y)) return true;
  if(findWord(word.substr(1), x+1, y+1)) return true;
  boardVisited[x][y]=false;
  return false;
}

void Boggle::readBoard() {
  // TODO
  cin>>rows; cols=rows;
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      cin>>board[i][j];
    }
  }
}

void Boggle::findOtherWord() {
  // TODO
  string word;
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      findOtherWord(i, j, word);
    }
  }
}

bool Boggle::findOtherWord(int x, int y, string word) {
  //找出board上剩余的四个字母及以上的单词
  //并且打印出来
  if(x<0||x>=rows||y<0||y>=cols) return false;
  if(boardVisited[x][y]) return false;
  boardVisited[x][y]=true;
  word+=board[x][y];
  if(word.length()>=4) {
    if(lex.contains(word)) {
      computerWords.add(word);
    }
  }
  if(findOtherWord(x-1, y-1, word)) return true;
  if(findOtherWord(x-1, y, word)) return true;
  if(findOtherWord(x-1, y+1, word)) return true;
  if(findOtherWord(x, y-1, word)) return true;
  if(findOtherWord(x, y+1, word)) return true;
  if(findOtherWord(x+1, y-1, word)) return true;
  if(findOtherWord(x+1, y, word)) return true;
  if(findOtherWord(x+1, y+1, word)) return true;
  boardVisited[x][y]=false;
  return false;
}

int main() {
  // TODO
  Boggle boggle;
  boggle.readBoard();
  boggle.printBoard();
  if(!boggle.getOperations()) {
    boggle.findOtherWord();
    cout<<"Computer Score: "<<boggle.computerScore<<endl;
    cout<<"Computer Words: ";
    //string转化成大写的函数
    string word_upper;
    for(string word: boggle.computerWords) {
      for(char c: word) {
        word_upper+=toupper(c);
      }
      cout<<word_upper<<" ";
      word_upper="";
    }
  }
  return 0;
}
