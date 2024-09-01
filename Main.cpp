#include <iostream>

#include "Library/Tween.h"

int main()
{
    Tween tween(10);

    std::cout << tween.GetValue() << std::endl;

    return 0;
}