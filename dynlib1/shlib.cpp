#include <iostream>
#include "singleton.h"
#include "shlibfirstexports.h"

using namespace std;

int shlibfirst_function(void)
{
    std::cout << __FUNCTION__ << ":\n";
    Singleton& singleton = Singleton::GetInstance();
    singleton.Do();
    return 0;
}

