#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/eventfd.h>

#define SIZE 4096 * sizeof(char) + sizeof(int)

char *buf;
int *counter;

int base;
int fd[2];

void increment(int j, size_t size)
{
    printf("%d %s\n", j, buf);
    fflush(stdout);

//    int len = strlen(buf);
    int carry = 1;

    for (int i = 0; i < size; ++i)
    {
        buf[i] += carry;

        if (buf[i] != '0' + base)
            carry = 0;
        else
        {
            buf[i] = '0';
            carry = 1;
        }
    }

    if (carry)
    {
        buf[size] = '1';
        buf[size + 1] = '\0';
    }

    (*counter)++;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
        exit(EXIT_FAILURE);

    int n;
    uint64_t t = 1;
    pid_t pid1, pid2;

    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &base) != 1)
        exit(EXIT_FAILURE);

    void* data = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (data == MAP_FAILED)
        exit(EXIT_FAILURE);

    counter = data;
    *counter = 1;

    buf = data + sizeof(int);
    strcpy(buf, argv[3]);
    size_t size = strlen(buf);

    fd[0] = eventfd(0, EFD_SEMAPHORE);
    fd[1] = eventfd(0, EFD_SEMAPHORE);

    if (fd[0] == -1 || fd[1] == -1)
        exit(EXIT_FAILURE);

    if (n == 0)
    {
        printf("Done\n");
        if (munmap(data, SIZE) == -1)
            exit(EXIT_FAILURE);

        exit(EXIT_SUCCESS);
    }
//-------------------------------------------------------------------------------------

    pid1 = fork();
    if (pid1 < 0)
        exit(EXIT_FAILURE);

    if (!pid1)
    {
//            uint64_t t = 1;
        t = 1;
        increment(1, size);

        if (write(fd[1], &t, sizeof(t)) != sizeof(t))
            exit(EXIT_FAILURE);

        while (*counter < n)
        {
            if (read(fd[0], &t, sizeof(t)) != sizeof(t))
                exit(EXIT_FAILURE);

            increment(1, size);

            if (write(fd[1], &t, sizeof(t)) != sizeof(t))
                    exit(EXIT_FAILURE);
        }

        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0)
        exit(EXIT_FAILURE);

    if (!pid2)
    {
//            uint64_t t;

        while (*counter < n)
        {
            if (read(fd[1], &t, sizeof(t)) != sizeof(t))
                exit(EXIT_FAILURE);

            increment(2, size);

            if (write(fd[0], &t, sizeof(t)) != sizeof(t))
                exit(EXIT_FAILURE);
        }

        exit(0);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

//--------------------------------------------------------------------------------------

    printf("Done\n");
    if (munmap(data, SIZE) == -1)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}

// аналогично лекции https://www.youtube.com/watch?v=BpaWnrVEnH4&feature=youtu.be&t=7885
