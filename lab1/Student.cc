#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"
using namespace std;

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();

    return "";
}

// TODO: implement functions which are declared in Student.h.
void Student::addClass(Class* c)
{
    classes.push_back(c);
}

double Undergraduate::getGrade()
{
    int i = 0; double score, point;
    double sum = 0,sumpoint=0;
    Class* c1;
    for (; i < classes.size(); ++i)
    {
        c1 = classes[i];
        sumpoint += c1->point;
        score = c1->getStudentWrapper(id).getScore();
        point = c1->point;
        sum += (score / 20.0) * point;
    }
    return sum / sumpoint;
}

double Graduate::getGrade()
{
    int i = 0; double score, point;
    double sum = 0,sumpoint=0;
    double score1;
    Class* c1;
    for (; i < classes.size(); ++i)
    {
        c1 = classes[i];
        score = c1->getStudentWrapper(id).getScore();
        point = c1->point;
        sumpoint += point;
        if (score >= 90)  score1 = 4.0;
        else if (score >= 80)  score1 = 3.5;
        else if (score >= 70)  score1 = 3.0;
        else if (score >= 60)  score1 = 2.5;
        else score1 = 2.0;

        sum += score1 * point;
    }
    return sum / sumpoint;
}