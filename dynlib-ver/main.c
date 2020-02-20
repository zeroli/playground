#include "stdio.h"

#include "simple.h"

int main()
{
    int n1 = foo1(1);
    int n2 = foo2(2);
    int n4 = foo4(4);
    int nr = n1 + n2 + n4;
    printf("foo1(1) + foo2(2) +foo4(4) = %d\n", nr);
    return 0;
}

