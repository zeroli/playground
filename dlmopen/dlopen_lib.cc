extern void duplicate_fun();
extern "C" {
void dlopen_fun()
{
    duplicate_fun();
}
}
