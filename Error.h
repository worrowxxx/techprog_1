#pragma once
#include <string>
using namespace std;

// Класс исключения
class Error
{
private:
    string message;
public:
    Error(const string& message);
    string getMessage() const;
};
