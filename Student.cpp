#include "Student.h"
#include "Error.h"
#include "Input.h"

Student::Student()
{
    group = "Не задано";
    specialty = "Не задано";
    course = 1;
    averageScore = 5;
    cout << "Вызван конструктор без параметров класса Student" << endl;
}

Student::Student(const string& name, const string& group, const string& specialty, int course, double averageScore)
    : Base(name)
{
    setGroup(group);
    setSpecialty(specialty);
    setCourse(course);
    setAverageScore(averageScore);
    cout << "Вызван конструктор с параметрами класса Student" << endl;
}

Student::Student(const Student& other) : Base(other)
{
    group = other.group;
    specialty = other.specialty;
    course = other.course;
    averageScore = other.averageScore;
    cout << "Вызван конструктор копирования класса Student" << endl;
}

Student::~Student()
{
    cout << "Вызван деструктор класса Student" << endl;
}

Student& Student::operator=(const Student& other)
{
    Base::operator=(other);
    group = other.group;
    specialty = other.specialty;
    course = other.course;
    averageScore = other.averageScore;
    return *this;
}

void Student::setGroup(const string& group)
{
    if (group.empty())
        throw Error("Группа не может быть пустой");
    this->group = group;
}

void Student::setSpecialty(const string& specialty)
{
    if (specialty.empty())
        throw Error("Специальность не может быть пустой");
    this->specialty = specialty;
}

void Student::setCourse(int course)
{
    if (course < 1 || course > 6)
        throw Error("Курс должен быть от 1 до 6");
    this->course = course;
}

void Student::setAverageScore(double averageScore)
{
    if (averageScore < 2 || averageScore > 5)
        throw Error("Средний балл должен быть от 2 до 5");
    this->averageScore = averageScore;
}

string Student::getGroup() const
{
    return group;
}

string Student::getSpecialty() const
{
    return specialty;
}

int Student::getCourse() const
{
    return course;
}

double Student::getAverageScore() const
{
    return averageScore;
}

Base* Student::clone() const
{
    return new Student(*this);
}

void Student::input()
{
    setName(readLine("ФИО: "));
    setGroup(readLine("Группа: "));
    setSpecialty(readLine("Специальность: "));
    setCourse(readInt("Курс (1-6): "));
    setAverageScore(readDouble("Средний балл (2-5): "));
}

void Student::print() const
{
    cout << "Студент" << endl;
    cout << "  ФИО: " << getName() << endl;
    cout << "  Группа: " << group << endl;
    cout << "  Специальность: " << specialty << endl;
    cout << "  Курс: " << course << endl;
    cout << "  Средний балл: " << averageScore << endl;
}

void Student::save(ostream& out) const
{
    out << "Student" << endl;
    out << getName() << endl;
    out << group << endl;
    out << specialty << endl;
    out << course << endl;
    out << averageScore << endl;
}

void Student::load(istream& in)
{
    string name, group, specialty;
    int course;
    double averageScore;
    getline(in, name);
    getline(in, group);
    getline(in, specialty);
    in >> course >> averageScore;
    in.ignore(10000, '\n');
    if (!in)
        throw Error("Ошибка чтения данных студента из файла");
    setName(name);
    setGroup(group);
    setSpecialty(specialty);
    setCourse(course);
    setAverageScore(averageScore);
}
