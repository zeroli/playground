#include <iostream>
#include "singleton.h"
#include "shlibfirstexports.h"
#include "shlibsecondexports.h"

using namespace std;

int main()
{
    shlibfirst_function();
    shlibsecond_function();

    std::cout << "Accessing singleton directly from the client App" << std::endl;
    Singleton& singleton = Singleton::GetInstance();
    singleton.Do();

    return 0;
}
