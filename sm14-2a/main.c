#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char ** argv)
{
    if (argc != 2)
        return 1;

    void* lib = dlopen("/lib/libm.so.6", RTLD_LAZY);

    if (!lib)
    {
        printf("%s\n", dlerror());
        return 1;
    }

    void * func = dlsym(lib, argv[1]);

    if (!func)
    {
        printf("%s\n", dlerror());
        return 2;
    }

    double num;

    while (scanf("%lf", &num) == 1)
        printf("%.10g\n", ((double(*)(double)) func)(num));
}
