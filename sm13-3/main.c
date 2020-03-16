#include <stdio.h>

int main(int argc, char **argv)
{
    char fn[80]="main.dat";
    if(argc==2)
    {
        sscanf(argv[1],"%s",fn);
    } else
        printf("./main [main.dat]\n");
    return(0);
}
