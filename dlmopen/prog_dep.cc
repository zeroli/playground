#include <iostream>
std::string duplicate_var = "prog_dep_var";
void duplicate_fun()
{
    std::cout << "this is duplicate function in prog_dep. address = " << (void*)&duplicate_fun
              << std::endl;
    std::cout << "duplicate var is " << duplicate_var
              << " in prog_dep. address = " << &duplicate_var << std::endl;
}
