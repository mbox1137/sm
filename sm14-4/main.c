#include <stdio.h>
#include <string.h>
#include <time.h>

#define NN 1000

int main(int argc, char **argv)
{
    char str[NN];
    char delim[]=" \t\r\n";
    char *ft, *from, *to, *tmp;
    unsigned long long a1, a2, ds, sum;
    int err, bof;
    sum=0;
    err=feof(stdin);
    bof=1;
    while(!feof(stdin)) {
        if (fgets(str, NN, stdin) == NULL) {
            if(bof) err=1;
            break;
        }
        bof=0;
        if(strlen(str) < 5) {err=1; continue;}
        if((ft = strtok(str, delim)) == NULL) {err=1; continue;}
        if((from = strtok(ft, "-")) == NULL) {err=1; continue;}
        if((to = strtok(NULL, "-")) == NULL) {err=1; continue;}
        if((tmp = strtok(NULL, "-")) != NULL) {err=1; continue;}
//        printf("%s %s\n", from, to);
        if(sscanf(from, "%llx", &a1)!=1) {err=1; continue;}
        if(sscanf(to, "%llx", &a2)!=1) {err=1; continue;}
        if(a1>a2) {err=1; continue;}
        ds = a2-a1;
        sum += ds;
//        printf("a1=0x%x\ta2=0x%x\tds=0x%x\tsum=0x%x\n", a1, a2, ds, sum);
    }
    if(err!=0) {
        return(-1);
    } else {
        printf("%llu\n", sum);
        return(0);
    }
}
