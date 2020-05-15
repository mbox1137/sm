#define DEBUG 0
#define FSIZE 30
#define ASCII_START 48
#define ASCII_END 122

#include <ctype.h>
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
    char chek;
    char *temp = malloc(FSIZE);
    if (temp == NULL)
        exit(EXIT_FAILURE);

    int fd, i;
    char *dir = getenv("XDG_RUNTIME_DIR");

    if (!dir)
        dir = getenv("TMPDIR");

    if (!dir)
        strcpy(path, "/tmp");
    else
        strcpy(path, dir);
    strcat(path, "/");

#if DEBUG
    printf("%s\n", path);
#endif

    srand(time(NULL));

    for(int i = 0; i < FSIZE - 3; i++)
    {
        chek = (char) (rand()%(ASCII_END - ASCII_START)) + ASCII_START;
        while(!isdigit(chek) && !isalpha(chek))
            chek = (char) (rand()%(ASCII_END - ASCII_START)) + ASCII_START;
        temp[i] = chek;
    }

    strcat(path, temp);
    strcat(path, ".py");

#if DEBUG
    printf("%s\n", path);
#endif

    fd = creat(path, 0700);

    dprintf(fd, "#!/usr/bin/env python3\n");
    dprintf(fd, "from sys import argv\n");
    dprintf(fd, "from os import remove\n");
    dprintf(fd, "print(");

    for (i = 1; i < argc - 1; ++i)
    {
        dprintf(fd, argv[i]);
        dprintf(fd, "*");
    }
    dprintf(fd, argv[i]);
    dprintf(fd, ")\n");
    dprintf(fd, "remove(argv[0])\n");

    close(fd);

    execlp("/bin/sh", "sh", "-c", path, NULL);

    exit(EXIT_SUCCESS);
}

// идея рандома взята с https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
//        write(fd, argv[i], sizeof(char) * strlen(argv[i]));
//        write(fd, "*", sizeof(char));

