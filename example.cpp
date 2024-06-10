#include "dwd_desktop.h"

int simple_add(int a, int b)
{
    return a + b;
}

DWD_PRINT_TRACE(int, print_add, int, a, int, b)
{
    return a + b;
}
DWD_END()

DWD_CATCH_TRACE(int, catch_add, int, a, int, b)
{
    if (a > 100 || b > 100) DWD::EXIT(1);
    return a + b;
}
DWD_END()

int main()
{
    simple_add(1, 2);
    print_add(1, 2);
    catch_add(1, 2);
    catch_add(100, 200);
    return 0;
}