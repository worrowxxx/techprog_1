#include <iostream>
#include <windows.h>
#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Error.h"
#include "Input.h"
using namespace std;

// Ввод данных нового объекта и добавление его в контейнер
void addObject(Keeper& vuz, Base* obj)
{
    try
    {
        obj->input();
        vuz += obj;
        cout << "Объект добавлен" << endl;
    }
    catch (const Error&)
    {
        delete obj;
        throw;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Keeper vuz;
    int choice = -1;
    while (choice != 0)
    {
        cout << endl << "===== ВУЗ =====" << endl;
        cout << "1 - Добавить студента" << endl;
        cout << "2 - Добавить преподавателя" << endl;
        cout << "3 - Добавить сотрудника администрации" << endl;
        cout << "4 - Удалить объект" << endl;
        cout << "5 - Изменить объект" << endl;
        cout << "6 - Показать один объект" << endl;
        cout << "7 - Показать всех" << endl;
        cout << "8 - Сохранить в файл" << endl;
        cout << "9 - Загрузить из файла" << endl;
        cout << "0 - Выход" << endl;
        choice = readInt("Ваш выбор: ");

        try
        {
            switch (choice)
            {
            case 1:
                addObject(vuz, new Student());
                break;
            case 2:
                addObject(vuz, new Teacher());
                break;
            case 3:
                addObject(vuz, new Admin());
                break;
            case 4:
                vuz.print();
                vuz.remove(readInt("Номер объекта для удаления: ") - 1);
                cout << "Объект удалён" << endl;
                break;
            case 5:
                vuz.print();
                vuz.edit(readInt("Номер объекта для изменения: ") - 1);
                cout << "Объект изменён" << endl;
                break;
            case 6:
                cout << vuz[readInt("Номер объекта: ") - 1];
                break;
            case 7:
                vuz.print();
                break;
            case 8:
                vuz.save(readLine("Имя файла: "));
                cout << "Данные сохранены" << endl;
                break;
            case 9:
                vuz.load(readLine("Имя файла: "));
                cout << "Данные загружены, объектов: " << vuz.getCount() << endl;
                break;
            case 0:
                break;
            default:
                cout << "Нет такого пункта меню" << endl;
            }
        }
        catch (const Error& e)
        {
            cout << "Ошибка: " << e.getMessage() << endl;
        }
    }
    return 0;
}
