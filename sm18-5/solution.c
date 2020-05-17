#define DEBUG 0
#define ERRTEST 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

//https://stackoverflow.com/questions/16639275/grouping-child-processes-with-setgpid

int runItem(int *lp, int *rp, char* cmd)
{
    pid_t pid, pgid;
    pid = fork();

    if (pid < 0)
        return -1;

    pgid = setpgid(getpid(), getpgid(getppid()));

    if (pgid < 0)
        return -1;

    if (!pid)
    {
        if (lp[0])
        {
            dup2(lp[0], 0);
            close(lp[0]);
            lp[0] = 0;
        }

        if (lp[1])
        {
            close(lp[1]);
            lp[1] = 0;
        }

        if (rp[1])
        {
            dup2(rp[1], 1);
            close(rp[1]);
            rp[1] = 0;
        }

        execlp(cmd, cmd, NULL);
        _exit(EXIT_FAILURE);
    } else {
        if (lp[0])
        {
            close(lp[0]);
            lp[0] = 0;
        }

        if (lp[1])
        {
            close(lp[1]);
            lp[1] = 0;
        }

        if (rp[1])
        {
            close(rp[1]);
            rp[1] = 0;
        }

        return pid;
    }
}

int solution (int argc, char *argv[])
{
    pid_t *pids, pgid;
    int k, k0;
    int status, retval;
    int lp[2], rp[2];

#if DEBUG
    for (k = 0; k < argc; k++)
        printf("argv[%d]=\t\"%s\"\n", k, argv[k]);
#endif

    if (argc < 1)
        return 0;

    k = -1;
    pids = malloc(argc * sizeof(pid_t));
    if (!pids)
        return 1;

    if (argc > 1)
    {
        pgid = setpgid(getpid(), getpid());

        if (pgid < 0)
            goto closeAll;

        lp[0] = 0;
        lp[1] = 0;
        for (k = 0; k < argc - 1; k++)
        {
            pipe(rp);
            pids[k] = runItem(lp, rp, argv[k]);
            lp[0] = rp[0];
            lp[1] = rp[1];

            if (pids[k] == -1)
                goto closeAll;
        }

        lp[0] = rp[0];
        lp[1] = rp[1];
        rp[0] = 0;
        rp[1] = 0;
        pids[k] = runItem(lp, rp, argv[k]);
        if (pids[k] == -1)
            goto closeAll;
    } else {
        k = 0;
        lp[0] = 0;
        lp[1] = 0;
        rp[0] = 0;
        rp[1] = 0;
        pids[k] = runItem(lp, rp, argv[k]);

#if ERRTEST
        goto closeAll;
#else
        if (pids[k] == -1)
            goto closeAll;
#endif
    }

    k0 = k + 1;
    retval=0;
    goto closeExit;

closeAll:
    k0 = k + 1;
    retval = 1;
    for (k = 0; k < k0; k++)
        kill(pids[k], SIGKILL);

closeExit:
    for (k = 0; k < k0; k++)
    {

#if DEBUG
        printf("Waiting for %d (%d)\n", k, pids[k]);
#endif
        waitpid(pids[k], &status, 0);
        if (WIFEXITED(status)) retval|=WEXITSTATUS(status)?1:0;
        else if (WIFSIGNALED(status)) retval|=WTERMSIG(status)?1:0;
/*
        if (WIFEXITED(status)) return(WEXITSTATUS(status));
        else if (WIFSIGNALED(status)) return(1024+WTERMSIG(status));
        else if (WIFSTOPPED(status)) return(1024+WSTOPSIG(status));
        else if (WIFCONTINUED(status)) return(1024+SIGCONT);
*/
    }
    free(pids);
    return retval;
}

int main(int argc, char *argv[])
{
    int retval;
#if DEBUG
    if (argc==1)
    {
        fprintf(stderr,"%s cmd1 cmd2 cmd3 ...\n", argv[0]);
        return(1);
    }

    retval=solution(argc-1, &argv[1]);
    printf("%d\n", retval);
#else
    retval=solution(argc-1, &argv[1]);
#endif
    return(retval);
}
