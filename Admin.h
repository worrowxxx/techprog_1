#pragma once
#include "Base.h"

// Административный персонал: ФИО, должность, телефон, область ответственности
class Admin : public Base
{
private:
    string position;
    string phone;
    string responsibility;
public:
    Admin();
    Admin(const string& name, const string& position, const string& phone, const string& responsibility);
    Admin(const Admin& other);
    ~Admin();
    Admin& operator=(const Admin& other);

    void setPosition(const string& position);
    void setPhone(const string& phone);
    void setResponsibility(const string& responsibility);
    string getPosition() const;
    string getPhone() const;
    string getResponsibility() const;

    Base* clone() const;
    void input();
    void print() const;
    void save(ostream& out) const;
    void load(istream& in);
};
