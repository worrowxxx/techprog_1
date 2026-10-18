#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Error.h"
#include <fstream>

Keeper::Keeper()
{
    items = nullptr;
    count = 0;
    cout << "Вызван конструктор без параметров класса Keeper" << endl;
}

Keeper::Keeper(Base* first)
{
    items = nullptr;
    count = 0;
    *this += first;
    cout << "Вызван конструктор с параметрами класса Keeper" << endl;
}

Keeper::Keeper(const Keeper& other)
{
    items = nullptr;
    count = 0;
    for (int i = 0; i < other.count; i++)
        *this += other.items[i]->clone();
    cout << "Вызван конструктор копирования класса Keeper" << endl;
}

Keeper::~Keeper()
{
    clear();
    cout << "Вызван деструктор класса Keeper" << endl;
}

Keeper& Keeper::operator=(const Keeper& other)
{
    if (this != &other)
    {
        clear();
        for (int i = 0; i < other.count; i++)
            *this += other.items[i]->clone();
    }
    return *this;
}

Keeper& Keeper::operator+=(Base* obj)
{
    if (obj == nullptr)
        throw Error("Нельзя добавить пустой объект");
    // создаём массив на один элемент больше и переносим туда указатели
    Base** newItems = new Base*[count + 1];
    for (int i = 0; i < count; i++)
        newItems[i] = items[i];
    newItems[count] = obj;
    delete[] items;
    items = newItems;
    count++;
    return *this;
}

Base& Keeper::operator[](int index)
{
    if (index < 0 || index >= count)
        throw Error("Объекта с номером " + to_string(index + 1) + " не существует");
    return *items[index];
}

int Keeper::getCount() const
{
    return count;
}

void Keeper::remove(int index)
{
    if (index < 0 || index >= count)
        throw Error("Объекта с номером " + to_string(index + 1) + " не существует");
    delete items[index];
    // создаём массив на один элемент меньше без удалённого указателя
    Base** newItems = nullptr;
    if (count > 1)
    {
        newItems = new Base*[count - 1];
        for (int i = 0, j = 0; i < count; i++)
            if (i != index)
                newItems[j++] = items[i];
    }
    delete[] items;
    items = newItems;
    count--;
}

void Keeper::edit(int index)
{
    // правим копию, чтобы при ошибке ввода исходный объект остался целым
    Base* copy = (*this)[index].clone();
    try
    {
        copy->input();
    }
    catch (const Error&)
    {
        delete copy;
        throw;
    }
    delete items[index];
    items[index] = copy;
}

void Keeper::print() const
{
    if (count == 0)
    {
        cout << "Список пуст" << endl;
        return;
    }
    for (int i = 0; i < count; i++)
        cout << i + 1 << ". " << *items[i];
}

void Keeper::clear()
{
    for (int i = 0; i < count; i++)
        delete items[i];
    delete[] items;
    items = nullptr;
    count = 0;
}

void Keeper::save(const string& fileName) const
{
    ofstream out(fileName);
    if (!out)
        throw Error("Не удалось открыть файл \"" + fileName + "\" для записи");
    out << count << endl;
    for (int i = 0; i < count; i++)
        items[i]->save(out);
}

void Keeper::load(const string& fileName)
{
    ifstream in(fileName);
    if (!in)
        throw Error("Не удалось открыть файл \"" + fileName + "\" для чтения");
    int n;
    in >> n;
    in.ignore(10000, '\n');
    if (!in || n < 0)
        throw Error("Файл повреждён: неверное количество объектов");

    clear();
    for (int i = 0; i < n; i++)
    {
        string type;
        getline(in, type);
        Base* obj;
        if (type == "Student")
            obj = new Student();
        else if (type == "Teacher")
            obj = new Teacher();
        else if (type == "Admin")
            obj = new Admin();
        else
        {
            clear();
            throw Error("Файл повреждён: неизвестный тип объекта \"" + type + "\"");
        }
        try
        {
            obj->load(in);
        }
        catch (const Error&)
        {
            delete obj;
            clear();
            throw;
        }
        *this += obj;
    }
}
