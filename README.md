# Welcome to Dumb-Ways-to-Debug!

You already tried all smart ways to debug? Your platform has no debugger? Or is a serial port the only way to communicate with the software? Anyway, you found the right repo.

# Usage
```
//Non-debugged version
int add(int a, int b) { return a + b; }

//Debugged version
DWD_PRINT_TRACE(int, add, int, a, int, b) { return a + b; }
```

The functions need to be declared with `DWD_PRINT_*` or `DWD_CATCH_*` macros. Both will print  the function call log (name and arguments) when your program calls `DWD::EXIT()`. The difference is that `DWD_CATCH_*` prints only when the function fails, `DWD_PRINT_*` will print in any case, including normal return command. Also the program will print only if the function's log level is higher or equal to `DWD::LOGLEVEL`.

# Compilation

Paste `.cpp` files into your project. Implement `dwd_desktop.h` for your platform (for example, serial port of your favorite microcontroller). You are on your own here.