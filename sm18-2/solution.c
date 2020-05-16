#define DEBUG 0
#define INT sizeof(int)

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <inttypes.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    int32_t num;
    int nnum;
    long long sum = 0;

    if (pipe(pipefd) == -1)
        exit(EXIT_FAILURE);

    pid_t pid1 = fork(); // child

    if (pid1 == -1)
        exit(EXIT_FAILURE);

    if (!pid1)
    {
        pid_t pid2 = fork();  // grand child

        if (pid2 == -1)
            exit(EXIT_FAILURE);

        if (!pid2)
        {
            close(pipefd[1]);

            while (read(pipefd[0], &nnum, INT))
                sum += nnum;

            close(pipefd[0]);

            printf("%lld\n", sum);

            exit(EXIT_SUCCESS);

        }

        close(pipefd[0]);
        close(pipefd[1]);

        waitpid(pid2, 0, 0);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);

    while (scanf("%" SCNd32, &num) == 1)
        write(pipefd[1], &num, INT);

    close(pipefd[1]);

    waitpid(pid1, 0, 0);

    exit(EXIT_SUCCESS);
}
