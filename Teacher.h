#pragma once
#include "Base.h"

// Преподаватель: ФИО, список групп, которые ведёт, список предметов
class Teacher : public Base
{
private:
    string* groups;     // динамический массив групп
    int groupCount;
    string* subjects;   // динамический массив предметов
    int subjectCount;
public:
    Teacher();
    Teacher(const string& name, const string* groups, int groupCount, const string* subjects, int subjectCount);
    Teacher(const Teacher& other);
    ~Teacher();
    Teacher& operator=(const Teacher& other);

    void setGroups(const string* groups, int count);
    void setSubjects(const string* subjects, int count);
    int getGroupCount() const;
    int getSubjectCount() const;
    string getGroup(int index) const;
    string getSubject(int index) const;

    Base* clone() const;
    void input();
    void print() const;
    void save(ostream& out) const;
    void load(istream& in);
};
