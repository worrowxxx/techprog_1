#include "Base.h"
#include "Error.h"

Base::Base()
{
    name = "Не задано";
    cout << "Вызван конструктор без параметров класса Base" << endl;
}

Base::Base(const string& name)
{
    setName(name);
    cout << "Вызван конструктор с параметрами класса Base" << endl;
}

Base::Base(const Base& other)
{
    name = other.name;
    cout << "Вызван конструктор копирования класса Base" << endl;
}

Base::~Base()
{
    cout << "Вызван деструктор класса Base" << endl;
}

Base& Base::operator=(const Base& other)
{
    name = other.name;
    return *this;
}

void Base::setName(const string& name)
{
    if (name.empty())
        throw Error("ФИО не может быть пустым");
    this->name = name;
}

string Base::getName() const
{
    return name;
}

ostream& operator<<(ostream& out, const Base& obj)
{
    obj.print();
    return out;
}
