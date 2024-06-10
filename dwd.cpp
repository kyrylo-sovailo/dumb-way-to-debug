#include "dwd_desktop.h"

int DWD::LOGLEVEL = 7;
DWD::GUARD *DWD::TOP = nullptr;

DWD::GUARD::GUARD(std::function<void()> head) : head(head) { previous = TOP; TOP = this; }
DWD::GUARD::~GUARD() { TOP = previous; }

void DWD::EXIT(int code)
{
    DWD::PRINT(DWD_FLASH("DWD_EXIT("));
    DWD::PRINT(code);
    DWD::PRINT(DWD_FLASH(") CALLED. UNWINDING STACK:\n"));
    for (auto guard = DWD::TOP; guard != nullptr; guard = guard->previous)
    {
        guard->head();
        DWD::PRINT('\n');
    }
    std::exit(code);
}