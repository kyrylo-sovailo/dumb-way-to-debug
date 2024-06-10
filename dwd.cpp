#include "dwd_desktop.h"

std::vector<std::function<void()>> DWD::STACK;
int DWD::LOGLEVEL = 7;

void DWD::EXIT(int code)
{
    DWD::PRINT(DWD_FLASH("DWD_EXIT("));
    DWD::PRINT(code);
    DWD::PRINT(DWD_FLASH(") CALLED. UNWINDING STACK:\n"));
    for (auto f = DWD::STACK.begin(); f != DWD::STACK.end(); f++)
    {
        (*f)();
        DWD::PRINT('\n');
    }
    std::exit(code);
}