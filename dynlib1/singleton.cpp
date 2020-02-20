#include <iostream>
#include "singleton.h"

using namespace std;

Singleton* Singleton::m_pInstance = NULL;

Singleton& Singleton::GetInstance()
{
    if (NULL == m_pInstance) 
        m_pInstance = new Singleton();
    return *m_pInstance;
}

int Singleton::Do()
{
    std::cout << "singleton instance address = " << this << std::endl;
    return 0;
}

