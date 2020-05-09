#define DEBUG 0

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/file.h>

int startArithmeticProgression(int h, int i, int n, int a0, int d, int k) //pid
{
    pid_t cpid;
    int a, j;
    cpid = fork();
    if (cpid < 0)
    {
        close(h);
        perror("fork");
        return EXIT_FAILURE;
    }
    if (cpid == 0)
    {
        a = a0;
        for(j = 0; j < k; j++)
        {
            pwrite(h, &a, sizeof(int), (i + j * n) * sizeof(int));
            a += d;
        }
        close(h);
        exit(EXIT_SUCCESS);
    } else
        return(cpid);
}

int main(int argc, char *argv[])
{
    int n, a0, d, k, i;
    int h;
    char f[132];
    pid_t *cpids;
    int pstat;

    if (argc == 1)
    {
        n = 3;
        strcpy(f, "out.bin");
        a0 = 4;
        d = 2;
        k = 4;
    } else if (argc == 6)
    {
        if(sscanf(argv[1], "%d", &n) != 1)
            exit(1);
        if(sscanf(argv[2], "%s", f) != 1)
            exit(1);
        if(sscanf(argv[3], "%d", &a0) != 1)
            exit(1);
        if(sscanf(argv[4], "%d", &d) != 1)
            exit(1);
        if(sscanf(argv[5], "%d", &k) != 1)
            exit(1);
    } else
    {
        fprintf(stderr, "%s: 3 out.bin 4 2 4", argv[0]);
        exit(1);
    }
#if DEBUG
    printf("N=%d F=%s A0=%d D=%d K=%d\n", n, f, a0, d, k);
#endif
    if ((h = creat(f, S_IRUSR|S_IWUSR| S_IRGRP| S_IROTH)) == 0)
        return(-3);
    if (ftruncate(h, n * k * sizeof(int)))
    {
        perror("ftruncate");
        return(-2);
    }
    cpids = malloc(n * sizeof(pid_t));
    if(cpids == NULL)
        return -1;

    for(i = 0; i < n; i++)
        cpids[i] = startArithmeticProgression(h, i, n, a0 + d * i, d * n, k);

    for(i = 0; i < n; i++)
        waitpid(cpids[i], &pstat, 0);

    free(cpids);

    close(h);

    return 0;
}

// http://www.opennet.ru/base/dev/unix_signals.txt.html
