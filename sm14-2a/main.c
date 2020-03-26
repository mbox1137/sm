#include <stdio.h>
#include <dlfcn.h>

void process(void* func)
{
    double num, res;
    while (scanf("%lf", &num) == 1)
    {
        res = ((double(*)(double)) func)(num);
        printf("%.10g\n", res);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    void* lib = dlopen("/lib/libm.so.6", RTLD_LAZY);

    if (!lib)
    {
        char* err = dlerror();
        printf("%s\n", err);
        return 1;
    }

    void* func = dlsym(lib, argv[1]);

    if (!func)
    {
        char* err = dlerror();
        printf("%s\n", err);
        return 1;
    }

    process(func);

    dlclose(lib);

    return 0;
}
