#include <iostream>

//Common
#define DWD_STRINGIZE(_A)  DWD_STRINGIZE1(_A)
#define DWD_STRINGIZE1(_A) DWD_STRINGIZE2(_A)
#define DWD_STRINGIZE2(_A) #_A
#define DWD_CONCATENATE(_A, _B)   DWD_CONCATENATE1(_A, _B)
#define DWD_CONCATENATE1(_A, _B)  DWD_CONCATENATE2(_A, _B)
#define DWD_CONCATENATE2(_A, _B)  _A##_B
#define DWD_APPEND_SEQUENCE(...) DWD_ARGUMENT_N1(__VA_ARGS__, DWD_SEQUENCE())
#define DWD_ARGUMENT_N1(...) DWD_ARGUMENT_N(__VA_ARGS__) 
#define DWD_ARGUMENT_N(_1, _2, _3, _4, _5, _6, _7, _8, _N, ...) _N 
#define DWD_SEQUENCE() 8, 7, 6, 5, 4, 3, 2, 1, 0

int DWD_LOGLEVEL = 7;
#define DWD_FATAL 1
#define DWD_ERROR 2
#define DWD_WARN 3
#define DWD_INFO 4
#define DWD_DEBUG 5
#define DWD_TRACE 6

//For loops
#define DWD_FOR_1(_KERNEL, _A, ...) _KERNEL(_A)
#define DWD_FOR_2(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_1(_KERNEL, __VA_ARGS__);
#define DWD_FOR_3(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_2(_KERNEL, __VA_ARGS__);
#define DWD_FOR_4(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_3(_KERNEL, __VA_ARGS__);
#define DWD_FOR_5(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_4(_KERNEL, __VA_ARGS__);
#define DWD_FOR_6(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_5(_KERNEL, __VA_ARGS__);
#define DWD_FOR_7(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_6(_KERNEL, __VA_ARGS__);
#define DWD_FOR_8(_KERNEL, _A, ...) _KERNEL(_A); DWD_FOR_7(_KERNEL, __VA_ARGS__);
#define DWD_FOR_(_N, _KERNEL, _A, ...) DWD_CONCATENATE(DWD_FOR_, _N)(_KERNEL, _A, __VA_ARGS__)
#define DWD_FOR(_KERNEL, _A, ...) DWD_FOR_(DWD_APPEND_SEQUENCE(_A, __VA_ARGS__), _KERNEL, _A, __VA_ARGS__)

#define DWD_FOR2S_2(_KERNEL, _A, _B, ...) _KERNEL(_A, _B);
#define DWD_FOR2S_4(_KERNEL, _A, _B, ...) _KERNEL(_A, _B); DWD_FOR2S_2(_KERNEL, __VA_ARGS__);
#define DWD_FOR2S_6(_KERNEL, _A, _B, ...) _KERNEL(_A, _B); DWD_FOR2S_4(_KERNEL, __VA_ARGS__);
#define DWD_FOR2S_8(_KERNEL, _A, _B, ...) _KERNEL(_A, _B); DWD_FOR2S_6(_KERNEL, __VA_ARGS__);
#define DWD_FOR2S_(_N, _KERNEL, _A, _B, ...) DWD_CONCATENATE(DWD_FOR2S_, _N)(_KERNEL, _A, _B, __VA_ARGS__)
#define DWD_FOR2S(_KERNEL, _A, _B, ...) DWD_FOR2S_(DWD_APPEND_SEQUENCE(_A, _B, __VA_ARGS__), _KERNEL, _A, _B, __VA_ARGS__)

#define DWD_FOR2C_2(_KERNEL, _A, _B, ...) _KERNEL(_A, _B)
#define DWD_FOR2C_4(_KERNEL, _A, _B, ...) _KERNEL(_A, _B), DWD_FOR2C_2(_KERNEL, __VA_ARGS__)
#define DWD_FOR2C_6(_KERNEL, _A, _B, ...) _KERNEL(_A, _B), DWD_FOR2C_4(_KERNEL, __VA_ARGS__)
#define DWD_FOR2C_8(_KERNEL, _A, _B, ...) _KERNEL(_A, _B), DWD_FOR2C_6(_KERNEL, __VA_ARGS__)
#define DWD_FOR2C_(_N, _KERNEL, _A, _B, ...) DWD_CONCATENATE(DWD_FOR2C_, _N)(_KERNEL, _A, _B, __VA_ARGS__)
#define DWD_FOR2C(_KERNEL, _A, _B, ...) DWD_FOR2C_(DWD_APPEND_SEQUENCE(_A, _B, __VA_ARGS__), _KERNEL, _A, _B, __VA_ARGS__)

//Kernels
#define DWD_LIST_TYPE_NAME(_TYPE, _NAME) _TYPE _NAME
#define DWD_LIST_NAME(_TYPE, _NAME) _NAME
#define DWD_PRINT_NAME(_TYPE, _NAME) std::cout << "DWD Argument \"" DWD_STRINGIZE(_NAME) "\": " << _NAME << std::endl

//Functionality
#define DWD_BEGIN(_LOGLEVEL, _TYPE, _NAME, ...) _TYPE _NAME(DWD_FOR2C(DWD_LIST_TYPE_NAME, __VA_ARGS__)) \
{ \
    if (DWD_LOGLEVEL >= 0) \
    { \
        std::cout << "DWD Function \"" DWD_STRINGIZE(_NAME) "\" called" << std::endl; \
        DWD_FOR2S(DWD_PRINT_NAME, __VA_ARGS__) \
    } \
    auto function = [=]() -> _TYPE \
    {

#define DWD_END() }; \
    try \
    { \
        auto result = function(); \
        if (DWD_LOGLEVEL >= 0) std::cout << "DWD Return: " << result << std::endl; \
        return result; \
    } \
    catch (const std::exception &e) \
    { \
        if (DWD_LOGLEVEL >= 0) std::cout << "DWD Exception: " << e.what() << std::endl; \
        throw e; \
    } \
}

#define DWD_BEGIN_FATAL(_TYPE, _NAME, ...) DWD_BEGIN(DWD_FATAL, _TYPE, _NAME, __VA_ARGS__)
#define DWD_BEGIN_ERROR(_TYPE, _NAME, ...) DWD_BEGIN(DWD_ERROR, _TYPE, _NAME, __VA_ARGS__)
#define DWD_BEGIN_WARN( _TYPE, _NAME, ...) DWD_BEGIN(DWD_WARN,  _TYPE, _NAME, __VA_ARGS__)
#define DWD_BEGIN_INFO( _TYPE, _NAME, ...) DWD_BEGIN(DWD_INFO,  _TYPE, _NAME, __VA_ARGS__)
#define DWD_BEGIN_DEBUG(_TYPE, _NAME, ...) DWD_BEGIN(DWD_DEBUG, _TYPE, _NAME, __VA_ARGS__)
#define DWD_BEGIN_TRACE(_TYPE, _NAME, ...) DWD_BEGIN(DWD_TRACE, _TYPE, _NAME, __VA_ARGS__)

DWD_BEGIN_TRACE(int, add, int, a, int, b)
{
    return a + b;
}
DWD_END()

int main(int argc, char *argv[])
{
    std::cout << add(1, 2) << std::endl;
    return 0;
}