#include "Error.h"

Error::Error(const string& message)
{
    this->message = message;
}

string Error::getMessage() const
{
    return message;
}
