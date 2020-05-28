#define DEBUG 0

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
        exit(EXIT_FAILURE);

    int cmp;
    float x;
    void *lib, *func;
    char *remember = "";

    if (sscanf(argv[1], "%f", &x) != 1)
        exit(EXIT_FAILURE);

    for(size_t i = 2; i < argc; i += 2)
    {
        cmp = strcmp(argv[i], "-");

        if (cmp != 0)
            lib = dlopen(argv[i], RTLD_LAZY);
        else
            lib = dlopen(remember, RTLD_LAZY);

        if (lib == NULL)
            continue;

#if DEBUG
        printf("lib ok\n");
#endif

        func = dlsym(lib, argv[i + 1]);

        if (func == NULL)
        {
            dlclose(lib);
            continue;
        }

#if DEBUG
        printf("func ok\n");
#endif

        x = ((float(*)(float)) func)(x);

        if (cmp != 0)
            remember = argv[i];

#if DEBUG
        printf("cur_x = %f\n\n", x);
#endif

        dlclose(lib);
    }

    printf("%.6g\n", x);

    exit(EXIT_SUCCESS);
}
