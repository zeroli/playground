#include <stdio.h>
#include "staticlibexports.h"
#include "shlibexports.h"

static int local_function(int x)
{
    x = 1;
    printf("clientApp:: %s\n", __FUNCTION__);
    return 0;
}

static int local_function_strippedoff(int x)
{
    x = 1;
    printf("clientApp:: %s\n", __FUNCTION__);
    return 0;
}

int main()
{
    shlib_function();
    staticlib_function(1);
    local_function(1);
    local_function_strippedoff(1);
    return 0;
}

