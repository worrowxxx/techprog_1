#pragma once
#include "Base.h"

// Контейнер ВУЗа
class Keeper
{
private:
    Base** items;   // динамический массив указателей на объекты
    int count;
public:
    Keeper();
    Keeper(Base* first);
    Keeper(const Keeper& other);
    ~Keeper();
    Keeper& operator=(const Keeper& other);

    Keeper& operator+=(Base* obj);      // добавить объект в конец
    Base& operator[](int index);        // доступ к объекту по номеру

    int getCount() const;
    void remove(int index);
    void edit(int index);
    void print() const;
    void clear();
    void save(const string& fileName) const;
    void load(const string& fileName);
};
