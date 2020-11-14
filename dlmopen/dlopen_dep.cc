#include <iostream>

std::string duplicate_var = "dlopen_dep_var";

void duplicate_fun()
{
    std::cout << "dlopen_dep: std::cout = " << &std::cout << "\n";
    std::cout << "this is duplicate function in dlopen_dep. address = " << (void*)&duplicate_fun
              << std::endl;
    std::cout << "duplicate var is " << duplicate_var
              << " in dlopen_dep. address = " << &duplicate_var << std::endl;
}
