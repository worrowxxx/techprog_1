#include "Input.h"
#include <iostream>
#include <cstdlib>

int readInt(const string& prompt)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && cin.peek() == '\n')
        {
            cin.ignore(10000, '\n');
            return x;
        }
        if (cin.eof())
            exit(0);
        cout << "Ошибка: нужно ввести целое число!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

double readDouble(const string& prompt)
{
    double x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && cin.peek() == '\n')
        {
            cin.ignore(10000, '\n');
            return x;
        }
        if (cin.eof())
            exit(0);
        cout << "Ошибка: нужно ввести число (дробная часть через точку)!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

string readLine(const string& prompt)
{
    string s;
    while (true)
    {
        cout << prompt;
        getline(cin, s);
        if (cin.eof())
            exit(0);
        if (!s.empty())
            return s;
        cout << "Ошибка: строка не может быть пустой!" << endl;
    }
}
