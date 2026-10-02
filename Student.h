#pragma once
#include "Base.h"

// Студент: ФИО, группа, специальность, курс, средний балл
class Student : public Base
{
private:
    string group;
    string specialty;
    int course;
    double averageScore;
public:
    Student();
    Student(const string& name, const string& group, const string& specialty, int course, double averageScore);
    Student(const Student& other);
    ~Student();
    Student& operator=(const Student& other);

    void setGroup(const string& group);
    void setSpecialty(const string& specialty);
    void setCourse(int course);
    void setAverageScore(double averageScore);
    string getGroup() const;
    string getSpecialty() const;
    int getCourse() const;
    double getAverageScore() const;

    Base* clone() const;
    void input();
    void print() const;
    void save(ostream& out) const;
    void load(istream& in);
};
