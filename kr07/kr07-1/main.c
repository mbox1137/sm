#define DEBUG 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fd1, *fd2;
    pid_t pid1, pid2;
    int num, wstatus1, wstatus2;
    int sum1, sum2;

    if (argc != 3)
        return 1;

    fd1 = fopen(argv[1], "r");
    fd2 = fopen(argv[2], "r");
#if DEBUG
    printf("fn1=%s (%p)\n", argv[1], fd1);
    printf("fn2=%s (%p)\n", argv[2], fd2);
#endif

    pid1 = fork();

    if(pid1 == -1)
        return 1;

    if(!pid1)
    {
        sum1 = 0;

#if DEBUG
        printf("p1: fn1=%s (%p)\n", argv[1], fd1);
        printf("p1: fn2=%s (%p)\n", argv[2], fd2);
#endif
        if (fd1 == NULL)
            exit(EXIT_FAILURE);

        while(fscanf(fd1, "%d", &num) == 1 )
        {

#if DEBUG
            printf("p1: %d\n", num);
#endif

            sum1 += num;
        }

//        fclose(fd1);
        fflush(stdout);
        exit(sum1);
    }

    pid2 = fork();

    if(pid2 == -1)
        return 1;

    if(!pid2)
    {
        sum2 = 0;

#if DEBUG
        printf("p2: fn1=%s (%p)\n", argv[1], fd1);
        printf("p2: fn2=%s (%p)\n", argv[2], fd2);
#endif
        if(!fd2)
            exit(EXIT_FAILURE);

        while(fscanf(fd1, "%d", &num) == 1 )
        {

#if DEBUG
            printf("p2: %d\n", num);
#endif

            sum2 += num;
        }

//        fclose(fd2);
        fflush(stdout);
        exit(sum2);
    }

    waitpid(pid1, &wstatus1, 0);
    waitpid(pid2, &wstatus2, 0);

    fclose(fd1);
    fclose(fd2);
#if DEBUG
    printf("sum2 = %d\n", wstatus2);
    printf("sum1 = %d\n", wstatus1);
    printf("res = %d\n", wstatus1 + wstatus2);
#else
    printf("%d\n", wstatus2);
    printf("%d\n", wstatus1);
    printf("%d\n", wstatus1 + wstatus2);
#endif
    exit(EXIT_SUCCESS);
}
