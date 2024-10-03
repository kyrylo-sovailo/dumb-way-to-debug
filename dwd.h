#pragma once
#include <vector>
#include <functional>

//Variables and functions
namespace DWD
{
    struct GUARD;

    extern int LOGLEVEL;
    extern GUARD *TOP;

    struct GUARD
    {
        GUARD *previous;
        std::function<void()> head;
        GUARD(std::function<void()> head);
        ~GUARD();
    };
    
    void EXIT(int code);
}

//For loops
#define DWD_STRINGIZE(_A)  __DWD_STRINGIZE1(_A)
#define __DWD_STRINGIZE1(_A) __DWD_STRINGIZE2(_A)
#define __DWD_STRINGIZE2(_A) #_A
#define DWD_CONCATENATE(_A, _B)   __DWD_CONCATENATE1(_A, _B)
#define __DWD_CONCATENATE1(_A, _B)  __DWD_CONCATENATE2(_A, _B)
#define __DWD_CONCATENATE2(_A, _B)  _A##_B
#define __DWD_APPEND_SEQUENCE(...) __DWD_ARGUMENT_N1(__VA_ARGS__, __DWD_SEQUENCE())
#define __DWD_ARGUMENT_N1(...) __DWD_ARGUMENT_N(__VA_ARGS__) 
#define __DWD_ARGUMENT_N(_1, _2, _3, _4, _5, _6, _7, _8, _N, ...) _N
#define __DWD_SEQUENCE() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define __DWD_FOR_1(_KERNEL, _A)      _KERNEL(_A)
#define __DWD_FOR_2(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_1(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_3(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_2(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_4(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_3(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_5(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_4(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_6(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_5(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_7(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_6(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_8(_KERNEL, _A, ...) _KERNEL(_A); __DWD_FOR_7(_KERNEL, __VA_ARGS__);
#define __DWD_FOR_(_N, _KERNEL, _A, ...) DWD_CONCATENATE(__DWD_FOR_, _N)(_KERNEL, _A, __VA_ARGS__)
#define __DWD_FOR(_KERNEL, _A, ...) __DWD_FOR_(__DWD_APPEND_SEQUENCE(_A, __VA_ARGS__), _KERNEL, _A, __VA_ARGS__)

#define __DWD_FOR2S_2(_KERNEL, _A, _B)      _KERNEL(_A, _B);
#define __DWD_FOR2S_4(_KERNEL, _A, _B, ...) _KERNEL(_A, _B); __DWD_FOR2S_2(_KERNEL, __VA_ARGS__);
#define __DWD_FOR2S_6(_KERNEL, _A, _B, ...) _KERNEL(_A, _B); __DWD_FOR2S_4(_KERNEL, __VA_ARGS__);
#define __DWD_FOR2S_8(_KERNEL, _A, _B, ...) _KERNEL(_A, _B); __DWD_FOR2S_6(_KERNEL, __VA_ARGS__);
#define __DWD_FOR2S_(_N, _KERNEL, _A, _B, ...) DWD_CONCATENATE(__DWD_FOR2S_, _N)(_KERNEL, _A, _B, __VA_ARGS__)
#define __DWD_FOR2S(_KERNEL, _A, _B, ...) __DWD_FOR2S_(__DWD_APPEND_SEQUENCE(_A, _B, __VA_ARGS__), _KERNEL, _A, _B, __VA_ARGS__)

#define __DWD_FOR2C_2(_KERNEL, _A, _B)      _KERNEL(_A, _B)
#define __DWD_FOR2C_4(_KERNEL, _A, _B, ...) _KERNEL(_A, _B), __DWD_FOR2C_2(_KERNEL, __VA_ARGS__)
#define __DWD_FOR2C_6(_KERNEL, _A, _B, ...) _KERNEL(_A, _B), __DWD_FOR2C_4(_KERNEL, __VA_ARGS__)
#define __DWD_FOR2C_8(_KERNEL, _A, _B, ...) _KERNEL(_A, _B), __DWD_FOR2C_6(_KERNEL, __VA_ARGS__)
#define __DWD_FOR2C_(_N, _KERNEL, _A, _B, ...) DWD_CONCATENATE(__DWD_FOR2C_, _N)(_KERNEL, _A, _B, __VA_ARGS__)
#define __DWD_FOR2C(_KERNEL, _A, _B, ...) __DWD_FOR2C_(__DWD_APPEND_SEQUENCE(_A, _B, __VA_ARGS__), _KERNEL, _A, _B, __VA_ARGS__)

//Kernels
#define __DWD_LIST_TYPE_NAME(_TYPE, _NAME) _TYPE _NAME
#define __DWD_LIST_NAME(_TYPE, _NAME) _NAME
#define __DWD_PRINT_NAME(_TYPE, _NAME) DWD::PRINT("DWD Argument \"" DWD_STRINGIZE(_NAME) "\": "); DWD::PRINT(_NAME); DWD::PRINT('\n')

//Functionality
#define __DWD_STACK_HEAD(_LOGLEVEL, _TYPE, _NAME, ...) _TYPE _NAME(__DWD_FOR2C(__DWD_LIST_TYPE_NAME, __VA_ARGS__)) \
{ \
    auto head = [=]() -> void { \
        if (DWD::LOGLEVEL >= 0) \
        { \
            DWD::PRINT(DWD_FLASH("DWD Function \"" DWD_STRINGIZE(_NAME) "\" at "  __FILE__ ":" DWD_STRINGIZE(__LINE__) "\n")); \
            __DWD_FOR2S(__DWD_PRINT_NAME, __VA_ARGS__) \
        } \
    }; \
    DWD::GUARD guard(head);

#define DWD_WRAP_VERBOSE(_LOGLEVEL, _TYPE, _NAME, ...) __DWD_STACK_HEAD(_LOGLEVEL, _TYPE, _NAME, __VA_ARGS__) \
    head(); \
    constexpr bool print_tail = true; \
    auto function = [=]() -> _TYPE \
    {

#define DWD_WRAP(_LOGLEVEL, _TYPE, _NAME, ...) __DWD_STACK_HEAD(_LOGLEVEL, _TYPE, _NAME, __VA_ARGS__) \
    constexpr bool print_tail = false; \
    auto function = [=]() -> _TYPE \
    {

#define DWD_END() }; \
    try \
    { \
        auto result = function(); \
        if (print_tail && DWD::LOGLEVEL >= 0) { DWD::PRINT(DWD_FLASH("DWD Return: ")); DWD::PRINT(result); DWD::PRINT('\n'); }\
        return result; \
    } \
    catch (const std::exception &e) \
    { \
        if (print_tail && DWD::LOGLEVEL >= 0) { DWD::PRINT(DWD_FLASH("DWD Exception: ")); DWD::PRINT(e.what()); DWD::PRINT('\n'); } \
        throw e; \
    } \
}

//Shortcuts
#define DWD_FATAL_VERBOSE(_TYPE, _NAME, ...) DWD_WRAP_VERBOSE(1, _TYPE, _NAME, __VA_ARGS__)
#define DWD_ERROR_VERBOSE(_TYPE, _NAME, ...) DWD_WRAP_VERBOSE(2, _TYPE, _NAME, __VA_ARGS__)
#define DWD_WARN_VERBOSE( _TYPE, _NAME, ...) DWD_WRAP_VERBOSE(3, _TYPE, _NAME, __VA_ARGS__)
#define DWD_INFO_VERBOSE( _TYPE, _NAME, ...) DWD_WRAP_VERBOSE(4, _TYPE, _NAME, __VA_ARGS__)
#define DWD_DEBUG_VERBOSE(_TYPE, _NAME, ...) DWD_WRAP_VERBOSE(5, _TYPE, _NAME, __VA_ARGS__)
#define DWD_TRACE_VERBOSE(_TYPE, _NAME, ...) DWD_WRAP_VERBOSE(6, _TYPE, _NAME, __VA_ARGS__)

#define DWD_FATAL(_TYPE, _NAME, ...) DWD_WRAP(1, _TYPE, _NAME, __VA_ARGS__)
#define DWD_ERROR(_TYPE, _NAME, ...) DWD_WRAP(2, _TYPE, _NAME, __VA_ARGS__)
#define DWD_WARN( _TYPE, _NAME, ...) DWD_WRAP(3, _TYPE, _NAME, __VA_ARGS__)
#define DWD_INFO( _TYPE, _NAME, ...) DWD_WRAP(4, _TYPE, _NAME, __VA_ARGS__)
#define DWD_DEBUG(_TYPE, _NAME, ...) DWD_WRAP(5, _TYPE, _NAME, __VA_ARGS__)
#define DWD_TRACE(_TYPE, _NAME, ...) DWD_WRAP(6, _TYPE, _NAME, __VA_ARGS__)