#include "Class.h"
#include <string>
#include "Student.h"

void Class::addStudent(const Student& st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper& Class::getStudentWrapper(const std::string& studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
        it != students.end();
        ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No match student!";
}

double Class::getAvgScore()
{
    // TODO: implement getAvgScore.
    double sum = 0.0;
    for (int i = 0; i < students.size(); ++i)
    {
        sum += students[i].getScore();
    }
    return sum / students.size();
}
