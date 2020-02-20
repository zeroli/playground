#include <iostream>
#include "singleton.h"

using namespace std;

Singleton& Singleton::GetInstance()
{
    static Singleton singleton;
    return singleton;
}

int Singleton::Do()
{
    std::cout << "singleton instance address = " << this << std::endl;
    return 0;
}

