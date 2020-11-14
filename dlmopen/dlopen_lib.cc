#include <iostream>

extern void duplicate_fun();
extern "C" {
void dlopen_fun()
{
    std::cout << "dlopen_lib: std::cout = " << &std::cout << "\n";
    duplicate_fun();
}
}
