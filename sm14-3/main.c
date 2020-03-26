#include <stdio.h>
#include <string.h>
#include <time.h>

#define NN 1000

int main(int argc, char **argv)
{
    char str[NN];
    char delim[]=" \t\r\n";
    char *ft, *from, *to;
    unsigned int a1, a2, ds, sum;
    sum=0;
    while(!feof(stdin)) {
        if (fgets(str, NN, stdin) == NULL)
            break;
        ft = strtok(str, delim);
        from = strtok(ft, "-");
        to = strtok(NULL, "-");
//        printf("%s %s\n", from, to);
        sscanf(from, "%x", &a1);
        sscanf(to, "%x", &a2);
        ds = a2-a1;
        sum += ds;
//        printf("a1=0x%x\ta2=0x%x\tds=0x%x\tsum=0x%x\n", a1, a2, ds, sum);
    }
    printf("%u\n", sum);
    return(0);
}
