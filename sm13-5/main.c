#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <malloc.h>
#include "myaccess.h"

int main(int argc, char **argv)
{
    struct stat stb;
    struct Task task;
    int access;
    int k, res;
    if(argc==1)
    {
//
        task.uid=77;
        task.gid_count=3;
        task.gids=(int*) calloc(task.gid_count, sizeof(int));
        int tmp[]={77,88,99};
        for(k=0; k<task.gid_count; k++)
            task.gids[k]=tmp[k];
//
        stb.st_uid=0;
        stb.st_gid=88;
        stb.st_mode=0660;
//
        access=6;
    } else
    if(argc>7)
    {
        sscanf(argv[1],"%i",&task.uid);
        sscanf(argv[2],"%i",&task.gid_count);
        task.gids=(int*) calloc(task.gid_count, sizeof(int));
        for(k=0; k<task.gid_count; k++)
            sscanf(argv[3+k],"%i",&task.gids[k]);
        sscanf(argv[3+k],"%i",&stb.st_uid);
        sscanf(argv[4+k],"%i",&stb.st_gid);
        sscanf(argv[5+k],"%i",&stb.st_mode);
        sscanf(argv[6+k],"%i",&access);
    } else
        printf("task: {uid ngids [gid]} stat: {uid gid mode} access\n");
    printf("job(u[g]): ");
    printf("%u ",task.uid);
    printf("[");
    for(k=0; k<task.gid_count; k++)
        printf("%u ",task.gids[k]);
    printf("] ");
    printf("; ");
    printf("file(ugm): ");
    printf("%u ",stb.st_uid);
    printf("%u ",stb.st_gid);
    printf("0%3o ",stb.st_mode);
    printf("; ");
    printf("? ");
    printf("0%o ",access);
    printf("; ");
    res=myaccess(&stb, &task, access);
    if(res)
        printf("Granted");
    else
        printf("Denied");
    printf("\n");
    free(task.gids);
    return(0);
}
