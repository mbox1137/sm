#include <stdio.h>
#include <string.h>
#include <time.h>

#define NN 1000

int main(int argc, char **argv)
{
    char str[NN];
    char delim[]=" \t\r\n";
    char *ft, *from, *to;
    long long a1, a2, ds, sum;
    sum=0;
    while(!feof(stdin)) {
        if (fgets(str, NN, stdin) == NULL)
            break;
        if((ft = strtok(str, delim)) == NULL) continue;
        if((from = strtok(ft, "-")) == NULL) continue;
        if((to = strtok(NULL, "-")) == NULL) continue;
//        printf("%s %s\n", from, to);
        if(sscanf(from, "%llx", &a1)!=1) continue;
        if(sscanf(to, "%llx", &a2)!=1) continue;
        ds = a2-a1;
        sum += ds;
//        printf("a1=0x%x\ta2=0x%x\tds=0x%x\tsum=0x%x\n", a1, a2, ds, sum);
    }
    printf("%llu\n", sum);
    return(0);
}
