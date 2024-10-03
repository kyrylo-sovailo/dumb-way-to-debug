#include "dwd_desktop.h"

DWD_TRACE(int, function, int, a, int, b)
{
    return a + b;
}
DWD_END()

DWD_TRACE_VOID(void_function, int, a, int, b)
{
}
DWD_END()

int function_void()
{
    return 1;
}

void void_function_void()
{
}

class Example
{
private:
    int _field = 60;

public:
    Example(int a, int b);
    Example();
    ~Example();

    int method(int a, int b);
    void void_method(int a, int b);
    int method_void();
    void void_method_void();

    int method_const(int a, int b) const;
    void void_method_const(int a, int b) const;
    int method_void_const() const;
    void void_method_void_const() const;
};

Example::Example(int a, int b)
{
}

Example::Example()
{
}

Example::~Example()
{
}

int Example::method(int a, int b)
{
    return _field + a + b;
}

void Example::void_method(int a, int b)
{
}

int Example::method_void()
{
    return _field + 1;
}

void Example::void_method_void()
{
}

int Example::method_const(int a, int b) const
{
    return a + b;
}

void Example::void_method_const(int a, int b) const
{
}

int Example::method_void_const() const
{
    return _field + 1;
}

void Example::void_method_void_const() const
{
}

int _main()
{
    function(1, 2);
    void_function(1, 2);
    function_void();
    void_function_void();

    Example example;
    Example example2(1, 2);
    example.method(1, 2);
    example.void_method(1, 2);
    example.method_void();
    example.void_method_void();
    example.method_const(1, 2);
    example.void_method(1, 2);
    example.method_void_const();
    example.void_method_void_const();

    return 0;
}

int main()
{
    return _main();
}