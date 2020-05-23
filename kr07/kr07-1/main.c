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

    fd1 = fopen(argv[2], "r");
    fd2 = fopen(argv[1], "r");

    pid1 = fork();

    if (pid1 == -1)
        return 1;

    if (!pid1)
    {
        sum1 = 0;

        if (fd1 == NULL)
            exit(EXIT_FAILURE);

        while(fscanf(fd1, "%d", &num) != EOF)
        {

#if DEBUG
            printf("%d\n", num);
#endif

            sum1 += num;
        }

        fclose(fd1);

        _exit(sum1);
    }

    pid2 = fork();

    if (pid2 == -1)
        return 1;

    if (!pid2)
    {
        sum2 = 0;

        if (fd2 == NULL)
            exit(EXIT_FAILURE);

        while(fscanf(fd1, "%d", &num) != EOF)
        {

#if DEBUG
            printf("%d\n", num);
#endif

            sum2 += num;
        }

        fclose(fd2);

        _exit(sum2);
    }

    waitpid(pid1, &wstatus1, 0);
    waitpid(pid2, &wstatus2, 0);

    printf("sum1 = %d\n", wstatus1);
    printf("sum2 = %d\n", wstatus2);

//    fclose(fd1);
//    fclose(fd2);

    printf("res = %d\n", wstatus1 + wstatus2);

    exit(EXIT_SUCCESS);
}
