#include "Teacher.h"
#include "Error.h"
#include "Input.h"

Teacher::Teacher()
{
    groups = nullptr;
    groupCount = 0;
    subjects = nullptr;
    subjectCount = 0;
    cout << "Вызван конструктор без параметров класса Teacher" << endl;
}

Teacher::Teacher(const string& name, const string* groups, int groupCount, const string* subjects, int subjectCount)
    : Base(name)
{
    this->groups = nullptr;
    this->groupCount = 0;
    this->subjects = nullptr;
    this->subjectCount = 0;
    setGroups(groups, groupCount);
    setSubjects(subjects, subjectCount);
    cout << "Вызван конструктор с параметрами класса Teacher" << endl;
}

Teacher::Teacher(const Teacher& other) : Base(other)
{
    groups = nullptr;
    groupCount = 0;
    subjects = nullptr;
    subjectCount = 0;
    setGroups(other.groups, other.groupCount);
    setSubjects(other.subjects, other.subjectCount);
    cout << "Вызван конструктор копирования класса Teacher" << endl;
}

Teacher::~Teacher()
{
    delete[] groups;
    delete[] subjects;
    cout << "Вызван деструктор класса Teacher" << endl;
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        Base::operator=(other);
        setGroups(other.groups, other.groupCount);
        setSubjects(other.subjects, other.subjectCount);
    }
    return *this;
}

void Teacher::setGroups(const string* groups, int count)
{
    if (count < 1)
        throw Error("Преподаватель должен вести хотя бы одну группу");
    string* newGroups = new string[count];
    for (int i = 0; i < count; i++)
        newGroups[i] = groups[i];
    delete[] this->groups;
    this->groups = newGroups;
    groupCount = count;
}

void Teacher::setSubjects(const string* subjects, int count)
{
    if (count < 1)
        throw Error("Преподаватель должен вести хотя бы один предмет");
    string* newSubjects = new string[count];
    for (int i = 0; i < count; i++)
        newSubjects[i] = subjects[i];
    delete[] this->subjects;
    this->subjects = newSubjects;
    subjectCount = count;
}

int Teacher::getGroupCount() const
{
    return groupCount;
}

int Teacher::getSubjectCount() const
{
    return subjectCount;
}

string Teacher::getGroup(int index) const
{
    if (index < 0 || index >= groupCount)
        throw Error("Нет группы с таким номером");
    return groups[index];
}

string Teacher::getSubject(int index) const
{
    if (index < 0 || index >= subjectCount)
        throw Error("Нет предмета с таким номером");
    return subjects[index];
}

Base* Teacher::clone() const
{
    return new Teacher(*this);
}

void Teacher::input()
{
    setName(readLine("ФИО: "));

    int count = readInt("Сколько групп ведёт: ");
    if (count < 1)
        throw Error("Преподаватель должен вести хотя бы одну группу");
    string* list = new string[count];
    for (int i = 0; i < count; i++)
        list[i] = readLine("  Группа " + to_string(i + 1) + ": ");
    setGroups(list, count);
    delete[] list;

    count = readInt("Сколько предметов преподаёт: ");
    if (count < 1)
        throw Error("Преподаватель должен вести хотя бы один предмет");
    list = new string[count];
    for (int i = 0; i < count; i++)
        list[i] = readLine("  Предмет " + to_string(i + 1) + ": ");
    setSubjects(list, count);
    delete[] list;
}

void Teacher::print() const
{
    cout << "Преподаватель" << endl;
    cout << "  ФИО: " << getName() << endl;
    cout << "  Группы:";
    for (int i = 0; i < groupCount; i++)
        cout << " " << groups[i] << (i < groupCount - 1 ? "," : "");
    cout << endl;
    cout << "  Предметы:";
    for (int i = 0; i < subjectCount; i++)
        cout << " " << subjects[i] << (i < subjectCount - 1 ? "," : "");
    cout << endl;
}

void Teacher::save(ostream& out) const
{
    out << "Teacher" << endl;
    out << getName() << endl;
    out << groupCount << endl;
    for (int i = 0; i < groupCount; i++)
        out << groups[i] << endl;
    out << subjectCount << endl;
    for (int i = 0; i < subjectCount; i++)
        out << subjects[i] << endl;
}

void Teacher::load(istream& in)
{
    string name;
    getline(in, name);
    setName(name);

    int count;
    in >> count;
    in.ignore(10000, '\n');
    if (!in || count < 1)
        throw Error("Ошибка чтения групп преподавателя из файла");
    string* list = new string[count];
    for (int i = 0; i < count; i++)
        getline(in, list[i]);
    setGroups(list, count);
    delete[] list;

    in >> count;
    in.ignore(10000, '\n');
    if (!in || count < 1)
        throw Error("Ошибка чтения предметов преподавателя из файла");
    list = new string[count];
    for (int i = 0; i < count; i++)
        getline(in, list[i]);
    setSubjects(list, count);
    delete[] list;
}
