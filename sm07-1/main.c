#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*funcptr_t)(double);

typedef struct FunctionTable_ {
    char name[20];
    funcptr_t fptr;
} FunctionTable;

FunctionTable fnt[]={	{"sin",&sin},
                        {"cos",&cos},
                        {"exp",&exp},
                        {"log",&log},
                        {"tan",&tan},
                        {"sqrt",&sqrt}
                    };

int main()
{
    char str[80];
    while (!feof(stdin))
    {
        if (fgets(str, 80, stdin) == NULL)
        {
            break;
        }
        printf("%s", str);
    }
    //sscanf;

    printf("%e\n",fnt[0].fptr(0.5));
    printf("%e\n",sin(0.5));

    return 0;
}