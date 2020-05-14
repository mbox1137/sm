#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
        exit(EXIT_FAILURE);

    char path[PATH_MAX];
    char temp[20];
    int outfd, i;
    char *dir = getenv("XDG_RUNTIME_DIR");

    if (!dir)
        dir = getenv("TMPDIR");

    if (!dir)
        strcpy(path, "/tmp/");
    else
    {
        strcpy(path, dir);
        strcat(path, "/");
    }

#if DEBUG
    printf("%s\n", path);
#endif

    time_t t;
    time(&t);

    sprintf(temp, "%ld", t);

    strcat(path, temp);

#if DEBUG
    printf("%s\n", path);
#endif

    srand(time(NULL));
    sprintf(temp, "%d", rand() % 100000000);
    strcat(path, temp);
    strcat(path, ".py");

#if DEBUG
    printf("%s\n", path);
#endif

    outfd = creat(path, 0700);

    write(outfd, "#!/usr/bin/env python3\n", 23 * sizeof(char));
    write(outfd, "from sys import argv\n", 21 * sizeof(char));
    write(outfd, "from os import remove\n", 22 * sizeof(char));
    write(outfd, "print(", 6 * sizeof(char));
    for (i = 1; i < argc - 1; ++i)
    {
        write(outfd, argv[i], sizeof(char) * strlen(argv[i]));
        write(outfd, "*", sizeof(char));
    }
    write(outfd, argv[i], sizeof(char) * strlen(argv[i]));
    write(outfd, ")\n", 2 * sizeof(char));
    write(outfd, "remove(argv[0])\n", 16 * sizeof(char));

    close(outfd);

    execlp("/bin/sh", "sh", "-c", path, NULL);

    exit(EXIT_SUCCESS);
}

