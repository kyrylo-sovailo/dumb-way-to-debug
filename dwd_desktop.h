#pragma once
#include <iostream>

//Output stream
namespace DWD
{
    template<class T> inline void PRINT(T a) { std::cout << a; }
}

//Flash qualifier
#define DWD_FLASH(_STRING) _STRING

#include "dwd.h"