#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"
#include<iomanip>

using namespace std;

class AppX {
private:
    vector<Student*> studentVec;
    vector<Class*> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class*>::iterator it = classVec.begin();
        it != classVec.end();
        ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto& s : studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student* st = nullptr;
    string clsname;
    int point;
    Class* cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            }
            else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);


        studentVec.push_back(st);
    }
    stfile.close();
    stfile.clear();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    ifstream clfile("./Classes.txt");

    while (getline(clfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;


        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.

        //Read the class name && point
        pos1 = 0;
        pos2 = line.find(':', pos1 + 1);
        bufv.push_back(line.substr(pos2 + 1, string::npos));
        getline(clfile, line);
        pos2 = line.find(':', pos1 + 1);
        bufv.push_back(line.substr(pos2 + 1, string::npos));
        point = atoi(bufv[1].c_str());
        cl = new Class(bufv[0], point);

        while (true) {
            getline(clfile, line);
            if (line[0] == '\0') break;
            else
            {
                for (int i = 0; i < studentVec.size(); ++i)
                {
                    if (line == studentVec[i]->id)
                    {
                        studentVec[i]->addClass(cl);
                        cl->addStudent(*studentVec[i]);
                        break;
                    }
                }
            }
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        classVec.push_back(cl);
    }
    clfile.close();
    // Hint: how is student information read?
}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    string sbuf;
    Class* cl;

    while (true) {
        std::cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class*>::iterator it = classVec.begin();
            it != classVec.end();
            ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            std::cout << "No match class!" << endl;
            continue;
        }

        while (true)
        {
            FLAG:
            std::cout << "Please input the student id (or input q to quit): ";
            cin >> sbuf;
            if (sbuf == "q")
                break;

            try{
            StudentWrapper &s1 = cl->getStudentWrapper(sbuf);
            }
            catch(const char* ch)
            {
                cout << ch << endl;
                goto FLAG;
            }
            cout<< cl->getStudentWrapper(sbuf).toString();
            std::cout << "Please input the student score: ";
            string score1;
            double score;
            cin>>score1;
            if (score1[0] == 'q') goto FLAG;
            else score = stod(score1);
            try{
                cl->getStudentWrapper(sbuf).setScore(score);
            }
            catch (const char* w1)
            {
                cout << w1 << endl;
                goto FLAG;
            }
        }
        // Hint: Take a look at printAvgScore().
    }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class* cl;
    double avg;

    while (true) {
        std::cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class*>::iterator it = classVec.begin();
            it != classVec.end();
            ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            std::cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        std::cout << "The average score is: " <<fixed<<setprecision(2) << avg << endl;
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    string id;
    Student* s1 = nullptr;
    while (true) {
        std::cout << "Please input the student id (or input q to quit): ";
        cin >> id;
        if (id == "q")
            break;

        s1 = nullptr;
        for (vector<Student*>::iterator it = studentVec.begin();
            it != studentVec.end();
            ++it) {
            if ((*it)->id == id) {
                s1 = *it;
                break;
            }
        }
        if (s1 == nullptr) {
            std::cout << "No match student!" << endl;
            continue;
        }
        std::cout << "GPA = " <<fixed << setprecision(2) << s1->getGrade() << endl;
    }


    // Hint: Take a look at printAvgScore().
}

int AppX::run()
{
    char cmd;
    while (true) {
        std::cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        }
        else if (cmd == 'a') {
            printAvgScore();
        }
        else if (cmd == 'g') {
            printGpa();
        }
        else if (cmd == 'q') {
            break;
        }
        else {
            std::cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
