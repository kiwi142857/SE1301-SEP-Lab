#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:
    const std::string name;
    const std::string year;
    Degree degree;
protected:
    std::vector <Class*>classes;
public:
    const std::string id;
    std::string toString() const;
    virtual double getGrade() = 0;
    void addClass(Class* c);
    Student() {};
    Student(std::string ID, std::string NAME, std::string YEAR, Degree d1) :id(ID), name(NAME), year(YEAR) { degree = d1; };
};

// TODO: implement class Graduate.
class Graduate :public Student {
public:
    double getGrade();
    Graduate(std::string ID, std::string NAME, std::string YEAR) :Student(ID, NAME, YEAR, graduate) {};
};
// TODO: implement class Undergraduate.
class Undergraduate :public Student {
public:
    double getGrade();
    Undergraduate(std::string ID, std::string NAME, std::string YEAR) :Student(ID, NAME, YEAR, undergraduate) {};
};

class StudentWrapper {
private:
    const Student& student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error  method:initial list
    StudentWrapper(const std::string& Id, const Student& student) :id(Id), student(student) {}

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Wrong score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
