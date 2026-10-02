#include "Admin.h"
#include "Error.h"
#include "Input.h"

Admin::Admin()
{
    position = "Не задано";
    phone = "Не задано";
    responsibility = "Не задано";
    cout << "Вызван конструктор без параметров класса Admin" << endl;
}

Admin::Admin(const string& name, const string& position, const string& phone, const string& responsibility)
    : Base(name)
{
    setPosition(position);
    setPhone(phone);
    setResponsibility(responsibility);
    cout << "Вызван конструктор с параметрами класса Admin" << endl;
}

Admin::Admin(const Admin& other) : Base(other)
{
    position = other.position;
    phone = other.phone;
    responsibility = other.responsibility;
    cout << "Вызван конструктор копирования класса Admin" << endl;
}

Admin::~Admin()
{
    cout << "Вызван деструктор класса Admin" << endl;
}

Admin& Admin::operator=(const Admin& other)
{
    Base::operator=(other);
    position = other.position;
    phone = other.phone;
    responsibility = other.responsibility;
    return *this;
}

void Admin::setPosition(const string& position)
{
    if (position.empty())
        throw Error("Должность не может быть пустой");
    this->position = position;
}

void Admin::setPhone(const string& phone)
{
    // телефон: только цифры, в начале может быть '+'
    if (phone.empty())
        throw Error("Телефон не может быть пустым");
    for (int i = 0; i < (int)phone.size(); i++)
    {
        if (phone[i] == '+' && i == 0)
            continue;
        if (phone[i] < '0' || phone[i] > '9')
            throw Error("Телефон должен состоять только из цифр (в начале можно '+')");
    }
    this->phone = phone;
}

void Admin::setResponsibility(const string& responsibility)
{
    if (responsibility.empty())
        throw Error("Область ответственности не может быть пустой");
    this->responsibility = responsibility;
}

string Admin::getPosition() const
{
    return position;
}

string Admin::getPhone() const
{
    return phone;
}

string Admin::getResponsibility() const
{
    return responsibility;
}

Base* Admin::clone() const
{
    return new Admin(*this);
}

void Admin::input()
{
    setName(readLine("ФИО: "));
    setPosition(readLine("Должность: "));
    setPhone(readLine("Телефон: "));
    setResponsibility(readLine("Область ответственности: "));
}

void Admin::print() const
{
    cout << "Административный персонал" << endl;
    cout << "  ФИО: " << getName() << endl;
    cout << "  Должность: " << position << endl;
    cout << "  Телефон: " << phone << endl;
    cout << "  Область ответственности: " << responsibility << endl;
}

void Admin::save(ostream& out) const
{
    out << "Admin" << endl;
    out << getName() << endl;
    out << position << endl;
    out << phone << endl;
    out << responsibility << endl;
}

void Admin::load(istream& in)
{
    string name, position, phone, responsibility;
    getline(in, name);
    getline(in, position);
    getline(in, phone);
    getline(in, responsibility);
    if (!in)
        throw Error("Ошибка чтения данных сотрудника из файла");
    setName(name);
    setPosition(position);
    setPhone(phone);
    setResponsibility(responsibility);
}
