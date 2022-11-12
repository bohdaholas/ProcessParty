#include <stdexcept>
#include "validator.h"

Validator::Validator(int x, int y)
{
    setInterval(x, y);
}

bool Validator::insideInterval(int num)
{
    return a <= num && num <= b;
}


void Validator::setInterval(int x, int y)
{
    if (x == y) {
        throw std::runtime_error("start and end coincide!");
    }
    a = x;
    b = y;
}
