#include <iostream>
#include "singleton.h"
#include "shlibsecondexports.h"

using namespace std;

int shlibsecond_function(void)
{
    std::cout << __FUNCTION__ << ":\n";
    Singleton& singleton = Singleton::GetInstance();
    singleton.Do();
    return 0;
}

