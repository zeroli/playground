#include <dlfcn.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "prog_staticlib.h"

extern void duplicate_fun();

void run(const char* lib)
{
    fprintf(stderr, "dlmopen %s\n", lib);
    //void* h = dlopen(lib, RTLD_LAZY | RTLD_LOCAL | RTLD_DEEPBIND);
    //void* h = dlopen(lib, RTLD_LAZY | RTLD_LOCAL);
    void* h = dlmopen(LM_ID_NEWLM, lib, RTLD_LAZY | RTLD_LOCAL | RTLD_DEEPBIND);
    //void* h = dlmopen(LM_ID_NEWLM, lib, RTLD_LAZY | RTLD_LOCAL);
    fprintf(stderr, "h=%p\n", h); 
    if (!h) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }   

    typedef void (*funType)();
    void* fp = dlsym(h, "dlopen_fun");
    if (!fp)
        exit(2);
    funType f = (funType)fp;
    f();
}

int main()
{
    run("dlopen_lib.so");
    run("dlopen_lib_gcc7.so");

    duplicate_fun();

    std::cout << "main: std::cout = " << &std::cout << "\n";
    std::cout << "this is output from main's cout\n";

    foo();

    return 0;
}
