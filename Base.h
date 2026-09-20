#pragma once
#include <iostream>
#include <string>
using namespace std;

// Абстрактный базовый класс
class Base
{
private:
    string name;
public:
    Base();
    Base(const string& name);
    Base(const Base& other);
    virtual ~Base();
    Base& operator=(const Base& other);

    void setName(const string& name);
    string getName() const;

    virtual Base* clone() const = 0;            // создать копию объекта
    virtual void input() = 0;                   // ввод всех данных с клавиатуры
    virtual void print() const = 0;             // вывод на экран
    virtual void save(ostream& out) const = 0;  // запись в файл
    virtual void load(istream& in) = 0;         // чтение из файла
};

ostream& operator<<(ostream& out, const Base& obj);
