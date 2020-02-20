#include "stdio.h"
#include "simple.h"

__asm__(".symver foo1_1_0,foo1@LIBSIMPLE_1.0");
int foo1_1_0(int x)
{
    printf("lib: %s\n", __FUNCTION__);
    return x+1;
}


__asm__(".symver foo1_2_0,foo1@LIBSIMPLE_2.0");
int foo1_2_0(int x)
{
    printf("lib: %s\n", __FUNCTION__);
    return 1000*(x+1);
}


__asm__(".symver foo1_3_0,foo1@@LIBSIMPLE_3.0");
int foo1_3_0(int x)
{
    printf("lib: %s\n", __FUNCTION__);
    return 2000*(x+1);
}

int foo2(int x)
{
    return x+2;
}

int foo3(int x)
{
    return x+3;
}

int foo4(int x)
{
    return x+4;
}

int foo5(int x)
{
    return x+5;
}

